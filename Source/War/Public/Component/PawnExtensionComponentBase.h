// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WAR_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	template <class T> 
	T* GetPawnOwner() const
	{
		static_assert(TIsDerivedFrom<T, APawn>::Value, "T must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetPawnOwner<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TIsDerivedFrom<T, AController>::Value, "T must be derived from AController");
		return GetOwningPawn()->GetController<T>();
	}
};
