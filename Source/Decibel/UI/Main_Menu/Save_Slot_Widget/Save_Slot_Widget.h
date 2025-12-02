#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Data/Slot_Save_State/Slot_Save_State.h"

#include "Save_Slot_Widget.generated.h"

class UButton;
class UTextBlock;
class UImage;

// USave_Slot_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API USave_Slot_Widget: public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	USave_Slot_Widget(const FObjectInitializer &object_initializer);
	void Setup(int32 slot_index, ESlot_Save_State state);

	ESlot_Save_State State;
	int32 Slot_Index;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject *list_item_obj) override;

	UPROPERTY(meta = (BindWidget)) UButton *Slot_Button = 0;
	UPROPERTY(meta = (BindWidget)) UImage *Screenshot_Image = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Slot_Number_Text = 0;

private:
	void Setup_Text();
	void Setup_Image();
	UFUNCTION() void On_Clicked();
};
//------------------------------------------------------------------------------------------------------------
