// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarGameplayAbility.h"
#include "GameplayEffect.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarAbilitySystemComponent* InWarASCToGive, int32 ApplyLevel)
{

	check(InWarASCToGive);

	GrantAbility(ActivateOnGivenAbility, InWarASCToGive, ApplyLevel); 
	GrantAbility(ReactiveAbility, InWarASCToGive, ApplyLevel);

    if (!StartUpGameplayEffect.IsEmpty())
    {
		for (const TSubclassOf <UGameplayEffect>& EffectClass : StartUpGameplayEffect)
		{
			if (!EffectClass)
			{
				continue;
			}

			UGameplayEffect* GameplayEffect = EffectClass->GetDefaultObject<UGameplayEffect>();

            InWarASCToGive->ApplyGameplayEffectToSelf(
                GameplayEffect,
                ApplyLevel,
                InWarASCToGive->MakeEffectContext()
            );
		}
    }

}

void UDataAsset_StartUpDataBase::GrantAbility(
    const TArray<TSubclassOf<UWarGameplayAbility>>& InAbilityToGive,
    UWarAbilitySystemComponent* InWarASCToGive,
    int32 ApplyLevel)
{
    if (!InWarASCToGive || InAbilityToGive.IsEmpty())
    {
        return;
    }

    for (const TSubclassOf<UWarGameplayAbility>& Ability : InAbilityToGive)
    {
        if (!Ability)
        {
            UE_LOG(LogTemp, Warning, TEXT("Ability in DataAsset_StartUpDataBase is null!"));
            continue;
        }

        FGameplayAbilitySpec AbilitySpec(Ability);
        AbilitySpec.SourceObject = InWarASCToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;

        FGameplayAbilitySpecHandle Handle = InWarASCToGive->GiveAbility(AbilitySpec);


        if (&InAbilityToGive == &ActivateOnGivenAbility)
        {
            UE_LOG(LogTemp, Warning, TEXT("Auto activating ability: %s"), *GetNameSafe(Ability));
            InWarASCToGive->TryActivateAbility(Handle);
        }
    }
}

