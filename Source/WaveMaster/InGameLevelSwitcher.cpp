// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameLevelSwitcher.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInGameLevelSwitcher::AInGameLevelSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInGameLevelSwitcher::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInGameLevelSwitcher::Tick(float DeltaTime)
{
	static float CompleteTime = 0;
	static bool ShouldTriggerSwitch = true;
	
	Super::Tick(DeltaTime);
	CompleteTime += DeltaTime;

	if (CompleteTime >= 10 && ShouldTriggerSwitch)
	{
		TriggerLevelSwitch();
		ShouldTriggerSwitch = false;
	}
}

void AInGameLevelSwitcher::TriggerLevelSwitch() const
{
	UGameplayStatics::OpenLevel(
		this, NextLevelName
	);
}
