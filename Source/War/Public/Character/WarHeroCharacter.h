// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WarBaseCharacter.h"
#include "WarHeroCharacter.generated.h"



class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class WAR_API AWarHeroCharacter : public AWarBaseCharacter
{
	GENERATED_BODY()
	

public:
	AWarHeroCharacter();
protected:
	
	virtual void BeginPlay() override;

private:
#pragma region Components 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

#pragma endregion
};
