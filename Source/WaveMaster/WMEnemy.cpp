// Fill out your copyright notice in the Description page of Project Settings.


#include "WMEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWMEnemy::AWMEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActivationSphere = CreateDefaultSubobject<USphereComponent>("ActivationSphere");
	ActivationSphere->SetupAttachment(GetRootComponent());

	SimonActorComponent = CreateDefaultSubobject<UWMSimonActorComponent>("SimonActorComponent");
	SimonActorComponent->SetIsEnemyComponent(true);
}

// Called when the game starts or when spawned
void AWMEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (CharacterObjectRef == nullptr)
	{
		FindCharacter();	
	}

	// Setup delegate callbacks
	ActivationSphere->OnComponentBeginOverlap.AddDynamic(this, &AWMEnemy::OnSphereOverlapBegin);
}

void AWMEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (CharacterObjectRef != nullptr)
	{
		CharacterObjectRef->SetInputEnabled(true);
		PlayerSimonComponent = nullptr;
	}
}

void AWMEnemy::FindCharacter()
{
	if (PlayerCharacterClass == nullptr) return;
	
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerCharacterClass, OutActors);

	if (!OutActors.IsEmpty())
	{
		CharacterObjectRef = Cast<AAMainCharacterBase>(OutActors[0]);
	}
}

// Called every frame
void AWMEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CharacterObjectRef != nullptr)
	{
		FVector StartLocation = GetActorLocation();
		auto StartPitchRotator = GetActorRotation().Pitch;
		
		FVector TargetLocation = CharacterObjectRef->GetActorLocation();
		
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

		SetActorRotation(FRotator(StartPitchRotator, LookAtRotation.Yaw, LookAtRotation.Roll));
	}
}


void AWMEnemy::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAMainCharacterBase* PlayerObj = Cast<AAMainCharacterBase>(OtherActor);
	if (PlayerObj == CharacterObjectRef)
	{
		CharacterObjectRef->SetInputEnabled(false);
		PlayerSimonComponent = PlayerObj->GetSimonComponent();

		TArray<UWMSimonAction*> ActionsToCheck = SimonActorComponent->PerformActionsFromList();
		PlayerSimonComponent->ReceiveActionsToCheck(ActionsToCheck);

		PlayerSimonComponent->StartSimonSequence();
	}
}