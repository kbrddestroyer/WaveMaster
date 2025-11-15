// Fill out your copyright notice in the Description page of Project Settings.


#include "SimonController.h"

SimonController* SimonController::GetInstance()
{
	static SimonController Instance;
	return &Instance;
}


void SimonController::AddActionInCheckQueue(const SimonActionID Action)
{
	qActionsToCheck.push(Action);
}

bool SimonController::CheckPerformedAction(const SimonActionID Action, const float PerformTime)
{
	// 1. Calculate delta time with prev. time

	if (const float DeltaTime = PerformTime - LastTriggerTime; DeltaTime < 0 && DeltaTime * 1000 > MAX_TIME)
	{
		return false;
	}

	// 2. Set new LastTriggerTime
	LastTriggerTime = PerformTime;

	// 3. Check action
	if (Action == qActionsToCheck.back())
	{
		qActionsToCheck.pop();
		return true;
	}
	return false;
}
