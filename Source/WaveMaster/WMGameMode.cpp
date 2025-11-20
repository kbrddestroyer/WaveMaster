// Fill out your copyright notice in the Description page of Project Settings.


#include "WMGameMode.h"
#include "WMSimonAction.h"

void AWMGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (SimonActionClasses.IsEmpty()) return;
	for (int i = 0; i < SimonActionClasses.Num(); i++)
	{
		UWMSimonAction* Action = NewObject<UWMSimonAction>(GetTransientPackage(), SimonActionClasses[i]);
		Action->SetActionID(i);
		SimonActions.Add(Action);
	}
}

TArray<UWMSimonAction*> AWMGameMode::GetAllSimonActions()
{
	return SimonActions;
}
