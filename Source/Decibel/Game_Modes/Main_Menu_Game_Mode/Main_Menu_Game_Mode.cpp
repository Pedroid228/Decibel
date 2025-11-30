#include "Main_Menu_Game_Mode.h"
#include "UI/Main_Menu_Widget/Main_Menu_Widget.h"
#include "Subsystems/Game_State_Manager_Subsystem/Game_State_Manager_Subsystem.h"

// AMain_Menu_Game_Mode
//------------------------------------------------------------------------------------------------------------
AMain_Menu_Game_Mode::AMain_Menu_Game_Mode()
{
}
//------------------------------------------------------------------------------------------------------------
void AMain_Menu_Game_Mode::BeginPlay()
{
	Super::BeginPlay();

	Create_And_Show_Main_Menu_Widget();
}
//------------------------------------------------------------------------------------------------------------
void AMain_Menu_Game_Mode::Create_And_Show_Main_Menu_Widget()
{
	UWorld *world = 0;
	APlayerController *player_controller = 0;

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

	check(Main_Menu_Widget_BP_Class != 0);

	Main_Menu_Widget = CreateWidget<UMain_Menu_Widget>(player_controller, Main_Menu_Widget_BP_Class);
	check(Main_Menu_Widget != 0);
	Main_Menu_Widget->AddToViewport();
	Main_Menu_Widget->SetVisibility(ESlateVisibility::Visible);
}
//------------------------------------------------------------------------------------------------------------
void AMain_Menu_Game_Mode::Hide_And_Delete_Main_Menu_Widget()
{
	check(Main_Menu_Widget != 0);
	Main_Menu_Widget->RemoveFromViewport();
	Main_Menu_Widget = 0;
}
//------------------------------------------------------------------------------------------------------------
