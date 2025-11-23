// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMainCharacterBase.h"
#include "WMSimonActorComponent.h"
#include "WMEnemy.generated.h"

class USphereComponent;

UCLASS()
class WAVEMASTER_API AWMEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWMEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void FindCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collision")
	USphereComponent* ActivationSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TSubclassOf<AAMainCharacterBase> PlayerCharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UWMSimonActorComponent* SimonActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actions")
	int32 ActionsNumber = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actions")
	int32 SequenceLength = 600;

	UWMSimonActorComponent* PlayerSimonComponent;
	
	AAMainCharacterBase* CharacterObjectRef;
	
	UFUNCTION()
	void OnSphereOverlapBegin(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
		);

	void SetupSimonActions();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
