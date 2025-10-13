// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/WarHeroLinkedLayer.h"
#include "AnimInstances/Hero/WarCharacterHeroAnimInstance.h"


UWarCharacterHeroAnimInstance* UWarHeroLinkedLayer::GetHeroAnimInstance() const
{
	return Cast<UWarCharacterHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
