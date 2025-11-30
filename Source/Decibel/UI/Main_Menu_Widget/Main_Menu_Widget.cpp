#include "Main_Menu_Widget.h"

#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"
#include "Decibel_Game_Instance/Decibel_Game_Instance.h"
#include "Subsystems/Game_State_Manager_Subsystem/Game_State_Manager_Subsystem.h"
#include "Data/Localization_Data/Localization_Data.h"
#include "Kismet/KismetInternationalizationLibrary.h"

// UMain_Menu_Widget
//------------------------------------------------------------------------------------------------------------
UMain_Menu_Widget::UMain_Menu_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	check(New_Game_Button != 0);
	New_Game_Button->OnClicked.AddDynamic(this, &UMain_Menu_Widget::On_New_Game_Clicked);

	check(Load_Game_Button != 0);
	Load_Game_Button->OnClicked.AddDynamic(this, &UMain_Menu_Widget::On_Load_Game_Clicked);

	Setup_Combo_Box();
	Update_Text();

	Decibel_Game_Inst = GetGameInstance<UDecibel_Game_Instance>();
	check(Decibel_Game_Inst != 0);
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::Setup_Combo_Box()
{
	check(Languages_Combo_Box != 0);
	Languages_Combo_Box->OnSelectionChanged.AddDynamic(this, &UMain_Menu_Widget::On_Language_Changed);

	for (const auto &language_pair : FLocalization_Data::Languages)
		Languages_Combo_Box->AddOption(language_pair.Key);

	Languages_Combo_Box->SetSelectedOption(FLocalization_Data::Languages.begin()->Key);
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::Update_Text()
{
	check(New_Game_Text != 0);
	New_Game_Text->SetText(NSLOCTEXT("Main_Menu", "New_Game", "NEW GAME"));

	check(Load_Game_Text != 0);
	Load_Game_Text->SetText(NSLOCTEXT("Main_Menu", "Load_Game", "LOAD GAME"));

	check(Quit_Game_Text != 0);
	Quit_Game_Text->SetText(NSLOCTEXT("Main_Menu", "Quit_Game", "QUIT GAME"));
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::On_New_Game_Clicked()
{
	check(Decibel_Game_Inst != 0);
	Decibel_Game_Inst->New_Game();
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::On_Load_Game_Clicked()
{
	check(Decibel_Game_Inst != 0);
	Decibel_Game_Inst->Load_Game();
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::On_Quit_Game_Clicked()
{
	check(Decibel_Game_Inst != 0);
	Decibel_Game_Inst->Quit_Game();
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::On_Language_Changed(FString new_language, ESelectInfo::Type SelectionType)
{
	FString culture_code = FLocalization_Data::Languages[new_language];

	UKismetInternationalizationLibrary::SetCurrentCulture(culture_code, true);
	Update_Text();
}
//------------------------------------------------------------------------------------------------------------
