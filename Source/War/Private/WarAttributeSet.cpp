// Fill out your copyright notice in the Description page of Project Settings.


#include "WarAttributeSet.h"
#include "GameplayEffectExtension.h"	
#include "WarFunctionLibrary.h"
#include "WarGameplayTags.h"
#include "PawnUIInterface.h"
#include "Component/UI/PawnUIComponent.h"
#include "Component/UI/HeroUIComponent.h"

UWarAttributeSet::UWarAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UWarAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("UWarAttributeSet::PostGameplayEffectExecute Failed to get IPawnUIInterface from Actor %s"), *Data.Target.GetAvatarActor()->GetName())

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("UWarAttributeSet::PostGameplayEffectExecute Failed to get PawnUIComponent from Actor %s"), *Data.Target.GetAvatarActor()->GetName())

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(NewCurrentHealth / GetMaxHealth()); 
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
		//OnCurrentRageChanged
		UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent();
		if (HeroUIComponent)
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(NewCurrentRage / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{ 
		const float OldHealth = GetCurrentHealth();
		const float DamageTakenAmount = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageTakenAmount, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.f)
		{
			UWarFunctionLibrary::AddGamePlayTagToActorIfNone(
				Data.Target.GetAvatarActor(),
				WarGameplayTags::Shared_Status_Dead
			);
			
		}
	} 

}
