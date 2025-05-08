#include "GreyFogController.h"

AGreyFogController::AGreyFogController()
{
	PrimaryActorTick.bCanEverTick = false;

	FogComponent = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("FogComponent"));
	RootComponent = FogComponent;

	// Set default values
	FogComponent->SetFogDensity(FogDensity);
	FogComponent->SetFogInscatteringColor(FogColor);
}

void AGreyFogController::SetFogIntensity(float NewDensity)
{
	FogDensity = NewDensity;
	FogComponent->SetFogDensity(FogDensity);
}

