// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/WarCharacterHeroAnimInstance.h"
#include  "Character/WarBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/WarHeroCharacter.h"



void UWarCharacterHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AWarHeroCharacter>(OwningCharacter);
	}
	
}

void UWarCharacterHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElpasedTime += DeltaSeconds;

		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxtStateThreshold);
	}
}
