#pragma once

#include "Blueprint/UserWidget.h"
#include "Pause_Menu_Widget.generated.h"

class UButton;
class UTextBlock;
class UDecibel_Game_Instance;

// UPause_Menu_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UPause_Menu_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UPause_Menu_Widget(const FObjectInitializer &object_initializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UButton *Main_Menu_Button = 0;
	UPROPERTY(meta = (BindWidget)) UButton *Save_Game_Button = 0;
	UPROPERTY(meta = (BindWidget)) UButton *Quit_Game_Button = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Main_Menu_Button_Text = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Save_Game_Button_Text = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Quit_Game_Button_Text = 0;

private:
	UFUNCTION() void On_Main_Menu_Clicked();
	UFUNCTION() void On_Save_Game_Clicked();
	UFUNCTION() void On_Quit_Game_Clicked();

	UDecibel_Game_Instance *Decibel_Game_Inst = 0;
};
//------------------------------------------------------------------------------------------------------------
