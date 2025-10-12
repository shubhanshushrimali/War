// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WAR_API UWarInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(
		const UDataAsset_InputConfig* InputConfig,
		const FGameplayTag& InputTag,
		ETriggerEvent TriggerEvent,
		UserObject* Object,
		CallbackFunc Func
	);
	
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(
		const UDataAsset_InputConfig* InputConfig,
		UserObject* Object,
		CallbackFunc InputPressedFunc,
		CallbackFunc InputReleasedFunc 
	);
};

template<class UserObject, typename CallbackFunc>
inline void UWarInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* Object, CallbackFunc Func)
{
	
	checkf(InInputConfig, TEXT("InputConfig is nullptr , can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, Object, Func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UWarInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InputConfig, UserObject* Object, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{

	checkf(InputConfig, TEXT("InputConfig is nullptr , can not proceed with binding"));

	for (const FWarInputActionConfig& AbilityInputActionConfig : InputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) { continue; }


			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, Object, InputPressedFunc, AbilityInputActionConfig.InputTag);
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, Object, InputReleasedFunc , AbilityInputActionConfig.InputTag);
		
	}

}
