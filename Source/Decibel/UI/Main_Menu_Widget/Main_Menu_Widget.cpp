#include "Main_Menu_Widget.h"
#include "UI/Saves_List_Widget/Saves_List_Widget.h"
#include "UI/Main_Menu_Buttons_Widget/Main_Menu_Buttons_Widget.h"
#include "UI/Save_Slot_Widget/Save_Slot_Widget.h"

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

	check(Saves_List != 0);
	Saves_List->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
void UMain_Menu_Widget::Show_Save_Slots(ESlot_Save_State state)
{
	check(Main_Menu_Buttons != 0);
	check(Saves_List != 0);

	Main_Menu_Buttons->SetVisibility(ESlateVisibility::Collapsed);
	Saves_List->SetVisibility(ESlateVisibility::Visible);
	Saves_List->Set_State(state);
}
//------------------------------------------------------------------------------------------------------------
