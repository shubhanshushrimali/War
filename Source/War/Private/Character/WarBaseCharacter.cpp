// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarBaseCharacter.h"

// Sets default values
AWarBaseCharacter::AWarBaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;	
}


