// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarHeroGameplayAbility.h"

void UWarAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue; 
		
			TryActivateAbility(AbilitySpec.Handle);
			
 }
}

void UWarAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
}

void UWarAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FWarHeroAbliltySet>& InDefaultWeaponAbilities, int32 ApplyLevel , TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle)
{
	if (InDefaultWeaponAbilities.IsEmpty()) { return; }

	for (const FWarHeroAbliltySet& HeroAbilitySet : InDefaultWeaponAbilities)
	{
		if (!HeroAbilitySet.IsValid()) { continue; }

		FGameplayAbilitySpec AbilitySpec(HeroAbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(HeroAbilitySet.InputTag);
		

		OutGrantedAbilitySpecHandle.AddUnique(GiveAbility(AbilitySpec) );
	}
}

void UWarAbilitySystemComponent::RemoveGrantHeroWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{

	if (InSpecHandlesToRemove.IsEmpty()) { return; }

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);	
		}
		
	}	

	InSpecHandlesToRemove.Empty();
}




