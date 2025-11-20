// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WMSimonAction.generated.h"


UCLASS(Blueprintable)
class WAVEMASTER_API UWMSimonAction : public UObject
{
	GENERATED_BODY()

protected:
	
	uint8 ActionID;
	
public:

	UFUNCTION(BlueprintCallable)
	void SetActionID(uint8 actionID);

	UFUNCTION(BlueprintCallable)
	uint8 GetActionID();

	UFUNCTION(BlueprintImplementableEvent)
	void PerformEnemyAction(AActor* TargetEnemy);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PerformPlayerAction(AActor* TargetPlayer);
};
