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

	/**Player Event Tags **/
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);

	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unquip_Axe); 

	/**Player status Tags **/

	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
}

