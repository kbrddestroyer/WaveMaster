// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WMSimonActorComponent.generated.h"

class UWMSimonAction;
class AInGameLevelSwitcher;

// UENUM(BlueprintType)
// enum class SimonActionID: uint8
// {
// 	// Action IDs
// 	DEFAULT UMETA(DisplayName = "Action ID"),
// };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WAVEMASTER_API UWMSimonActorComponent : public UActorComponent
{
	GENERATED_BODY()
	
	const uint32 MAX_TIME = 500;

public:	
	// Sets default values for this component's properties
	UWMSimonActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	TArray<uint8> qActionsToCheck;
	float LastTriggerTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actions")
	float isEnemyComponent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control entities")
	TSubclassOf<AInGameLevelSwitcher> LevelSwitcherClass;

	AActor* OwningActor;
	
	AInGameLevelSwitcher* LevelSwitcher;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddActionInCheckQueue(uint8 ActionID);
	bool CheckPerformedAction(uint8 ActionID, float PerformTime);

	UFUNCTION(BlueprintCallable)
	void PerformAction(UWMSimonAction* Action);
};
