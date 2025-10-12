// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartUpData.generated.h"

/**
 * 
 */

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

UCLASS()
class WAR_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UWarAbilitySystemComponent* InWarASCToGive, int32 ApplyLevel = 1) override;;
private: 
	UPROPERTY(EditAnywhere, Category = "StartUpData", meta = (TitleProperty ="InputTag"))
	TArray<FWarHeroAbliltySet> HeroStartUpAbiliySets;
};
