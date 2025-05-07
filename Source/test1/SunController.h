#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SunController.generated.h"

UCLASS()
class TEST1_API ASunController : public AActor
{
    GENERATED_BODY()
    
public:
    ASunController();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Sun Settings")
    float RotationSpeed = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Sun Settings")
    float Intensity = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Sun Settings")
    FLinearColor SunColor = FLinearColor::White;

private:
    UPROPERTY()
    class ADirectionalLight* SunLight = nullptr; // Initialize to nullptr
};