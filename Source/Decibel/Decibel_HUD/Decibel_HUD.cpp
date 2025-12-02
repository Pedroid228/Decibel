#include "Decibel_HUD.h"
#include "UI/Pause_Menu_Widget/Pause_Menu_Widget.h"
#include "Game_Modes/Mars_Station_Game_Mode/Mars_Station_Game_Mode.h"

// ADecibel_HUD
//------------------------------------------------------------------------------------------------------------
ADecibel_HUD::ADecibel_HUD()
{
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_HUD::BeginPlay()
{
	UWorld *world = 0;
	Super::BeginPlay();
	AGameModeBase* game_mode = 0;
	AMars_Station_Game_Mode *mars_station_game_mode = 0;

	world = GetWorld();
	check(world != 0);
	
	check(Pause_Menu_Widget_BP_Class != 0);
	
	game_mode = world->GetAuthGameMode();
	check(game_mode != 0);

	mars_station_game_mode = Cast<AMars_Station_Game_Mode>(game_mode);
	check(mars_station_game_mode != 0);
	mars_station_game_mode->On_Pause.AddDynamic(this, &ADecibel_HUD::Show_Pause_Menu);

    Pasue_Menu_Widget = CreateWidget<UPause_Menu_Widget>(world, Pause_Menu_Widget_BP_Class);
	check(Pasue_Menu_Widget != 0);
	Pasue_Menu_Widget->AddToViewport();
	Pasue_Menu_Widget->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_HUD::Show_Pause_Menu(bool is_visible)
{
	check(Pasue_Menu_Widget != 0)

	if (is_visible)
		Pasue_Menu_Widget->SetVisibility(ESlateVisibility::Visible);
	else
		Pasue_Menu_Widget->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
