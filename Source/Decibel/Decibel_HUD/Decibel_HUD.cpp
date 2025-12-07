#include "Decibel_HUD.h"

#include "Game_Modes/Mars_Station_Game_Mode/Mars_Station_Game_Mode.h"
#include "Subsystems/Save_Manager_Subsystem/Save_Manager_Subsystem.h"
#include "UI/Game_Saving_Widget/Game_Saving_Widget.h"
#include "UI/Keycards_Widget/Keycards_Widget.h"
#include "UI/Pause_Menu_Widget/Pause_Menu_Widget.h"
#include "Subsystems/Localization_Manager_Subsystem/Localization_Manager_Subsystem.h"

// ADecibel_HUD
//------------------------------------------------------------------------------------------------------------
ADecibel_HUD::ADecibel_HUD(): Game_Saved_Showing_Time(1.5f)
{
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_HUD::Add_Keycard(EKeycard_Type keycard_type)
{
	check(Keycards_Widget != 0);
	Keycards_Widget->Add_Keycard(keycard_type);
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_HUD::Show_Credits()
{
	UWorld *world = 0;
	UGameInstance *game_inst = 0;
	ULocalization_Manager_Subsystem *localization_manager = 0;

	game_inst = GetGameInstance();
	check(game_inst != 0);

	localization_manager = game_inst->GetSubsystem<ULocalization_Manager_Subsystem>();
	check(localization_manager != 0);

	Crosshair_Widget->SetVisibility(ESlateVisibility::Collapsed);
	Keycards_Widget->SetVisibility(ESlateVisibility::Collapsed);
	Pasue_Menu_Widget->SetVisibility(ESlateVisibility::Collapsed);

	world = GetWorld();
	check(world != 0);
	
	if (localization_manager->Get_Language() == ELanguage::Ru)
		Credits_Widget = CreateWidget<UUserWidget>(world, Credits_RU_Widget_BP_Class);
	else
		Credits_Widget = CreateWidget<UUserWidget>(world, Credits_EN_Widget_BP_Class);

	check(Credits_Widget != 0);
	Credits_Widget->AddToViewport();
	Credits_Widget->SetVisibility(ESlateVisibility::Visible);
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_HUD::BeginPlay()
{
	UWorld *world = 0;
	Super::BeginPlay();
	AGameModeBase *game_mode = 0;
	AMars_Station_Game_Mode *mars_station_game_mode = 0;
	UGameInstance *game_inst = 0;
	USave_Manager_Subsystem *save_manager = 0;

	world = GetWorld();
	check(world != 0);

	check(Pause_Menu_Widget_BP_Class != 0);
	check(Game_Saving_Widget_BP_Class != 0);
	check(Crosshair_Widget_BP_Class != 0);
	check(Keycards_Widget_BP_Class != 0);
	check(Credits_RU_Widget_BP_Class != 0);
	check(Credits_EN_Widget_BP_Class != 0);

	game_mode = world->GetAuthGameMode();
	check(game_mode != 0);

	mars_station_game_mode = Cast<AMars_Station_Game_Mode>(game_mode);
	check(mars_station_game_mode != 0);
	mars_station_game_mode->On_Pause.AddDynamic(this, &ADecibel_HUD::Show_Pause_Menu);

	game_inst = GetGameInstance();
	check(game_inst != 0);

	save_manager = game_inst->GetSubsystem<USave_Manager_Subsystem>();
	check(save_manager != 0);

	save_manager->On_Game_Saved.AddDynamic(this, &ADecibel_HUD::Show_Game_Saved);

	Pasue_Menu_Widget = CreateWidget<UPause_Menu_Widget>(world, Pause_Menu_Widget_BP_Class);
	check(Pasue_Menu_Widget != 0);
	Pasue_Menu_Widget->AddToViewport();
	Pasue_Menu_Widget->SetVisibility(ESlateVisibility::Collapsed);

	Game_Saving_Widget = CreateWidget<UGame_Saving_Widget>(world, Game_Saving_Widget_BP_Class);
	check(Game_Saving_Widget != 0);
	Game_Saving_Widget->AddToViewport();
	Game_Saving_Widget->SetVisibility(ESlateVisibility::Collapsed);

	Crosshair_Widget = CreateWidget<UUserWidget>(world, Crosshair_Widget_BP_Class);
	check(Crosshair_Widget != 0);
	Crosshair_Widget->AddToViewport();
	Crosshair_Widget->SetVisibility(ESlateVisibility::Visible);

	Keycards_Widget = CreateWidget<UKeycards_Widget>(world, Keycards_Widget_BP_Class);
	check(Keycards_Widget != 0);
	Keycards_Widget->AddToViewport();
	Keycards_Widget->SetVisibility(ESlateVisibility::Visible);
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_HUD::Show_Pause_Menu(bool is_visible)
{
	check(Pasue_Menu_Widget != 0)

	    if (is_visible)
	{
		Crosshair_Widget->SetVisibility(ESlateVisibility::Collapsed);
		Keycards_Widget->SetVisibility(ESlateVisibility::Collapsed);
		Pasue_Menu_Widget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Crosshair_Widget->SetVisibility(ESlateVisibility::Visible);
		Keycards_Widget->SetVisibility(ESlateVisibility::Visible);
		Pasue_Menu_Widget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_HUD::Show_Game_Saved()
{
	UWorld *world = 0;

	check(Game_Saving_Widget != 0);
	Game_Saving_Widget->SetVisibility(ESlateVisibility::Visible);

	world = GetWorld();
	check(world != 0);
	world->GetTimerManager().SetTimer(Game_Save_Timer, this, &ADecibel_HUD::Hide_Game_Saved, Game_Saved_Showing_Time, false);
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_HUD::Hide_Game_Saved()
{
	check(Game_Saving_Widget != 0);
	Game_Saving_Widget->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------

