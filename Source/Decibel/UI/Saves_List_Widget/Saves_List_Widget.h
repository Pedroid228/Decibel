#pragma once

#include "Data/Slot_Save_State/Slot_Save_State.h"
#include "Components/ListView.h"
#include "Saves_List_Widget.generated.h"

class USave_Slot_Widget;

// USaves_List_View
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract, Blueprintable) class DECIBEL_API USaves_List_Widget: public UListView
{
	GENERATED_BODY()
	
public:
	USaves_List_Widget(const FObjectInitializer &object_initializer);
	void Set_State(ESlot_Save_State new_state);

private:
	void Update();
	ESlot_Save_State State;
	int32 Generated_Entries_Count;
	TArray<USave_Slot_Widget*> Slots;
};
//------------------------------------------------------------------------------------------------------------