// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarGameplayAbility.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "Component/Combat/PwanCombatComponent.h"

void UWarGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EWarAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWarGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EWarAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo )
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}

}

UPwanCombatComponent* UWarGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{

	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPwanCombatComponent>();


}

UWarAbilitySystemComponent* UWarGameplayAbility::GetWarAbilitySystemComponentFromActorInfo() const
{
	return Cast<UWarAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);

}
