// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "AbilitySystem/Abilities/WarHeroGameplayAbility.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"

bool FWarHeroAbliltySet::IsValid() const
{
	
		return InputTag.IsValid() && AbilityToGrant;
	
}

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWarAbilitySystemComponent* InWarASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InWarASCToGive, ApplyLevel);

	for (const FWarHeroAbliltySet& HeroAbilitySet : HeroStartUpAbiliySets)
	{
		if (!HeroAbilitySet.IsValid()) { continue; }
		

		FGameplayAbilitySpec AbilitySpec(HeroAbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InWarASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(HeroAbilitySet.InputTag);
		InWarASCToGive->GiveAbility(AbilitySpec); 
		
	}
}
