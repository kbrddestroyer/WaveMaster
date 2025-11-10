// Fill out your copyright notice in the Description page of Project Settings.


#include "AMainCharacterBase.h"
#include "EnhancedInputComponent.h"


// Sets default values
AAMainCharacterBase::AAMainCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAMainCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAMainCharacterBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAMainCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (
			UEnhancedInputComponent * enhancedInputComponent = Cast<UEnhancedInputComponent>( PlayerInputComponent )
			)
	{
		// Movement function is bind to movement controls, easy, right?
		enhancedInputComponent->BindAction(
			MovementInputAction,
			ETriggerEvent::Triggered,
			this,
			&AAMainCharacterBase::Move
		);
	}
}

void AAMainCharacterBase::Move(const FInputActionValue& Value)
{
	if (!Controller)
		return;

	const FVector2D inputValue2D = Value.Get<FVector2D>();

	if (inputValue2D == FVector2D::ZeroVector)
		return;

	const FRotator rotator = Controller->GetControlRotation();
	const FRotator yaw(0, rotator.Yaw, 0);

	const auto rotationMatrix = FRotationMatrix(yaw);

	const FVector forward = rotationMatrix.GetUnitAxis(EAxis::X);
	const FVector right = rotationMatrix.GetUnitAxis(EAxis::Y);

	AddMovementInput(forward, inputValue2D.Y);
	AddMovementInput(right, inputValue2D.X);
}


