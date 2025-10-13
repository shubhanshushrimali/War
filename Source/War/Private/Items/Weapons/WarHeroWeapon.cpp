// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WarHeroWeapon.h"
#include "GameplayAbilitySpecHandle.h"

void AWarHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InGrantedAbilitySpecHandles)
{
	GrantedAbilitySpecHandles = InGrantedAbilitySpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AWarHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
