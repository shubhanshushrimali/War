// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WarWidgetBase.h"
#include "PawnUIInterface.h"

void UWarWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn());
	if (PawnUIInterface)
	{
		UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent();
		if (HeroUIComponent)
		{
			BP_OnOwningHeroUIComponentIntilaized(HeroUIComponent);
		}
	}
}

void UWarWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor);
	if (PawnUIInterface)
	{
		UEnemyUIComponent* EnemyUIComponent =  PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("UWarWidgetBase::InitEnemyCreatedWidget Failed to get EnemyUIComponent from Actor %s"), *OwningEnemyActor->GetName())

		if  (EnemyUIComponent)
		{
			BP_OnOwningEnemyUIComponentIntilaized(EnemyUIComponent);
		}
	}

}

