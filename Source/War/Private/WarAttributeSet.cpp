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
    // Get the target actor safely
    AActor* TargetAvatarActor = Data.Target.GetAvatarActor();

    // First, check if we have a valid target actor
    if (!IsValid(TargetAvatarActor))
    {
        return;
    }

    // Try to get or cache the interface
    if (!CachedPawnUIInterface.IsValid())
    {
        // Check if the actor implements the interface before assigning
        if (TargetAvatarActor->GetClass()->ImplementsInterface(UPawnUIInterface::StaticClass()))
        {
            CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(TargetAvatarActor);
        }
        else
        {
            // If the actor doesn't implement the interface, we can't proceed
            UE_LOG(LogTemp, Warning, TEXT("Actor %s does not implement IPawnUIInterface"), *TargetAvatarActor->GetName());
            return;
        }
    }

    // Double-check if the cached interface is valid
    if (!CachedPawnUIInterface.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("CachedPawnUIInterface is invalid for actor %s"), *TargetAvatarActor->GetName());
        return;
    }

    // Now safely get the pawn UI component
    UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

    if (!IsValid(PawnUIComponent))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get PawnUIComponent from actor %s"), *TargetAvatarActor->GetName());
        return;
    }

    // Process health attribute changes
    if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
    {
        const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
        SetCurrentHealth(NewCurrentHealth);

        if (IsValid(PawnUIComponent))
        {
            PawnUIComponent->OnCurrentHealthChanged.Broadcast(NewCurrentHealth / GetMaxHealth());
        }
    }

    // Process rage attribute changes
    if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
    {
        const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
        SetCurrentRage(NewCurrentRage);

        UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent();
        if (IsValid(HeroUIComponent))
        {
            HeroUIComponent->OnCurrentRageChanged.Broadcast(NewCurrentRage / GetMaxRage());
        }
    }

    // Process damage taken
    if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
    {
        const float OldHealth = GetCurrentHealth();
        const float DamageTakenAmount = GetDamageTaken();

        const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageTakenAmount, 0.f, GetMaxHealth());
        SetCurrentHealth(NewCurrentHealth);

        if (IsValid(PawnUIComponent))
        {
            PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
        }

        if (GetCurrentHealth() == 0.f && IsValid(TargetAvatarActor))
        {
            UWarFunctionLibrary::AddGamePlayTagToActorIfNone(
                TargetAvatarActor,
                WarGameplayTags::Shared_Status_Dead
            );
        }

        // Reset damage taken after processing
        SetDamageTaken(0.f);
    }
}
