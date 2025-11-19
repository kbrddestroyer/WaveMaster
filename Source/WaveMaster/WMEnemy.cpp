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
}

// Called when the game starts or when spawned
void AWMEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (CharacterObjectRef == nullptr)
	{
		FindCharacter();	
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

