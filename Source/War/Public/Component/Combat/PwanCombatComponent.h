// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PwanCombatComponent.generated.h"

class AWarWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
   CurrentEquippedWeapon,
   LeftHandWeapon,
   RightHandWeapon
};


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
	
	UFUNCTION(BlueprintCallable, Category = "War|Combat")
	void ToggleWeaponCollision(bool bShouldEnable , EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnPulledFromTargetActor(AActor* InteractedActor);

protected:
	TArray<AActor*> OverlappedActorsDuringAttack;






private:
	TMap<FGameplayTag, AWarWeaponBase*> CharcterCarriedWeaponsMap;
};
