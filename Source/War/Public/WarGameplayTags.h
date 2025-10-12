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

	/**Player Tags **/
	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);

	WAR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unquip_Axe); 
}

