// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarGameplayAbility.h"
#include "WarEnemyGameplayAbility.generated.h"


class AWarEnemyCharacter; 
class UEnemyCombatComponent; 


/**
 * 
 */
UCLASS()
class WAR_API UWarEnemyGameplayAbility : public UWarGameplayAbility
{
	GENERATED_BODY()
	

public: 
	UFUNCTION(BlueprintPure, Category = "War|Ability")
	AWarEnemyCharacter* GetEnemyCharacterFromActorInfo() ;

	UFUNCTION(BlueprintPure, Category = "War|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AWarEnemyCharacter> ChachedWarEnemyCharcter; 

};
