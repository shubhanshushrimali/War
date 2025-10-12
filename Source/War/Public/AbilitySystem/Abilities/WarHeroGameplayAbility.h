// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarGameplayAbility.h"
#include "WarHeroGameplayAbility.generated.h"

/**
 * 
 */

class AWarHeroCharacter; 
class AWarCharacterController; 
class UHeroCombatComponent; 

UCLASS()
class WAR_API UWarHeroGameplayAbility : public UWarGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "War|Ability")
	AWarHeroCharacter* GetHeroCharacterFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "War|Ability")
	AWarCharacterController* GetHeroControllerFromActorInfo() const; 

	UFUNCTION(BlueprintPure, Category = "War|Ability")
	UHeroCombatComponent* GetHeroCombatFromActorInfo() const;
	

private :
	TWeakObjectPtr<AWarHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<AWarCharacterController> CachedHeroController;
};
