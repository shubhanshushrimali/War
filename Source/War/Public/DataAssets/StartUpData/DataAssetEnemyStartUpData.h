// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAssetEnemyStartUpData.generated.h"



class UWarEnemyGameplayAbility; 


/**
 * 
 */
UCLASS()
class WAR_API UDataAssetEnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()


public:
	virtual void GiveToAbilitySystemComponent(UWarAbilitySystemComponent* InWarASCToGive, int32 ApplyLevel = 1) override;
private:
	UPROPERTY(EditAnywhere, Category = "StartUpData")
	TArray<TSubclassOf<UWarEnemyGameplayAbility>> EnemyCombactAbilities; 
};
