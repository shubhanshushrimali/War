// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarCharacterAnimInstance.h"
#include "WarCharacterHeroAnimInstance.generated.h"



class AWarHeroCharacter;

/**
 * 
 */
UCLASS()
class WAR_API UWarCharacterHeroAnimInstance : public UWarCharacterAnimInstance
{
	GENERATED_BODY()
	
public: 
	virtual void NativeInitializeAnimation() override; 

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;


protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	AWarHeroCharacter* OwningHeroCharacter;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxtStateThreshold = 5.f;

	float IdleElpasedTime;
};
