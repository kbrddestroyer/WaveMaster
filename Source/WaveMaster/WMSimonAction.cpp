// Fill out your copyright notice in the Description page of Project Settings.


#include "WMSimonAction.h"

void UWMSimonAction::SetActionID(uint8 actionID)
{
	ActionID = actionID;
}

uint8 UWMSimonAction::GetActionID()
{
	return ActionID;
}
