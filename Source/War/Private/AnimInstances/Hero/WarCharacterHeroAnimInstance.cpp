// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/WarCharacterHeroAnimInstance.h"
#include  "Character/WarBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"




void UWarCharacterHeroAnimInstance::NativeInitializeAnimation()
{

	OwningCharacter = Cast<AWarBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningCharacterMovement = OwningCharacter->GetCharacterMovement();
	}
}

void UWarCharacterHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningCharacterMovement)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();	
	bHasAcceleration = OwningCharacterMovement->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
