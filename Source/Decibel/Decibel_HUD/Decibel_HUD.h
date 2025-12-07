#pragma once

#include "GameFramework/HUD.h"
#include "Decibel_HUD.generated.h"

class UPause_Menu_Widget;
class UGame_Saving_Widget;

// ADecibel_HUD
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API ADecibel_HUD: public AHUD
{
	GENERATED_BODY()

public:
	ADecibel_HUD();

protected:
	virtual void BeginPlay();
	UPROPERTY(EditAnywhere) float Game_Saved_Showing_Time;
	UPROPERTY(EditAnywhere) TSubclassOf<UPause_Menu_Widget> Pause_Menu_Widget_BP_Class;
	UPROPERTY(EditAnywhere) TSubclassOf<UGame_Saving_Widget> Game_Saving_Widget_BP_Class;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> Crosshair_Widget_BP_Class;

private:
	UFUNCTION() void Show_Pause_Menu(bool is_visible);
	UFUNCTION() void Show_Game_Saved();
	UFUNCTION() void Hide_Game_Saved();

	bool Is_Pause_Menu_Visible;
	FTimerHandle Game_Save_Timer;
	UPause_Menu_Widget *Pasue_Menu_Widget = 0;
	UGame_Saving_Widget *Game_Saving_Widget = 0;
	UUserWidget *Crosshair_Widget = 0;
};
//------------------------------------------------------------------------------------------------------------
