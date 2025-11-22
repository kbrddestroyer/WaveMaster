// Fill out your copyright notice in the Description page of Project Settings.


#include "AMainCharacterBase.h"
#include "EnhancedInputComponent.h"
#include "WMBaseInteractable.h"
#include "WMSimonActorComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAMainCharacterBase::AAMainCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SimonSaysControllerComponent = CreateDefaultSubobject<UWMSimonActorComponent>(TEXT("SimonSaysController"));
}

// Called when the game starts or when spawned
void AAMainCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AAMainCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
    
	if (APlayerController* PlayerController = Cast<APlayerController>(NewController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 1);
		}
	}
}

void AAMainCharacterBase::AddInteractableInSight(AActor* Interactable)
{
	if (!InteractablesInSight.Contains(Interactable))
	{
		InteractablesInSight.Add(Interactable);
	}
}

void AAMainCharacterBase::RemoveInteractableInSight(AActor* Interactable)
{
	int32 RemovingID = InteractablesInSight.Find(Interactable);
	if (RemovingID != INDEX_NONE)
	{
		if (CurrentInteractableID >= RemovingID && CurrentInteractableID != 0)
		{
			CurrentInteractableID--;
		}
		InteractablesInSight.RemoveSingle(Interactable);
	}
}

UWMSimonActorComponent* AAMainCharacterBase::GetWMSimonActorComponent() const
{
	return SimonSaysControllerComponent;
}

void AAMainCharacterBase::SetInputEnabled(bool bEnable)
{
	if (bEnable)
	{
		EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));		
	}
	else
	{
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
}

UWMSimonActorComponent* AAMainCharacterBase::GetSimonComponent() const
{
	return SimonSaysControllerComponent;
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

	if (UEnhancedInputComponent * enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(
				MovementInputAction, ETriggerEvent::Triggered, this, &AAMainCharacterBase::Move
			);
		enhancedInputComponent->BindAction(
				InteractionInputAction, ETriggerEvent::Triggered, this, &AAMainCharacterBase::Interact
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

void AAMainCharacterBase::Interact(const FInputActionValue& Value)
{
	if (InteractablesInSight.IsEmpty()) return;
	AWMBaseInteractable* InteractableObject = Cast<AWMBaseInteractable>(InteractablesInSight[CurrentInteractableID]);

	if (InteractableObject == nullptr) return;
	InteractableObject->Interact();
	CurrentInteractableID = GetNextInteractableID();
}

int32 AAMainCharacterBase::GetNextInteractableID() const
{
	int32 nextInteractableID = CurrentInteractableID + 1;

	if (nextInteractableID >= InteractablesInSight.Num())
	{
		nextInteractableID = 0;
	}
	
	return nextInteractableID;
}


