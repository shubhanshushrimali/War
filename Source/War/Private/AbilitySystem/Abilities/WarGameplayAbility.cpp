// WarGameplayAbility.cpp

#include "AbilitySystem/Abilities/WarGameplayAbility.h"

#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "Component/Combat/PwanCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"            // For UAbilitySystemComponent
#include "GameplayEffectTypes.h"              // For FGameplayEffectSpecHandle, FActiveGameplayEffectHandle
#include "GameFramework/Actor.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarGameplayAbility, Log, All);

void UWarGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EWarAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && Spec.IsActive())
		{
			// ActorInfo->AbilitySystemComponent may be a TWeakObjectPtr in some engine versions.
			if (ActorInfo->AbilitySystemComponent.IsValid())
			{
				UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
				if (ASC)
				{
					ASC->TryActivateAbility(Spec.Handle);
				}
				else
				{
					UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] OnGiveAbility: AbilitySystemComponent.Get() returned null."), *GetName());
				}
			}
			else
			{
				UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] OnGiveAbility failed: AbilitySystemComponent is not valid."), *GetName());
			}
		}
	}
}

void UWarGameplayAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EWarAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && ActorInfo->AbilitySystemComponent.IsValid())
		{
			// ✅ In UE5.5, AbilitySystemComponent is a raw pointer, not a TWeakObjectPtr
			UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
			if (ASC)
			{
				ASC->ClearAbility(Handle);
			}
			else
			{
				UE_LOG(LogWarGameplayAbility, Warning,
					TEXT("[%s] EndAbility: AbilitySystemComponent pointer is null."),
					*GetName());
			}
		}
		else
		{
			UE_LOG(LogWarGameplayAbility, Warning,
				TEXT("[%s] EndAbility failed: Missing ActorInfo or AbilitySystemComponent."),
				*GetName());
		}
	}
}


UPwanCombatComponent* UWarGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor)
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] GetPawnCombatComponentFromActorInfo failed: AvatarActor is null."), *GetName());
		return nullptr;
	}

	UPwanCombatComponent* CombatComp = AvatarActor->FindComponentByClass<UPwanCombatComponent>();
	if (!CombatComp)
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] No UPwanCombatComponent found on AvatarActor %s."), *GetName(), *AvatarActor->GetName());
	}
	return CombatComp;
}

UWarAbilitySystemComponent* UWarGameplayAbility::GetWarAbilitySystemComponentFromActorInfo() const
{
	if (!CurrentActorInfo)
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] GetWarAbilitySystemComponentFromActorInfo failed: CurrentActorInfo is null."), *GetName());
		return nullptr;
	}

	// CurrentActorInfo->AbilitySystemComponent is commonly a TWeakObjectPtr<UAbilitySystemComponent>.
	if (!CurrentActorInfo->AbilitySystemComponent.IsValid())
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] CurrentActorInfo AbilitySystemComponent is not valid."), *GetName());
		return nullptr;
	}

	UAbilitySystemComponent* RawASC = CurrentActorInfo->AbilitySystemComponent.Get();
	return RawASC ? Cast<UWarAbilitySystemComponent>(RawASC) : nullptr;
}

FActiveGameplayEffectHandle UWarGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	FActiveGameplayEffectHandle InvalidHandle;

	if (!TargetActor)
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] NativeApplyEffectSpecHandleToTarget failed: TargetActor is null."), *GetName());
		return InvalidHandle;
	}

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC)
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] TargetActor '%s' has no AbilitySystemComponent."), *GetName(), *TargetActor->GetName());
		return InvalidHandle;
	}

	if (!InSpecHandle.IsValid() || !InSpecHandle.Data.IsValid())
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] Invalid or uninitialized GameplayEffectSpecHandle when applying to %s."), *GetName(), *TargetActor->GetName());
		return InvalidHandle;
	}

	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
	if (!SourceASC)
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] Source AbilitySystemComponent is null."), *GetName());
		return InvalidHandle;
	}

	// Apply safely
	FActiveGameplayEffectHandle ActiveHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data.Get(), TargetASC);
	if (!ActiveHandle.WasSuccessfullyApplied())
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] Failed to apply GameplayEffectSpec to %s."), *GetName(), *TargetActor->GetName());
	}
	else
	{
		UE_LOG(LogWarGameplayAbility, Verbose, TEXT("[%s] Successfully applied GameplayEffect to %s."), *GetName(), *TargetActor->GetName());
	}

	return ActiveHandle;
}

FActiveGameplayEffectHandle UWarGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EWarSuccessType& OutSuccessType)
{
	OutSuccessType = EWarSuccessType::Failed;

	FActiveGameplayEffectHandle ActiveHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	if (ActiveHandle.WasSuccessfullyApplied())
	{
		OutSuccessType = EWarSuccessType::Successful;
	}
	else
	{
		UE_LOG(LogWarGameplayAbility, Warning, TEXT("[%s] BP_ApplyEffectSpecHandleToTarget failed on Target %s."), *GetName(), TargetActor ? *TargetActor->GetName() : TEXT("Unknown"));
	}

	return ActiveHandle;
}
