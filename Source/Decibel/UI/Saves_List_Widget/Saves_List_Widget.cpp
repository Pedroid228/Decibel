#include "Saves_List_Widget.h"
#include "UI/Save_Slot_Widget/Save_Slot_Widget.h"
#include "Subsystems/Save_Manager_Subsystem/Save_Manager_Subsystem.h"


// USaves_List_Widget
//------------------------------------------------------------------------------------------------------------
USaves_List_Widget::USaves_List_Widget(const FObjectInitializer &object_initializer): Super(object_initializer), State(ESlot_Save_State::None), Generated_Entries_Count(0)
{
}
//------------------------------------------------------------------------------------------------------------
void USaves_List_Widget::Set_State(ESlot_Save_State new_state)
{
	if (new_state != State)
	{
		Generated_Entries_Count = 0;
		State = new_state;
		Update();
	}
}
//------------------------------------------------------------------------------------------------------------
void USaves_List_Widget::Update()
{
	int32 i;
	UWorld *world = 0;
	USave_Slot_Widget *new_slot = 0;
	TSubclassOf<UUserWidget> entry_widget_class;

	world = GetWorld();
	check(world != 0);

	entry_widget_class = GetEntryWidgetClass();

	ClearListItems();

	for (i = 0; i < USave_Manager_Subsystem::Save_Slots_Count; i++)
	{
		new_slot = CreateWidget<USave_Slot_Widget>(world, entry_widget_class);
		check(new_slot != 0);
		new_slot->Setup(i, State);
		AddItem(new_slot);
	}
}
//------------------------------------------------------------------------------------------------------------