// Fill out your copyright notice in the Description page of Project Settings.


#include "WMLevelGeometry.h"
#include "Kismet/GameplayStatics.h"
#include "AMainCharacterBase.h"
#include "InGameLevelSwitcher.h"

// Sets default values
AWMLevelGeometry::AWMLevelGeometry()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GeometryRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GeometryRoot"));
	SetRootComponent(GeometryRoot);
	
	EnemySpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawnPoint"));
	EnemySpawnPoint->SetupAttachment(RootComponent);

	PlayerStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerStartPoint"));
	PlayerStartPoint->SetupAttachment(RootComponent);
	
	LevelSwitchVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("LevelSwitchVolume"));
	LevelSwitchVolume->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWMLevelGeometry::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyClass != nullptr)
	{
		EnemyEntity = GetWorld()->SpawnActor<AWMEnemy>(EnemyClass, EnemySpawnPoint->GetComponentTransform());
	}

	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorTransform(PlayerStartPoint->GetComponentTransform());
	
	LevelSwitchVolume->OnComponentBeginOverlap.AddDynamic(this, &AWMLevelGeometry::OnSwitcherOverlapBegin);
}

void AWMLevelGeometry::OnSwitcherOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AAMainCharacterBase>(OtherActor) == nullptr) return;
	OwnerGeometrySwitcher->TriggerLevelSwitch();
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

void AWMLevelGeometry::SetOwner(AInGameLevelSwitcher* InOwner)
{
	OwnerGeometrySwitcher = InOwner;
}

