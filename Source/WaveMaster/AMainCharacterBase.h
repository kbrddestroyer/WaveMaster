// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"

#include "AMainCharacterBase.generated.h"


class UWMSimonActorComponent;

/**
*  Just a base class for player that implements controls (movement) logics
*
*  @property MovementInputAction 
*/
UCLASS()
class WAVEMASTER_API AAMainCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAMainCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual  void PossessedBy(AController* NewController) override;

	void AddInteractableInSight(AActor* Interactable);

	void RemoveInteractableInSight(AActor* Interactable);

	UFUNCTION(BlueprintCallable)
	UWMSimonActorComponent* GetWMSimonActorComponent() const;

	void SetInputEnabled(bool bEnable);

	UFUNCTION(BlueprintCallable)
	UWMSimonActorComponent* GetSimonComponent() const;
	
protected:
	virtual void Move( const FInputActionValue& Value );

	void Interact(const FInputActionValue& Value);
	
	void PauseMenuCall(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void PauseMenuCallback();

	UFUNCTION(BlueprintCallable)
	void SetMouseCursorVisible(bool bVisible);
	
	int32 GetNextInteractableID() const;
	
	int32 CurrentInteractableID = 0;

	TArray<AActor*> InteractablesInSight;
	
	// Input Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input/Input Actions")
	UInputMappingContext* InputMappingContext;
	
	// Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input/Input Actions")
	UInputAction * MovementInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input/Input Actions")
	UInputAction * InteractionInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input/Input Actions")
	UInputAction * PauseMenuCallInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UWMSimonActorComponent * SimonSaysControllerComponent;
};