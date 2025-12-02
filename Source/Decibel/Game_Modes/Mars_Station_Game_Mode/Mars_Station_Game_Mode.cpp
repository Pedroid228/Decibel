#include "Mars_Station_Game_Mode.h"

// AMars_Station_Game_Mode
//------------------------------------------------------------------------------------------------------------
AMars_Station_Game_Mode::AMars_Station_Game_Mode()
{
}
//------------------------------------------------------------------------------------------------------------
void AMars_Station_Game_Mode::BeginPlay()
{
	UWorld *world = 0;
	APlayerController *player_controller = 0;

	Super::BeginPlay();

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

	player_controller->bShowMouseCursor = false;
}
//------------------------------------------------------------------------------------------------------------
bool AMars_Station_Game_Mode::SetPause(APlayerController* PC, FCanUnpause can_unpause_delegate)
{
	On_Pause.Broadcast(true);

	return Super::SetPause(PC, can_unpause_delegate);
}
//------------------------------------------------------------------------------------------------------------
bool AMars_Station_Game_Mode::ClearPause()
{
	On_Pause.Broadcast(false);

	return Super::ClearPause();
}
//------------------------------------------------------------------------------------------------------------
