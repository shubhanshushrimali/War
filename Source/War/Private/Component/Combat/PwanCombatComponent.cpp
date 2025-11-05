// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/PwanCombatComponent.h"
#include "Items/Weapons/WarWeaponBase.h"
#include "Components/BoxComponent.h"
#include "WarDebugHelper.h"

void UPwanCombatComponent::RegisterSpwanedWeapon(FGameplayTag InWeaponTagTopRegister, AWarWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharcterCarriedWeaponsMap.Contains(InWeaponTagTopRegister), TEXT("A named %s has already been regidtred "), *InWeaponTagTopRegister.ToString()); 
	check(InWeaponToRegister);

	CharcterCarriedWeaponsMap.Emplace(InWeaponTagTopRegister, InWeaponToRegister);


	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnPulledFromTargetActor);

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

void UPwanCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWarWeaponBase* WeapontoToggle = GetCharacterCurrentEquippedWeapon();
		check(WeapontoToggle);
		
		if (bShouldEnable)
		{
			WeapontoToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			
		}
		else
		{
			WeapontoToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActorsDuringAttack.Empty();
		}
	}
}

void UPwanCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPwanCombatComponent::OnPulledFromTargetActor(AActor* InteractedActor)
{
}
