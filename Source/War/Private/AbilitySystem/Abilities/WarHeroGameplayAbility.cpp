// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarHeroGameplayAbility.h"
#include "Character/WarHeroCharacter.h"
#include "Controller/WarCharacterController.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "WarGameplayTags.h"

AWarHeroCharacter* UWarHeroGameplayAbility::GetHeroCharacterFromActorInfo() const
{
	if (!CachedHeroCharacter.IsValid())
	{
		CachedHeroCharacter = Cast<AWarHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;	
	
}

AWarCharacterController* UWarHeroGameplayAbility::GetHeroControllerFromActorInfo() const
{
	if (!CachedHeroController.IsValid())
	{
		CachedHeroController = Cast<AWarCharacterController>(CurrentActorInfo->PlayerController);

	}

	return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarHeroGameplayAbility::GetHeroCombatFromActorInfo() const
{
	const AWarHeroCharacter* HeroCharacter = GetHeroCharacterFromActorInfo();
	return HeroCharacter ? HeroCharacter->GetHeroCombatComponent() : nullptr;
}

FGameplayEffectSpecHandle UWarHeroGameplayAbility::MakeHeroEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount)
{
	check(EffectClass); 


	FGameplayEffectContextHandle  ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetWarAbilitySystemComponentFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());	

	FGameplayEffectSpecHandle EffectSpecHandle = GetWarAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(

		EffectClass,
		GetAbilityLevel(),
		ContextHandle

	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(WarGameplayTags::Shared_SetByCaller_BaseDamage , InWeaponDamage);


	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag , InCurrentComboCount);
	}






	return EffectSpecHandle;
}
