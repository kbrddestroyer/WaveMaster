// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "WMBaseInteractable.generated.h"

UCLASS()
class WAVEMASTER_API AWMBaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWMBaseInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collision")
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance")
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void OnSphereOverlapBegin(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
		);

	UFUNCTION()
	void OnSphereOverlapEnd(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Interactable")
	void Interact();

	UFUNCTION(BlueprintImplementableEvent, Category = "Interactable")
	void StartInteractionSignalization();

	UFUNCTION(BlueprintImplementableEvent, Category = "Interactable")
	void StopInteractionSignalization();
};
