// Fill out your copyright notice in the Description page of Project Settings.


#include "WarAttributeSet.h"
#include "GameplayEffectExtension.h"	
#include "WarFunctionLibrary.h"
#include "WarGameplayTags.h"


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
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{ 
		const float OldHealth = GetCurrentHealth();
		const float DamageTakenAmount = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageTakenAmount, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);



		if (NewCurrentHealth == 0.f)
		{
			UWarFunctionLibrary::AddGamePlayTagToActorIfNone(
				Data.Target.GetAvatarActor(),
				WarGameplayTags::Shared_Status_Dead
			);
			
		}
	} 

}
