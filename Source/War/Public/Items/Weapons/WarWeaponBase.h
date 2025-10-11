// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class WAR_API AWarWeaponBase : public AActor
{
	GENERATED_BODY()

public:

	AWarWeaponBase(); 

	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;
};
