// Fill out your copyright notice in the Description page of Project Settings.


#include "WarGameplayTags.h"

namespace WarGameplayTags
{
	/**Input Tags **/
	WAR_API UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "Input.Move");
		
	WAR_API UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "Input.Look");

	WAR_API UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipAxe, "Input.EquipAxe");

	WAR_API UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipAxe, "Input.UnequipAxe");
 
	WAR_API UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe, "Player.Weapon.Axe");
	/**Input Tags **/
	WAR_API UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe, "Player.Event.Equip.Axe");

	WAR_API UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unquip_Axe, "Player.Event.Unquip.Axe");



	WAR_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe");

	WAR_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Axe, "Player.Ability.Unequip.Axe");

}
