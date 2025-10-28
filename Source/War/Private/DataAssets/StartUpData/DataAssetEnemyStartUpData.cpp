// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAssetEnemyStartUpData.h"
#include "Component/Combat/EnemyCombatComponent.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarEnemyGameplayAbility.h"

void UDataAssetEnemyStartUpData::GiveToAbilitySystemComponent(UWarAbilitySystemComponent* InWarASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InWarASCToGive, ApplyLevel); 


	if (!EnemyCombactAbilities.IsEmpty())
	{
		for (const TSubclassOf <UWarEnemyGameplayAbility>& AbilityClass : EnemyCombactAbilities)
		{
			if (!AbilityClass) continue; 

			FGameplayAbilitySpec AbilitySpec(AbilityClass);	
			AbilitySpec.SourceObject = InWarASCToGive->GetAvatarActor();	
			AbilitySpec.Level = ApplyLevel;


			InWarASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
