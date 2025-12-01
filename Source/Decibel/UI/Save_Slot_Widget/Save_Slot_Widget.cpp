#include "Save_Slot_Widget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Decibel_Game_Instance/Decibel_Game_Instance.h"

// USave_Slot_Widget
//------------------------------------------------------------------------------------------------------------
USave_Slot_Widget::USave_Slot_Widget(const FObjectInitializer &object_initializer): Super(object_initializer), Slot_Index(0)
{
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::Setup(int32 slot_index, ESlot_Save_State state)
{
	Slot_Index = slot_index;
	State = state;
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	check(Slot_Button != 0);
	Slot_Button->OnClicked.AddDynamic(this, &USave_Slot_Widget::On_Clicked);
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::NativeOnListItemObjectSet(UObject *list_item)
{
	USave_Slot_Widget *save_slot = 0;
	
	check(list_item != 0);
	
	IUserObjectListEntry::NativeOnListItemObjectSet(list_item);

	save_slot = Cast<USave_Slot_Widget>(list_item);
	check(save_slot != 0);
	
	Setup(save_slot->Slot_Index, save_slot->State);
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::On_Clicked()
{
	UDecibel_Game_Instance *decibel_game_inst = GetGameInstance<UDecibel_Game_Instance>();

	check(decibel_game_inst != 0);

	if (State == ESlot_Save_State::Load_Game)
		decibel_game_inst->Load_Game(Slot_Index);
	else
		if (State == ESlot_Save_State::New_Game)
			decibel_game_inst->New_Game(Slot_Index);
}
//------------------------------------------------------------------------------------------------------------
