// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarHeroWeapon.h"

AWarHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return  Cast<AWarHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));

}
