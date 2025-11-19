// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMainCharacterBase.h"
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

	void FindCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collision")
	USphereComponent* ActivationSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TSubclassOf<AAMainCharacterBase> PlayerCharacterClass;

	AAMainCharacterBase* CharacterObjectRef;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
