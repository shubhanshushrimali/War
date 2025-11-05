// WarGameplayAbility.h
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarTypes/WarEnumTypes.h"
#include "WarGameplayAbility.generated.h"

class UWarAbilitySystemComponent;
class UPwanCombatComponent;

UENUM(BlueprintType)
enum class EWarAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class WAR_API UWarGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// Match the base class signature (note the const ref for ActivationInfo)
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled
	) override;

	UPROPERTY(EditDefaultsOnly, Category = "WarAbility")
	EWarAbilityActivationPolicy AbilityActivationPolicy = EWarAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "War|Ability")
	UPwanCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "War|Ability")
	UWarAbilitySystemComponent* GetWarAbilitySystemComponentFromActorInfo() const;

	// Not exposed to BP (internal helper)
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "War|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EWarSuccessType& OutSuccessType);
};
