// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SimonActionID.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WAVEMASTER_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float) override;
protected:
	UPROPERTY()
	APawn *owningPawn;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float fSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float fRotationAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isInSimonMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<SimonActionID> currentActionId;
};
