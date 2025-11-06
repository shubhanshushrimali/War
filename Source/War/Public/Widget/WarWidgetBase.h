// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WarWidgetBase.generated.h"




class UHeroUIComponent; 
class UEnemyUIComponent;
/**
 * 
 */
UCLASS()
class WAR_API UWarWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	 virtual void NativeOnInitialized() override;

	 UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Intilaized"))
	 void BP_OnOwningHeroUIComponentIntilaized(UHeroUIComponent* OwningHeroUIComponent);

	 UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Intilaized"))
	 void BP_OnOwningEnemyUIComponentIntilaized(UEnemyUIComponent* OwningEnemyUIComponent);
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};
