// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarAbilitySystemComponent.h"

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
