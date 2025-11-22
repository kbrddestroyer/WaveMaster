// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	owningPawn = TryGetPawnOwner();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float x)
{
	Super::NativeUpdateAnimation(x);

	if (!owningPawn)
		return;

	fSpeed = owningPawn->GetVelocity().Size();
	fRotationAngle = owningPawn->GetVelocity().Rotation().Pitch;
}
