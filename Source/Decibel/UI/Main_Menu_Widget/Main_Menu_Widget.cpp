#include "Main_Menu_Widget.h"
#include "UI/Saves_List_Widget/Saves_List_Widget.h"
#include "UI/Main_Menu_Buttons_Widget/Main_Menu_Buttons_Widget.h"
#include "UI/Save_Slot_Widget/Save_Slot_Widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

// UMain_Menu_Widget
//------------------------------------------------------------------------------------------------------------
UMain_Menu_Widget::UMain_Menu_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	check(Main_Menu_Buttons != 0);
	Main_Menu_Buttons->SetVisibility(ESlateVisibility::Visible);
	Main_Menu_Buttons->On_Show_Save_Slots.AddDynamic(this, &UMain_Menu_Widget::Show_Save_Slots);
	Main_Menu_Buttons->On_Language_Changed.AddDynamic(this, &UMain_Menu_Widget::Update_Text);

	check(Saves_List != 0);
	Saves_List->SetVisibility(ESlateVisibility::Collapsed);

	check(Back_Button != 0);
	Back_Button->OnClicked.AddDynamic(this, &UMain_Menu_Widget::Hide_Save_Slots);
	Back_Button->SetVisibility(ESlateVisibility::Collapsed);

	Update_Text();
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::Update_Text()
{
	check(Back_Button_Text != 0);
	Back_Button_Text->SetText(NSLOCTEXT("Main_Menu", "Back", "BACK"));
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::Show_Save_Slots(ESlot_Save_State state)
{
	check(Main_Menu_Buttons != 0);
	check(Saves_List != 0);
	check(Back_Button != 0);

	Main_Menu_Buttons->SetVisibility(ESlateVisibility::Collapsed);
	Back_Button->SetVisibility(ESlateVisibility::Visible);
	Saves_List->SetVisibility(ESlateVisibility::Visible);
	Saves_List->Set_State(state);
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::Hide_Save_Slots()
{
	check(Main_Menu_Buttons != 0);
	check(Saves_List != 0);

	Main_Menu_Buttons->SetVisibility(ESlateVisibility::Visible);
	Back_Button->SetVisibility(ESlateVisibility::Collapsed);
	Saves_List->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
