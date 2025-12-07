#pragma once

#include "GameFramework/HUD.h"
#include "Data/Keycard_Type/Keycard_Type.h"
#include "Decibel_HUD.generated.h"

class UPause_Menu_Widget;
class UGame_Saving_Widget;
class UKeycards_Widget;

// ADecibel_HUD
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API ADecibel_HUD: public AHUD
{
	GENERATED_BODY()

public:
	ADecibel_HUD();
	void Add_Keycard(EKeycard_Type keycard_type);
	UFUNCTION(BlueprintCallable) void Show_Credits();

protected:
	virtual void BeginPlay();
	UPROPERTY(EditAnywhere) float Game_Saved_Showing_Time;
	UPROPERTY(EditAnywhere) TSubclassOf<UPause_Menu_Widget> Pause_Menu_Widget_BP_Class;
	UPROPERTY(EditAnywhere) TSubclassOf<UGame_Saving_Widget> Game_Saving_Widget_BP_Class;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> Crosshair_Widget_BP_Class;
	UPROPERTY(EditAnywhere) TSubclassOf<UKeycards_Widget> Keycards_Widget_BP_Class;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> Credits_RU_Widget_BP_Class;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> Credits_EN_Widget_BP_Class;

private:
	UFUNCTION() void Show_Pause_Menu(bool is_visible);
	UFUNCTION() void Show_Game_Saved();
	UFUNCTION() void Hide_Game_Saved();

	bool Is_Pause_Menu_Visible;
	FTimerHandle Game_Save_Timer;
	UPause_Menu_Widget *Pasue_Menu_Widget = 0;
	UGame_Saving_Widget *Game_Saving_Widget = 0;
	UUserWidget *Crosshair_Widget = 0;
	UUserWidget *Credits_Widget = 0;
	UKeycards_Widget *Keycards_Widget = 0;
};
//------------------------------------------------------------------------------------------------------------
