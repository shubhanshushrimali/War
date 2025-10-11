// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WarWeaponBase.h"
#include "Components/BoxComponent.h"



AWarWeaponBase::AWarWeaponBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;


	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(RootComponent);
	WeaponCollisionBox->SetBoxExtent(FVector(20.0f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}



