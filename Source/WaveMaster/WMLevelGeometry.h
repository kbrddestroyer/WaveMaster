// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WMEnemy.h"
#include "WMBaseInteractable.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "WMLevelGeometry.generated.h"

class AInGameLevelSwitcher;

UCLASS()
class WAVEMASTER_API AWMLevelGeometry : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWMLevelGeometry();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns")
	TSubclassOf<AWMEnemy> EnemyClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry")
	USceneComponent* GeometryRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns")
	USceneComponent* EnemySpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns")
	USceneComponent* PlayerStartPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns")
	USceneComponent* InteractableSpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSwitch")
	UBoxComponent* LevelSwitchVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry")
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSwitch")
	AInGameLevelSwitcher* OwnerGeometrySwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns")
	TSubclassOf<AWMBaseInteractable> InteractableClass;
	
	AWMEnemy* EnemyEntity;

	AWMBaseInteractable* InteractableInstance;

	UFUNCTION()
	void OnSwitcherOverlapBegin(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawns")
	void RemoveEnemy();

	void SetOwner(AInGameLevelSwitcher* InOwner);
};
