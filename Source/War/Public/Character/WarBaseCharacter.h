// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WarBaseCharacter.generated.h"


class UWarAbilitySystemComponent;
class UWarAttributeSet;

UCLASS()
class WAR_API AWarBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarBaseCharacter();
	//~ Begin APawn Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	//~ End APawn Interface
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWarAbilitySystemComponent* WarAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWarAttributeSet* WarAttributeSet;


public:
	FORCEINLINE UWarAbilitySystemComponent* GetWarAbilitySystemComponent() const { return WarAbilitySystemComponent; }
	FORCEINLINE UWarAttributeSet* GetWarAttributeSet() const { return WarAttributeSet; }
};
