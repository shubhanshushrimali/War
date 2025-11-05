// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"

namespace WarGameplayTags
{
	/**Input Tags **/
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);


	/**Player Tags **/

	/**Player Weaopns Tags **/
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	/**Player Ability Tags **/
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);

	/**Player Event Tags **/
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);

	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unquip_Axe); 
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);

	/**Player status Tags **/

	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);
	/**Enemy Tags **/
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	/**Shared Tags **/
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);

	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);


	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
}

