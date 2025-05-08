#include "DynamicSkyController.h"
#include "Engine/Classes/GameFramework/Actor.h"

// UE4.27 compatible spawn method
void ADynamicSkyController::SpawnMissingSkyComponents()
{
	if (!SkyAtmosphere)
	{
		SkyAtmosphere = GetWorld()->SpawnActor(AActor::StaticClass());
		// Manually add sky component in Blueprints later
	}

	if (!VolumetricCloud)
	{
		VolumetricCloud = GetWorld()->SpawnActor(AActor::StaticClass());
	}

	if (!HeightFog)
	{
		HeightFog = GetWorld()->SpawnActor(AActor::StaticClass());
	}
}

ADynamicSkyController::ADynamicSkyController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADynamicSkyController::BeginPlay()
{
	Super::BeginPlay();
	SpawnMissingSkyComponents();
}