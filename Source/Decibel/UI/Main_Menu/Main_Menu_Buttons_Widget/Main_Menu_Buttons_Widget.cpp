#include "Main_Menu_Buttons_Widget.h"

#include "Components/ComboBoxString.h"
#include "UI/Decibel_Button_Widget/Decibel_Button_Widget.h"
#include "Data/Localization_Data/Localization_Data.h"
#include "Decibel_Game_Instance/Decibel_Game_Instance.h"
#include "Subsystems/Localization_Manager_Subsystem/Localization_Manager_Subsystem.h"
#include "UI/Main_Menu/Saves_List_Widget/Saves_List_Widget.h"

// UMain_Menu_Buttons_Widget
//------------------------------------------------------------------------------------------------------------
UMain_Menu_Buttons_Widget::UMain_Menu_Buttons_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Buttons_Widget::NativeConstruct()
{
	ELanguage curr_language;
	UGameInstance *game_inst = 0;

	Super::NativeConstruct();

	game_inst = GetGameInstance();
	check(game_inst != 0);

	Localization_Manager = game_inst->GetSubsystem<ULocalization_Manager_Subsystem>();
	check(Localization_Manager != 0);
	Localization_Manager->On_Language_Changed.AddDynamic(this, &UMain_Menu_Buttons_Widget::Update_Text);

	Decibel_Game_Inst = GetGameInstance<UDecibel_Game_Instance>();
	check(Decibel_Game_Inst != 0);

	check(New_Game_Button != 0);
	New_Game_Button->Get_On_Clicked().AddDynamic(this, &UMain_Menu_Buttons_Widget::On_New_Game_Clicked);

	check(Load_Game_Button != 0);
	Load_Game_Button->Get_On_Clicked().AddDynamic(this, &UMain_Menu_Buttons_Widget::On_Load_Game_Clicked);

	check(Quit_Game_Button != 0);
	Quit_Game_Button->Get_On_Clicked().AddDynamic(this, &UMain_Menu_Buttons_Widget::On_Quit_Game_Clicked);

	Setup_Combo_Box();

	curr_language = Localization_Manager->Get_Language();
	Update_Text(curr_language);
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Buttons_Widget::Setup_Combo_Box()
{
	ELanguage curr_language_code;

	check(Languages_Combo_Box != 0);
	Languages_Combo_Box->OnSelectionChanged.AddDynamic(this, &UMain_Menu_Buttons_Widget::Change_Language);

	for (const auto &language_pair : FLocalization_Data::Languages)
		Languages_Combo_Box->AddOption(language_pair.Key);

	curr_language_code = Localization_Manager->Get_Language();
	const FString *curr_language = FLocalization_Data::Reverse_Languages.Find(curr_language_code);
	check(curr_language != 0);

	Languages_Combo_Box->SetSelectedOption(*curr_language);
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Buttons_Widget::Update_Text(ELanguage new_language)
{
	check(Localization_Manager != 0);

	check(New_Game_Button != 0);
	New_Game_Button->Set_Text_By_Key(TEXT("New_Game"));

	check(Load_Game_Button != 0);
	Load_Game_Button->Set_Text_By_Key(TEXT("Load_Game"));

	check(Quit_Game_Button != 0);
	Quit_Game_Button->Set_Text_By_Key(TEXT("Quit_Game"));
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Buttons_Widget::On_New_Game_Clicked()
{
	On_Show_Save_Slots.Broadcast(ESlot_Save_State::New_Game);
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Buttons_Widget::On_Load_Game_Clicked()
{
	On_Show_Save_Slots.Broadcast(ESlot_Save_State::Load_Game);
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Buttons_Widget::On_Quit_Game_Clicked()
{
	check(Decibel_Game_Inst != 0);
	Decibel_Game_Inst->Quit_Game();
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Buttons_Widget::Change_Language(FString new_language, ESelectInfo::Type SelectionType)
{
	UGameInstance *game_inst = 0;
	ULocalization_Manager_Subsystem *localization_manager_subsys = 0; 

	game_inst = GetGameInstance();
	check(game_inst != 0);

	localization_manager_subsys = game_inst->GetSubsystem<ULocalization_Manager_Subsystem>();
	check(localization_manager_subsys != 0);

	ELanguage new_language_code = FLocalization_Data::Languages[new_language];
	localization_manager_subsys->Set_Language(new_language_code);
}
//------------------------------------------------------------------------------------------------------------
