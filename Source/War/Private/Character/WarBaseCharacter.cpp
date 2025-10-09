// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarBaseCharacter.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "WarAttributeSet.h"



// Sets default values
AWarBaseCharacter::AWarBaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;	


	WarAbilitySystemComponent = CreateDefaultSubobject<UWarAbilitySystemComponent>(TEXT("WarAbilitySystemComponent"));

	WarAttributeSet = CreateDefaultSubobject<UWarAttributeSet>(TEXT("WarAttributeSet"));
}

UAbilitySystemComponent* AWarBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarAbilitySystemComponent();
}

void AWarBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (WarAbilitySystemComponent)
	{
		WarAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}


