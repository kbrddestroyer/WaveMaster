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
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bDoCollisionTest = false; 
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->SetActive(true);
}

// Called when the game starts or when spawned
void AWMLevelGeometry::BeginPlay()
{
	Super::BeginPlay();

	AAMainCharacterBase* MainPlayer = Cast<AAMainCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MainPlayer->SetActorLocation(PlayerStartPoint->GetComponentLocation());
	FRotator NewPlayerRotation = FRotator(
		MainPlayer->GetActorRotation().Pitch,
		CameraComp->GetComponentRotation().Yaw,
		CameraComp->GetComponentRotation().Roll
		);
	MainPlayer->SetActorRotation(NewPlayerRotation);
	
	APlayerController* MainPlayerController = Cast<APlayerController>(MainPlayer->GetController());
	if (MainPlayerController != nullptr)
	{
		FViewTargetTransitionParams Params = FViewTargetTransitionParams();
		MainPlayerController->SetViewTarget(this, FViewTargetTransitionParams());	
	}

	if (EnemyClass != nullptr)
	{
		EnemyEntity = GetWorld()->SpawnActor<AWMEnemy>(EnemyClass, EnemySpawnPoint->GetComponentTransform());
	}
	
	LevelSwitchVolume->OnComponentBeginOverlap.AddDynamic(this, &AWMLevelGeometry::OnSwitcherOverlapBegin);
}

void AWMLevelGeometry::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EnemyEntity != nullptr) EnemyEntity->Destroy();
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

