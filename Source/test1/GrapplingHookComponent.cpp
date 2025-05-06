#include "GrapplingHookComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "CableComponent.h"

UGrapplingHookComponent::UGrapplingHookComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UGrapplingHookComponent::BeginPlay()
{
    Super::BeginPlay();

    OwnerRoot = GetOwner()->GetRootComponent();

    // Optional: create cable at runtime
    Cable = NewObject<UCableComponent>(GetOwner());
    if (Cable)
    {
        Cable->RegisterComponent();
        Cable->AttachToComponent(OwnerRoot, FAttachmentTransformRules::KeepRelativeTransform);
        Cable->SetVisibility(false);
    }
}

void UGrapplingHookComponent::FireHook(FVector StartLocation, FVector Direction)
{
    if (bIsHooked) return;

    FHitResult Hit;
    FVector End = StartLocation + Direction * MaxDistance;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, End, ECC_Visibility, Params);

    if (bHit)
    {
        AttachHook(Hit);
    }

    if (Cable)
    {
        Cable->SetVisibility(true);
        Cable->SetAttachEndTo(nullptr, NAME_None); // Free-floating end
        Cable->EndLocation = Hit.Location - StartLocation;
    }
}

void UGrapplingHookComponent::AttachHook(const FHitResult& Hit)
{
    HookedActor = Hit.GetActor();
    HookPoint = Hit.Location;
    bIsHooked = true;

    if (Cable)
    {
        Cable->EndLocation = HookPoint - OwnerRoot->GetComponentLocation();
    }
}

void UGrapplingHookComponent::ReleaseHook()
{
    bIsHooked = false;
    HookedActor = nullptr;
    HookPoint = FVector::ZeroVector;

    if (Cable)
    {
        Cable->SetVisibility(false);
    }

    GetWorld()->GetTimerManager().ClearTimer(PullTimerHandle);
}

void UGrapplingHookComponent::Pull()
{
    if (!bIsHooked || !OwnerRoot) return;

    FVector Direction = (HookPoint - OwnerRoot->GetComponentLocation()).GetSafeNormal();

    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
    if (OwnerChar)
    {
        OwnerChar->LaunchCharacter(Direction * PullStrength, true, true);
    }

    // You can also interpolate manually or use AddForce if Rigidbody/Physics-based movement
}
