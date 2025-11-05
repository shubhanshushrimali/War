// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/PwanCombatComponent.h"
#include "HeroCombatComponent.generated.h"

/**
 * 
 */

class AWarHeroWeapon;




UCLASS()
class WAR_API UHeroCombatComponent : public UPwanCombatComponent
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "War|Combat")
	AWarHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "War|Combat")
	AWarHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "War|Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnPulledFromTargetActor(AActor* InteractedActor) override;
};
