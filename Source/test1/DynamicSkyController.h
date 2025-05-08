#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicSkyController.generated.h"

// Forward declarations for UE4.27
class ASkyAtmosphere;
class AVolumetricCloud;
class AExponentialHeightFog;

UCLASS()
class TEST1_API ADynamicSkyController : public AActor
{
	GENERATED_BODY()

public:
	ADynamicSkyController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Sky Settings")
	AActor* SkyAtmosphere;

	UPROPERTY(EditAnywhere, Category = "Sky Settings")
	AActor* VolumetricCloud;

	UPROPERTY(EditAnywhere, Category = "Sky Settings")
	AActor* HeightFog;

private:
	void SpawnMissingSkyComponents();
};