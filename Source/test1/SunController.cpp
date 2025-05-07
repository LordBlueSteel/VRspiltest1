#include "SunController.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ASunController::ASunController()
{
    PrimaryActorTick.bCanEverTick = true;
    SunLight = nullptr; // Explicit initialization
}

void ASunController::BeginPlay()
{
    Super::BeginPlay();

    // Find all directional lights in the level
    TArray<AActor*> FoundLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundLights);

    if (FoundLights.Num() > 0)
    {
        // Use the first found directional light
        SunLight = Cast<ADirectionalLight>(FoundLights[0]);
        if (SunLight && SunLight->GetLightComponent())
        {
            // Configure the light
            SunLight->GetLightComponent()->SetMobility(EComponentMobility::Movable);
            SunLight->GetLightComponent()->SetIntensity(Intensity);
            SunLight->GetLightComponent()->SetLightColor(SunColor);
            UE_LOG(LogTemp, Log, TEXT("Found and configured directional light: %s"), *SunLight->GetName());
        }
    }
    else
    {
        // Spawn a new directional light if none exists
        SunLight = GetWorld()->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), FVector::ZeroVector, FRotator(-45.f, 0.f, 0.f));
        if (SunLight && SunLight->GetLightComponent())
        {
            SunLight->GetLightComponent()->SetMobility(EComponentMobility::Movable);
            SunLight->GetLightComponent()->SetIntensity(Intensity);
            SunLight->GetLightComponent()->SetLightColor(SunColor);
            UE_LOG(LogTemp, Log, TEXT("Created new directional light"));
        }
    }

    if (!SunLight)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find or create directional light!"));
    }
}

void ASunController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SunLight && SunLight->GetLightComponent())
    {
        // Smoothly rotate the sun
        FRotator NewRotation = SunLight->GetActorRotation();
        NewRotation.Pitch += RotationSpeed * DeltaTime;
        
        // Normalize the rotation
        NewRotation.Normalize();
        SunLight->SetActorRotation(NewRotation);

        // Optional: Update color based on time of day
        float TimeOfDay = FMath::Fmod(NewRotation.Pitch, 360.0f) / 360.0f;
        FLinearColor NewColor = FMath::Lerp(SunColor, FLinearColor(1.0f, 0.5f, 0.3f, 1.0f), TimeOfDay);
        SunLight->GetLightComponent()->SetLightColor(NewColor);
    }
}