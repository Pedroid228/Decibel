#pragma once

#include "GameFramework/GameModeBase.h"

#include "Main_Menu_Game_Mode.generated.h"

class UMain_Menu_Widget;

// AMain_Menu_Game_Mode
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AMain_Menu_Game_Mode: public AGameModeBase
{
	GENERATED_BODY()

public:
	AMain_Menu_Game_Mode();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere) TSubclassOf<UMain_Menu_Widget> Main_Menu_Widget_BP_Class = 0;

private:
	void Create_And_Show_Main_Menu_Widget(APlayerController *player_controller);
	void Hide_And_Delete_Main_Menu_Widget();

	UMain_Menu_Widget *Main_Menu_Widget = 0;
};
//------------------------------------------------------------------------------------------------------------
