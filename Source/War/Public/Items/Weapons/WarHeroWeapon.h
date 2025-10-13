// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WarWeaponBase.h"
#include "WarTypes/WarStructTypes.h"
#include "WarHeroWeapon.generated.h"

/**
 * 
 */


struct FGameplayAbilitySpecHandle;

UCLASS()
class WAR_API AWarHeroWeapon : public AWarWeaponBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarHeroWeaponData HeroWeaponData;	

	UFUNCTION(BlueprintCallable, Category = "War|Weapon")
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "War|Weapon")
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
private:
	
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
