// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WarCharacterAnimInstance.h"
#include "Character/WarBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UWarCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWarBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWarCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
