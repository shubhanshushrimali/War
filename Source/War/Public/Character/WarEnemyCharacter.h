// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WarBaseCharacter.h"
#include "WarEnemyCharacter.generated.h"



class UEnemyCombatComponent; 


/**
 * 
 */
UCLASS()
class WAR_API AWarEnemyCharacter : public AWarBaseCharacter
{
	GENERATED_BODY()


public : 
	AWarEnemyCharacter();
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombactComponent() const { return EnemyCombatComponent; }
protected:

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEnemyCombatComponent* EnemyCombatComponent;

private:
	
	void InitEnemyStartUpData();	
};
