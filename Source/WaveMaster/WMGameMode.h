// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WMGameMode.generated.h"

class UWMSimonAction;

UCLASS()
class WAVEMASTER_API AWMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	TArray<UWMSimonAction*> GetAllSimonActions();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimonSays")
	TArray<TSubclassOf<UWMSimonAction>> SimonActionClasses;
	
	TArray<UWMSimonAction*> SimonActions;

	void SetupActionInstances();
};
