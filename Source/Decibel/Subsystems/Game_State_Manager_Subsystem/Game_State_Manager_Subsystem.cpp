#include "Game_State_Manager_Subsystem.h"
#include "Kismet/GameplayStatics.h"

// UGame_State_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
UGame_State_Manager_Subsystem::UGame_State_Manager_Subsystem(): Game_State(EGame_State::None)
{
}
//------------------------------------------------------------------------------------------------------------
void UGame_State_Manager_Subsystem::Set_Game_State(EGame_State new_game_state)
{
	UWorld *world = 0;
	FName map_name;

	if (new_game_state == Game_State)
		return;

	check(new_game_state != EGame_State::None);

	switch (new_game_state)
	{
	case EGame_State::Menu:
		map_name = TEXT("Menu_Map");
		break;

	case EGame_State::Game:
		map_name = TEXT("Test_Map");
		break;
	}

	world = GetWorld();
	check(world != 0);
	UGameplayStatics::OpenLevel(world, map_name);

	Game_State = new_game_state;
}
//------------------------------------------------------------------------------------------------------------
