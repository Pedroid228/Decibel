#include "Decibel_Player_Controller.h"
#include "Decibel_HUD/Decibel_HUD.h"
#include "Decibel_Game_Instance/Decibel_Game_Instance.h"

// ADecibel_Player_Controller
//------------------------------------------------------------------------------------------------------------
ADecibel_Player_Controller::ADecibel_Player_Controller(const FObjectInitializer &object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Toggle_Pause", IE_Pressed, this, &ADecibel_Player_Controller::Toggle_Pause).bExecuteWhenPaused = true;
	InputComponent->BindAction("Load_Save", IE_Pressed, this, &ADecibel_Player_Controller::Load_Save);  // !!! Debug
	InputComponent->BindAction("Save_Game", IE_Pressed, this, &ADecibel_Player_Controller::Save_Game);  // !!! Debug
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_Player_Controller::Load_Save()
{
	UDecibel_Game_Instance *game_inst = 0;

	game_inst = GetGameInstance<UDecibel_Game_Instance>();
	check(game_inst != 0);

	game_inst->Load_Curr_Game();
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_Player_Controller::Save_Game()
{
	UDecibel_Game_Instance *game_inst = 0;

	game_inst = GetGameInstance<UDecibel_Game_Instance>();
	check(game_inst != 0);

	game_inst->Save_Curr_Game();
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_Player_Controller::Toggle_Pause()
{
	bool is_paused;

	is_paused = IsPaused();

	bShowMouseCursor = !is_paused;
	SetPause(!is_paused);
}
//------------------------------------------------------------------------------------------------------------
