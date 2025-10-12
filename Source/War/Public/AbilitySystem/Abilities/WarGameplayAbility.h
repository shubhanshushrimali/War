// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarGameplayAbility.generated.h"

class UWarAbilitySystemComponent; 
class UPwanCombatComponent;
UENUM(BlueprintType)
enum class EWarAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};
/**
 * 
 */
UCLASS()
class WAR_API UWarGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	

protected: 

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	UPROPERTY(EditDefaultsOnly, Category = "WarAbility")
	EWarAbilityActivationPolicy AbilityActivationPolicy = EWarAbilityActivationPolicy::OnTriggered; 

	UFUNCTION(BlueprintPure, Category = "War|Ability")
	UPwanCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "War|Ability")
	UWarAbilitySystemComponent* GetWarAbilitySystemComponentFromActorInfo() const; 
};
