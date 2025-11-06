// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "PawnCombactInterface.h"
#include "PawnUIInterface.h"
#include "WarBaseCharacter.generated.h"


class UWarAbilitySystemComponent;
class UWarAttributeSet;
class UDataAsset_StartUpDataBase; 

UCLASS()
class WAR_API AWarBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombactInterface , public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarBaseCharacter();
	//~ Begin APawn Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End APawn Interface

	virtual UPwanCombatComponent* GetPawnCombactComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;


protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWarAbilitySystemComponent* WarAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWarAttributeSet* WarAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData; 

public:
	FORCEINLINE UWarAbilitySystemComponent* GetWarAbilitySystemComponent() const { return WarAbilitySystemComponent; }
	FORCEINLINE UWarAttributeSet* GetWarAttributeSet() const { return WarAttributeSet; }
};
