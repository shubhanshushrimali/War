// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarGameplayTags.h"


#include "WarDebugHelper.h"	

AWarHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return  Cast<AWarHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));

}

AWarHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast <AWarHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActorsDuringAttack.Contains(HitActor))
	{
		return; 
	}
	OverlappedActorsDuringAttack.AddUnique(HitActor);


	FGameplayEventData Data; 
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;


	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WarGameplayTags::Shared_Event_MeleeHit,
		Data
	);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WarGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
		); 
}

void UHeroCombatComponent::OnPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WarGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}
