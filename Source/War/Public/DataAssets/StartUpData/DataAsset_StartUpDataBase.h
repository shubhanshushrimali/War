// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UWarGameplayAbility; 
class UWarAbilitySystemComponent;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class WAR_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public :
	virtual void GiveToAbilitySystemComponent(UWarAbilitySystemComponent* InWarASCToGive, int32 ApplyLevel = 1) ;



protected:
	UPROPERTY(EditAnywhere, Category = "StartUpData")
	TArray < TSubclassOf <UWarGameplayAbility> > ActivateOnGivenAbility; 

	UPROPERTY(EditAnywhere, Category = "StartUpData")
	TArray < TSubclassOf <UWarGameplayAbility> > ReactiveAbility;

	UPROPERTY(EditAnywhere, Category = "StartUpData")
	TArray < TSubclassOf <UGameplayEffect> > StartUpGameplayEffect;

	void GrantAbility(const TArray < TSubclassOf <UWarGameplayAbility> >& InAblityToGive , UWarAbilitySystemComponent* InWarASCToGive, int32 ApplyLevel = 1);

};
