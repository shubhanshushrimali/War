// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarCharacterAnimInstance.h"
#include "WarCharacterHeroAnimInstance.generated.h"



class AWarBaseCharacter;
class UCharacterMovementComponent;
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
	UPROPERTY()
	AWarBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningCharacterMovement;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
