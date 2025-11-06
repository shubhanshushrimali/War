// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnUIInterface.h"
#include "Component/UI/PawnUIComponent.h"
#include "Component/UI/HeroUIComponent.h"
#include "Component/UI/EnemyUIComponent.h"
// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.

UHeroUIComponent* IPawnUIInterface::GetHeroUIComponent() const
{
	return nullptr;
}

UEnemyUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
