AugustsHus_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, AugustsHus_OnTransition
    map_script MAP_SCRIPT_ON_RESUME, AugustsHus_OnResume
	.byte 0

AugustsHus_EventScript_TryRemoveHarry::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

AugustsHus_OnTransition:
	call_if_unset FLAG_UNUSED_0x068, AugustsHus_EventScript_ShowHarry
	end

AugustsHus_EventScript_ShowHarry::
	clearflag FLAG_UNUSED_RS_LEGENDARY_BATTLE_DONE
	return

AugustsHus_EventScript_HarryEncounter::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEW, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_MEW, 5
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	callnative doharrybattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, AugustsHus_EventScript_DefeatedHarry
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, AugustsHus_EventScript_RanFromHarry
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, AugustsHus_EventScript_RanFromHarry
	setflag FLAG_UNUSED_0x068
	release
	end

AugustsHus_Text_HarryInteract:
	.string "HARRY: Mjau$"

AugustsHus_EventScript_DefeatedHarry::
	setflag FLAG_UNUSED_0x068
	goto Common_EventScript_RemoveStaticPokemon
	end
AugustsHus_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, AugustsHus_EventScript_TryRemoveHarry
	end

AugustsHus_EventScript_RanFromHarry::
    end

