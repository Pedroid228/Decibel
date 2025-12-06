#include "Pause_Menu_Widget.h"
#include "UI/Decibel_Button_Widget/Decibel_Button_Widget.h"
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
	Main_Menu_Button->Get_On_Clicked().AddDynamic(this, &UPause_Menu_Widget::On_Main_Menu_Clicked);
	Main_Menu_Button->Set_Text_By_Key(TEXT("To_Main_Menu"));

	check(Save_Game_Button != 0);
	Save_Game_Button->Get_On_Clicked().AddDynamic(this, &UPause_Menu_Widget::On_Save_Game_Clicked);
	Save_Game_Button->Set_Text_By_Key(TEXT("Save_Game"));

	check(Quit_Game_Button != 0);
	Quit_Game_Button->Get_On_Clicked().AddDynamic(this, &UPause_Menu_Widget::On_Quit_Game_Clicked);
	Quit_Game_Button->Set_Text_By_Key(TEXT("Quit_Game"));

	game_inst = GetGameInstance();
	check(game_inst != 0);

	localization_manager = game_inst->GetSubsystem<ULocalization_Manager_Subsystem>();
	check(localization_manager != 0);

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
