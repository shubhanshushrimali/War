// Fill out your copyright notice in the Description page of Project Settings.


#include "WarFunctionLibrary.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"

UWarAbilitySystemComponent* UWarFunctionLibrary::NativeGetWarAbilitySystemComponentFromActor(AActor* Actor)
{

	check(Actor);

	return CastChecked<UWarAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));

}

void UWarFunctionLibrary::AddGamePlayTagToActorIfNone(AActor* Actor, FGameplayTag TagToAdd)
{
	UWarAbilitySystemComponent* ASC = NativeGetWarAbilitySystemComponentFromActor(Actor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWarFunctionLibrary::RemoveGamePlayTagToActorIfFound(AActor* Actor, FGameplayTag TagToRemove)
{

	UWarAbilitySystemComponent* ASC = NativeGetWarAbilitySystemComponentFromActor(Actor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}

}

bool UWarFunctionLibrary::NativeDoesActorHaveTag(AActor* Actor, FGameplayTag TagToCheck)
{
	UWarAbilitySystemComponent* ASC = NativeGetWarAbilitySystemComponentFromActor(Actor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UWarFunctionLibrary::DoesActorHaveTag(AActor* Actor, FGameplayTag TagToCheck, EWarConfiemType& OutConfirmType)
{

	OutConfirmType = NativeDoesActorHaveTag(Actor, TagToCheck) ? EWarConfiemType::YES : EWarConfiemType::No;
}

