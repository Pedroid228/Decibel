#pragma once

#include "Blueprint/UserWidget.h"
#include "Data/Slot_Save_State/Slot_Save_State.h"
#include "Data/Localization_Data/Localization_Data.h"
#include "Main_Menu_Buttons_Widget.generated.h"

class UDecibel_Button_Widget;
class UComboBoxString;
class UDecibel_Game_Instance;
class USaves_List_Widget;
class ULocalization_Manager_Subsystem;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Show_Save_Slots, ESlot_Save_State, SaveState);

// UMain_Menu_Buttons_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UMain_Menu_Buttons_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UMain_Menu_Buttons_Widget(const FObjectInitializer &object_initializer);
	FOn_Show_Save_Slots On_Show_Save_Slots;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UDecibel_Button_Widget *New_Game_Button;
	UPROPERTY(meta = (BindWidget)) UDecibel_Button_Widget *Load_Game_Button;
	UPROPERTY(meta = (BindWidget)) UDecibel_Button_Widget *Quit_Game_Button;
	UPROPERTY(meta = (BindWidget)) UComboBoxString *Languages_Combo_Box = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Greetings_Text = 0;

private:
	void Setup_Combo_Box();
	UFUNCTION() void Update_Text(ELanguage new_language);
	UFUNCTION() void On_New_Game_Clicked();
	UFUNCTION() void On_Load_Game_Clicked();
	UFUNCTION() void On_Quit_Game_Clicked();
	UFUNCTION() void Change_Language(FString new_language, ESelectInfo::Type SelectionType);

	UDecibel_Game_Instance *Decibel_Game_Inst = 0;
	ULocalization_Manager_Subsystem *Localization_Manager = 0; 
};
//------------------------------------------------------------------------------------------------------------
