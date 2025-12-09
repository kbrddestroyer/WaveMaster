#include "WMGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "WMSimonAction.h"

void AWMGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (SimonActions.IsEmpty())
	{
		SetupActionInstances();
	}

	AActor* OutActor = UGameplayStatics::GetActorOfClass(GetWorld(), AInGameLevelSwitcher::StaticClass());
	InGameLevelSwitcher = Cast<AInGameLevelSwitcher>(OutActor);
}

TArray<UWMSimonAction*> AWMGameMode::GetAllSimonActions()
{
	if (SimonActions.IsEmpty())
	{
		SetupActionInstances();
	}
	
	return SimonActions;
}

void AWMGameMode::ChangeLevel()
{
	if (InGameLevelSwitcher != nullptr)
	{
		InGameLevelSwitcher->TriggerLevelSwitch();
	}
}

void AWMGameMode::SetupActionInstances()
{
	if (SimonActionClasses.IsEmpty()) return;
	for (int i = 0; i < SimonActionClasses.Num(); i++)
	{
		UWMSimonAction* Action = NewObject<UWMSimonAction>(GetTransientPackage(), SimonActionClasses[i]);
		Action->SetActionID(i);
		SimonActions.Add(Action);
	}
}
