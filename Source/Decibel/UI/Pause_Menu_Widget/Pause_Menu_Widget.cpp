#include "Pause_Menu_Widget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Decibel_Game_Instance/Decibel_Game_Instance.h"
#include "Subsystems/Localization_Manager_Subsystem/Localization_Manager_Subsystem.h"

// UPause_Menu_Widget
//------------------------------------------------------------------------------------------------------------
UPause_Menu_Widget::UPause_Menu_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void UPause_Menu_Widget::NativeConstruct()
{
	UGameInstance *game_inst = 0;
	ULocalization_Manager_Subsystem *localization_manager = 0;

	Super::NativeConstruct();

	check(Main_Menu_Button != 0);
	Main_Menu_Button->OnClicked.AddDynamic(this, &UPause_Menu_Widget::On_Main_Menu_Clicked);

	check(Save_Game_Button != 0);
	Save_Game_Button->OnClicked.AddDynamic(this, &UPause_Menu_Widget::On_Save_Game_Clicked);

	check(Quit_Game_Button != 0);
	Quit_Game_Button->OnClicked.AddDynamic(this, &UPause_Menu_Widget::On_Quit_Game_Clicked);

	game_inst = GetGameInstance();
	check(game_inst != 0);

	localization_manager = game_inst->GetSubsystem<ULocalization_Manager_Subsystem>();
	check(localization_manager != 0);

	check(Main_Menu_Button_Text != 0);
	Main_Menu_Button_Text->SetText(localization_manager->Get_Value(TEXT("To_Main_Menu")));

	check(Save_Game_Button_Text != 0);
	Save_Game_Button_Text->SetText(localization_manager->Get_Value(TEXT("Save_Game")));

	check(Quit_Game_Button_Text != 0);
	Quit_Game_Button_Text->SetText(localization_manager->Get_Value(TEXT("Quit_Game")));

	Decibel_Game_Inst = GetGameInstance<UDecibel_Game_Instance>();
	check(Decibel_Game_Inst != 0);
}
//------------------------------------------------------------------------------------------------------------
void UPause_Menu_Widget::On_Main_Menu_Clicked()
{
	check(Decibel_Game_Inst != 0);
	Decibel_Game_Inst->Main_Menu();
}
//------------------------------------------------------------------------------------------------------------
void UPause_Menu_Widget::On_Save_Game_Clicked()
{
	check(Decibel_Game_Inst != 0);
	Decibel_Game_Inst->Save_Curr_Game();
}
//------------------------------------------------------------------------------------------------------------
void UPause_Menu_Widget::On_Quit_Game_Clicked()
{
	check(Decibel_Game_Inst != 0);
	Decibel_Game_Inst->Quit_Game();
}
//------------------------------------------------------------------------------------------------------------
