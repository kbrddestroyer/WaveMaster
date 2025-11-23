// Fill out your copyright notice in the Description page of Project Settings.


#include "WMSimonActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InGameLevelSwitcher.h"
#include "WMSimonAction.h"

// Sets default values for this component's properties
UWMSimonActorComponent::UWMSimonActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWMSimonActorComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningActor = GetOwner();
	
	if (LevelSwitcherClass == nullptr) return;
	
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), LevelSwitcherClass, OutActors);

	if (!OutActors.IsEmpty())
	{
		LevelSwitcher = Cast<AInGameLevelSwitcher>(OutActors[0]);
	}
}


// Called every frame
void UWMSimonActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isSequenceStarted)
	{
		if (CurrentSequenceTime >= MaxSequenceTime)
		{
			// Fail
			
			StopSimonSequence();

			// Switch to first level here
		}
		CurrentSequenceTime += DeltaTime;
	}
	
}

bool UWMSimonActorComponent::CheckPerformedAction(uint8 ActionID)
{
	if (! isSequenceStarted) return false;
	
	if (ActionID == ActionsToCheck[0]->GetActionID())
	{
		ActionsToCheck.RemoveAt(0);
		if (ActionsToCheck.IsEmpty())
		{
			LevelSwitcher->GetCurrentGeometry()->RemoveEnemy();
		}
		
		return true;
	}
	// Fail
	StopSimonSequence();

	// Switch to first level here
	
	return false;
}

void UWMSimonActorComponent::PerformAction(UWMSimonAction* Action)
{
	if (isEnemyComponent)
	{
		Action->PerformEnemyAction(OwningActor);
	}
	else
	{
		Action->PerformPlayerAction(OwningActor);
	}
}

void UWMSimonActorComponent::SetIsEnemyComponent(bool bIsEnemy)
{
	isEnemyComponent = bIsEnemy;
}

TArray<UWMSimonAction*> UWMSimonActorComponent::PerformActionsFromList()
{
	if (ActionList.IsEmpty()) return ActionList;
	TArray<UWMSimonAction*> OutActions;

	while (!ActionList.IsEmpty())
	{
		if (ActionList[0] == nullptr) break;
		UWMSimonAction* Action = ActionList[0];
		ActionList.RemoveAt(0);

		PerformAction(Action);
		
		OutActions.Add(Action);
	}
	
	return OutActions;
}

void UWMSimonActorComponent::ReceiveActionsToCheck(TArray<UWMSimonAction*> OutActionsToCheck)
{
	ActionsToCheck = OutActionsToCheck;
}

void UWMSimonActorComponent::StartSimonSequence(float NewMaxSequenceTime)
{
	 // Enable time check
	isSequenceStarted = true;
	MaxSequenceTime = NewMaxSequenceTime;
}

void UWMSimonActorComponent::StopSimonSequence()
{
	isSequenceStarted = false;
	CurrentSequenceTime = 0;
	MaxSequenceTime = 0;
}

void UWMSimonActorComponent::AddActionToList(UWMSimonAction* Action)
{
	ActionList.Add(Action);
}



