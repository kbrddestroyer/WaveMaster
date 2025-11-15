// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <queue>


enum SimonActionID
{
	// Action IDs
	DEFAULT,
};

/**
 * Low level shit for Simon implementation
 *
 * Falls to C++ API
 */
class WAVEMASTER_API SimonController
{
	const UINT8 MAX_TIME = 500;  // ms
	
private:
	// Only GetInstance() function should be able to construct this class
	SimonController() = default;
public:
	~SimonController() = default;
	
	static SimonController * GetInstance();

	void AddActionInCheckQueue(SimonActionID);
	bool CheckPerformedAction(SimonActionID, float);
private:
	std::queue<const SimonActionID> qActionsToCheck;
	float LastTriggerTime = 0;
};
