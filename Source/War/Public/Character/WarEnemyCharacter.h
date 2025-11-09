// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WarBaseCharacter.h"
#include "WarEnemyCharacter.generated.h"



class UEnemyCombatComponent; 
class UEnemyUIComponent; 
class UWidgetComponent; 
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

	virtual UPwanCombatComponent* GetPawnCombactComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;

protected:

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthBarWidgetComponent;


private:
	
	void InitEnemyStartUpData();	
};
