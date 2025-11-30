#pragma once

#include "Engine/GameInstance.h"
#include "Decibel_Game_Instance.generated.h"

class USave_Manager_Subsystem;

// UDecibel_Game_Instance
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API UDecibel_Game_Instance: public UGameInstance
{
	GENERATED_BODY()

public:
	UDecibel_Game_Instance();
	virtual void Init() override;
	void Main_Menu();
	void New_Game();
	void Load_Game();
	void Quit_Game();
	void Open_Level(const FName &map_name);

private:
	USave_Manager_Subsystem *Save_Manager = 0;
};
//------------------------------------------------------------------------------------------------------------
