// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarEnemyGameplayAbility.h"
#include "Character/WarEnemyCharacter.h"
#include "Component/Combat/EnemyCombatComponent.h"

AWarEnemyCharacter* UWarEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!ChachedWarEnemyCharcter.IsValid())
    {
        ChachedWarEnemyCharcter =  Cast<AWarEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }

    return ChachedWarEnemyCharcter.IsValid() ? ChachedWarEnemyCharcter.Get() : nullptr; 
}

UEnemyCombatComponent* UWarEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombactComponent();
}
