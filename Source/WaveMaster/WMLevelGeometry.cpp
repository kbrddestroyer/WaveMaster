// Fill out your copyright notice in the Description page of Project Settings.


#include "WMLevelGeometry.h"

// Sets default values
AWMLevelGeometry::AWMLevelGeometry()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemySpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawnPoint"));
	EnemySpawnPoint->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AWMLevelGeometry::BeginPlay()
{
	Super::BeginPlay();

	EnemyEntity = GetWorld()->SpawnActor<AWMEnemy>(EnemyClass, EnemySpawnPoint->GetComponentTransform());
}

// Called every frame
void AWMLevelGeometry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWMLevelGeometry::RemoveEnemy()
{
	if (EnemyEntity != nullptr)
	{
		EnemyEntity->Destroy();
		EnemyEntity = nullptr;
	}
}

