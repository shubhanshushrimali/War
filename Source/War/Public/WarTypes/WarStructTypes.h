// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"

#include "WarStructTypes.generated.h"



class UWarHeroLinkedLayer; 
class UWarGameplayAbility;
class UInputMappingContext; 

USTRUCT(BlueprintType)
struct FWarHeroAbliltySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarGameplayAbility> AbilityToGrant;

	bool IsValid() const;


};

USTRUCT(BlueprintType)
struct FWarHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarHeroLinkedLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWarHeroAbliltySet> DefaultWeaponAbilities;

}; 