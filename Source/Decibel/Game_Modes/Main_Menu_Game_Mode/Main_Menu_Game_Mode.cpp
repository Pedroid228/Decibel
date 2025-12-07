#include "Main_Menu_Game_Mode.h"
#include "UI/Main_Menu/Main_Menu_Widget/Main_Menu_Widget.h"

// AMain_Menu_Game_Mode
//------------------------------------------------------------------------------------------------------------
AMain_Menu_Game_Mode::AMain_Menu_Game_Mode()
{
}
//------------------------------------------------------------------------------------------------------------
void AMain_Menu_Game_Mode::BeginPlay()
{
	FInputModeUIOnly input_mode_data;
	UWorld *world = 0;
	APlayerController *player_controller = 0;

	Super::BeginPlay();

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

	Create_And_Show_Main_Menu_Widget(player_controller);

    input_mode_data.SetWidgetToFocus(Main_Menu_Widget->TakeWidget());
    input_mode_data.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	player_controller->bShowMouseCursor = true;
    player_controller->SetInputMode(input_mode_data);
}
//------------------------------------------------------------------------------------------------------------
void AMain_Menu_Game_Mode::Create_And_Show_Main_Menu_Widget(APlayerController *player_controller)
{
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
