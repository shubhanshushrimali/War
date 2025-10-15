// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/PwanCombatComponent.h"
#include "Items/Weapons/WarWeaponBase.h"
#include "WarDebugHelper.h"

void UPwanCombatComponent::RegisterSpwanedWeapon(FGameplayTag InWeaponTagTopRegister, AWarWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharcterCarriedWeaponsMap.Contains(InWeaponTagTopRegister), TEXT("A named %s has already been regidtred "), *InWeaponTagTopRegister.ToString()); 
	check(InWeaponToRegister);

	CharcterCarriedWeaponsMap.Emplace(InWeaponTagTopRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagTopRegister;
	}

}

AWarWeaponBase* UPwanCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharcterCarriedWeaponsMap.Contains(InWeaponTagToGet))
	{
		if (AWarWeaponBase* const* FoundWeapon = CharcterCarriedWeaponsMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}

	return nullptr; 
}


AWarWeaponBase* UPwanCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	else if (CurrentEquippedWeaponTag.IsValid())
	{
		return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
	}
	
	else
	{
		return nullptr;
	}
}
