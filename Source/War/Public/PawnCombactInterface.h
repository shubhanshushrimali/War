// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnCombactInterface.generated.h"

class UPwanCombatComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnCombactInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WAR_API IPawnCombactInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPwanCombatComponent* GetPawnCombactComponent() const = 0;
};
