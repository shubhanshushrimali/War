// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PwanCombatComponent.generated.h"

class AWarWeaponBase;
/**
 * 
 */
UCLASS()
class WAR_API UPwanCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "War|Combat")
	void RegisterSpwanedWeapon(FGameplayTag InWeaponTagTopRegister, AWarWeaponBase* InWeaponToRegister , bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "War|Combat")
	AWarWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "War|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "War|Combat")
	AWarWeaponBase* GetCharacterCurrentEquippedWeapon() const; 
	

private:
	TMap<FGameplayTag, AWarWeaponBase*> CharcterCarriedWeaponsMap;
};
