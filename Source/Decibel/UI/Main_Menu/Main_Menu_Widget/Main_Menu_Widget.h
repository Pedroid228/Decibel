#pragma once

#include "Blueprint/UserWidget.h"
#include "Data/Slot_Save_State/Slot_Save_State.h"
#include "Data/Localization_Data/Localization_Data.h"
#include "Main_Menu_Widget.generated.h"

class UButton;
class UTextBlock;
class USaves_List_Widget;
class UMain_Menu_Buttons_Widget;
class ULocalization_Manager_Subsystem;

// UMain_Menu_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UMain_Menu_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UMain_Menu_Widget(const FObjectInitializer &object_initializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UMain_Menu_Buttons_Widget *Main_Menu_Buttons = 0;
	UPROPERTY(meta = (BindWidget)) USaves_List_Widget *Saves_List = 0;
	UPROPERTY(meta = (BindWidget)) UButton *Back_Button = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Back_Button_Text = 0;

private:
	UFUNCTION() void Update_Text(ELanguage new_language);
	UFUNCTION() void Show_Save_Slots(ESlot_Save_State state);
	UFUNCTION() void Hide_Save_Slots();

	ULocalization_Manager_Subsystem *Localization_Manager = 0; 
};
//------------------------------------------------------------------------------------------------------------
