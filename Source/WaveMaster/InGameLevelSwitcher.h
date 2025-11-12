// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InGameLevelSwitcher.generated.h"

UCLASS()
class WAVEMASTER_API AInGameLevelSwitcher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInGameLevelSwitcher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Function that triggers level switch
	 * Param NextLevelName should be set to valid value in editor!
	 */
	UFUNCTION()
	void TriggerLevelSwitch() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Switcher")
	FName NextLevelName;
};
