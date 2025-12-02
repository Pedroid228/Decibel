#pragma once

#include "GameFramework/HUD.h"
#include "Decibel_HUD.generated.h"

class UPause_Menu_Widget;

// ADecibel_HUD
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API ADecibel_HUD: public AHUD
{
	GENERATED_BODY()

public:
	ADecibel_HUD();

protected:
	virtual void BeginPlay();
	UPROPERTY(EditAnywhere) TSubclassOf<UPause_Menu_Widget> Pause_Menu_Widget_BP_Class;

private:
	UFUNCTION() void Show_Pause_Menu(bool is_visible);
	bool Is_Pause_Menu_Visible;
	UPause_Menu_Widget *Pasue_Menu_Widget = 0;
};
//------------------------------------------------------------------------------------------------------------
