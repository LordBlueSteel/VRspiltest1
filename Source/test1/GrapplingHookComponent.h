#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrapplingHookComponent.generated.h"

// Forward declaration is OK here
class UCableComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST1_API UGrapplingHookComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
    UGrapplingHookComponent();

    UFUNCTION(BlueprintCallable, Category="Grappling")
    void FireHook(FVector StartLocation, FVector Direction);

    UFUNCTION(BlueprintCallable, Category="Grappling")
    void ReleaseHook();

    UFUNCTION(BlueprintCallable, Category="Grappling")
    void Pull();

protected:
    virtual void BeginPlay() override;

private:
    void AttachHook(const FHitResult& Hit);

    UPROPERTY()
    AActor* HookedActor;

    UPROPERTY()
    UCableComponent* Cable;  // ✅ Proper declaration inside class

    UPROPERTY()
    USceneComponent* OwnerRoot;

    FVector HookPoint;
    bool bIsHooked;

    UPROPERTY(EditDefaultsOnly, Category="Grappling")
    float MaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, Category="Grappling")
    float PullStrength = 1000.0f;

    FTimerHandle PullTimerHandle;
};
