// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarFunctionLibrary.generated.h"

/**
 * 
 */

UENUM()
enum class  EWarConfiemType : uint8
{
	YES,
	No
};



class UWarAbilitySystemComponent; 
struct FGameplayTag;

UCLASS()
class WAR_API UWarFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UWarAbilitySystemComponent* NativeGetWarAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "War|FunctionLibrary")
	static void AddGamePlayTagToActorIfNone(AActor* Actor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "War|FunctionLibrary")
	static void RemoveGamePlayTagToActorIfFound(AActor* Actor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* Actor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "War|FunctionLibrary", meta = (DisplayName = "Does Actor Have TAG", ExpandEnumAsExecs = "OutConfirmType"))
	static void DoesActorHaveTag(AActor* Actor, FGameplayTag TagToCheck , EWarConfiemType& OutConfirmType);

};