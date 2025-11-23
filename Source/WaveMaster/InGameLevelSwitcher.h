// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WMLevelGeometry.h"
#include "InGameLevelSwitcher.generated.h"

UCLASS()
class WAVEMASTER_API AInGameLevelSwitcher : public AActor
{
	GENERATED_BODY()

private:
	static AInGameLevelSwitcher * Instance;
	
public:	
	// Sets default values for this actor's properties
	AInGameLevelSwitcher();

	inline static AInGameLevelSwitcher * GetInstance() { return Instance; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;
	
	/**
	 * Function that triggers level switch
	 * Param NextLevelName should be set to valid value in editor!
	 */
	UFUNCTION()
	void TriggerLevelSwitch();

	AWMLevelGeometry* GetCurrentGeometry();

	void UpdateSession();
	
private:

	void DestroyOldGeometry();
	void CreateNewGeometry();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Switcher")
	TArray<TSubclassOf<AWMLevelGeometry>> GeometryList;
	
	TArray<TSubclassOf<AWMLevelGeometry>> CurrSessionGeometryList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Switcher")
	AWMLevelGeometry* CurrentGeometry;
};
