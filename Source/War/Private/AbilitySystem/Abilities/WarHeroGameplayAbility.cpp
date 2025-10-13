// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarHeroGameplayAbility.h"
#include "Character/WarHeroCharacter.h"
#include "Controller/WarCharacterController.h"


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
