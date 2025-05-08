#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "GreyFogController.generated.h"

UCLASS()
class TEST1_API AGreyFogController : public AActor
{
	GENERATED_BODY()
    
public:
	AGreyFogController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UExponentialHeightFogComponent* FogComponent;

	// Editable fog settings
	UPROPERTY(EditAnywhere, Category="Fog Settings")
	float FogDensity = 0.02f;

	UPROPERTY(EditAnywhere, Category="Fog Settings")
	FLinearColor FogColor = FLinearColor(0.5f, 0.5f, 0.5f); // Default grey

	UFUNCTION(BlueprintCallable)
	void SetFogIntensity(float NewDensity);
};