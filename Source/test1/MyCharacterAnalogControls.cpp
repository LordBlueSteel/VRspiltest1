#include "MyCharacterAnalogControls.h"

// Sets default values
AMyCharacterAnalogControls::AMyCharacterAnalogControls()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacterAnalogControls::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMyCharacterAnalogControls::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacterAnalogControls::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MotionControllerThumbLeft_X", this, &AMyCharacterAnalogControls::ThumbstickLeftX);
    PlayerInputComponent->BindAxis("MotionControllerThumbLeft_Y", this, &AMyCharacterAnalogControls::ThumbstickLeftY);
}

void AMyCharacterAnalogControls::ThumbstickLeftX(float Value)
{
    if (FMath::Abs(Value) > 0.1f) // Deadzone
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void AMyCharacterAnalogControls::ThumbstickLeftY(float Value)
{
    if (FMath::Abs(Value) > 0.1f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}
