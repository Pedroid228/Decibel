#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "Game_State_Manager_Subsystem.generated.h"

// EGame_State
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class EGame_State: uint8
{
	None,
	Menu,
	Game,
};
//------------------------------------------------------------------------------------------------------------




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Game_State_Changed, EGame_State, new_state);

// UGame_State_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API UGame_State_Manager_Subsystem: public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UGame_State_Manager_Subsystem();
	void Set_Game_State(EGame_State new_game_state);

	FOn_Game_State_Changed On_Game_State_Changed;

private:
	EGame_State Game_State;
};
//------------------------------------------------------------------------------------------------------------
