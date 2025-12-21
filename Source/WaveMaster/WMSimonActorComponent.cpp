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

	if (isSequenceStarted && MaxSequenceTime > 0)
	{
		if (CurrentSequenceTime >= MaxSequenceTime)
		{
			// Fail
			StopSimonSequence();
			LevelSwitcher->UpdateSession();
			GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, "Fail no time");
			return;
		}
		CurrentSequenceTime += DeltaTime;
	}
	
}

bool UWMSimonActorComponent::CheckPerformedAction(uint8 ActionID)
{
	if (! isSequenceStarted) return false;
	
	if (ActionID == ActionsToCheck.Last()->GetActionID())
	{
		ActionsToCheck.Pop();
		if (ActionsToCheck.IsEmpty())
		{
			// Success
			GEngine->AddOnScreenDebugMessage(-1, MaxSequenceTime, FColor::Green, "Success");
			StopSimonSequence();
			LevelSwitcher->GetCurrentGeometry()->RemoveEnemy();
		}
		
		return true;
	}
	// Fail
	StopSimonSequence();
	LevelSwitcher->UpdateSession();
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, "Fail wrong action");
	
	return false;
}

void UWMSimonActorComponent::PerformAction(UWMSimonAction* Action)
{
	if (OwningActor == nullptr) return;
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
		UWMSimonAction* Action = ActionList.Last();
		ActionList.Pop();

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

	/* ---Only for debug purposes--- 

	if (isSendDebugActionSequence)
	{
		TArray<UWMSimonAction*> FuckingActions = ActionsToCheck;
	
		for (int i = 0; i < FuckingActions.Num(); i++)
		{
			if (i == FuckingActions.Num() - 1 && isSendWrongAction)
			{
				CheckPerformedAction(99);
			}
			else
			{
				PerformAction(FuckingActions[i]);
				CheckPerformedAction(FuckingActions[i]->GetActionID());
			}
			
		}
	}
	 ---Only for debug purposes--- */
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



