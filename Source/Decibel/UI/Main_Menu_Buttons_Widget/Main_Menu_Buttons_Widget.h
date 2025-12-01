#pragma once

#include "Blueprint/UserWidget.h"
#include "Data/Slot_Save_State/Slot_Save_State.h"
#include "Main_Menu_Buttons_Widget.generated.h"

class UButton;
class UComboBoxString;
class UTextBlock;
class UDecibel_Game_Instance;
class USaves_List_Widget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Show_Save_Slots, ESlot_Save_State, SaveState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOn_Language_Changed);

// UMain_Menu_Buttons_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UMain_Menu_Buttons_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMain_Menu_Buttons_Widget(const FObjectInitializer &object_initializer);
	FOn_Show_Save_Slots On_Show_Save_Slots;
	FOn_Language_Changed On_Language_Changed;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UButton *New_Game_Button = 0;
	UPROPERTY(meta = (BindWidget)) UButton *Load_Game_Button = 0;
	UPROPERTY(meta = (BindWidget)) UButton *Quit_Game_Button = 0;
	UPROPERTY(meta = (BindWidget)) UComboBoxString *Languages_Combo_Box = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *New_Game_Text = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Load_Game_Text = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Quit_Game_Text = 0;

private:
	void Setup_Combo_Box();
	void Update_Text();
	UFUNCTION() void On_New_Game_Clicked();
	UFUNCTION() void On_Load_Game_Clicked();
	UFUNCTION() void On_Quit_Game_Clicked();
	UFUNCTION() void Change_Language(FString new_language, ESelectInfo::Type SelectionType);

	UDecibel_Game_Instance *Decibel_Game_Inst = 0;
};
//------------------------------------------------------------------------------------------------------------
