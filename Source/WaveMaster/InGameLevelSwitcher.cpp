// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameLevelSwitcher.h"

AInGameLevelSwitcher * AInGameLevelSwitcher::Instance;


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

	CurrSessionGeometryList = GeometryList;

	// if (CurrentGeometry != nullptr)
	// {
	// 	TriggerLevelSwitch();
	// }
}

// Called every frame
void AInGameLevelSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInGameLevelSwitcher::BeginDestroy()
{
	Instance = nullptr;
	Super::BeginDestroy();
}


void AInGameLevelSwitcher::TriggerLevelSwitch()
{
	DestroyOldGeometry();
	CreateNewGeometry();
}

AWMLevelGeometry* AInGameLevelSwitcher::GetCurrentGeometry()
{
	return CurrentGeometry;
}

void AInGameLevelSwitcher::UpdateSession()
{
	CurrSessionGeometryList = GeometryList;

	TriggerLevelSwitch();
}

void AInGameLevelSwitcher::DestroyOldGeometry()
{
	if (CurrentGeometry == nullptr)
		return;
	
	CurrentGeometry->Destroy();
	CurrentGeometry = nullptr;
}

void AInGameLevelSwitcher::CreateNewGeometry()
{
	if (CurrSessionGeometryList.IsEmpty())
		return;

	FActorSpawnParameters Params;
	Params.Owner = nullptr;
	Params.Instigator = GetInstigator();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector Position = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	
	CurrentGeometry = GetWorld()->SpawnActor<AWMLevelGeometry>(
			CurrSessionGeometryList[0],
			Position,
			Rotation,
			Params
		);
	CurrSessionGeometryList.RemoveAt(0);
	CurrentGeometry->SetOwner(this);
}
