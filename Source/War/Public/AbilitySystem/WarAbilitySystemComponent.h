// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarTypes/WarStructTypes.h"
#include "WarAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class WAR_API UWarAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	

public: 
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "War|Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FWarHeroAbliltySet>& InDefaultWeaponAbilities,int32 ApplyLevel , TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle);

	UFUNCTION(BlueprintCallable, Category = "War|Ability")
	void RemoveGrantHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
};
