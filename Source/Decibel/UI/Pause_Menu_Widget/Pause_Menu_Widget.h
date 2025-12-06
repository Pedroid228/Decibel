#pragma once

#include "Blueprint/UserWidget.h"
#include "Pause_Menu_Widget.generated.h"

class UDecibel_Button_Widget;
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

	UPROPERTY(meta = (BindWidget)) UDecibel_Button_Widget *Main_Menu_Button = 0;
	UPROPERTY(meta = (BindWidget)) UDecibel_Button_Widget *Save_Game_Button = 0;
	UPROPERTY(meta = (BindWidget)) UDecibel_Button_Widget *Quit_Game_Button = 0;

private:
	UFUNCTION() void On_Main_Menu_Clicked();
	UFUNCTION() void On_Save_Game_Clicked();
	UFUNCTION() void On_Quit_Game_Clicked();

	UDecibel_Game_Instance *Decibel_Game_Inst = 0;
};
//------------------------------------------------------------------------------------------------------------
