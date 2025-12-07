#pragma once

#include "GameFramework/PlayerController.h"

#include "Decibel_Player_Controller.generated.h"

// ADecibel_Player_Controller
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API ADecibel_Player_Controller: public APlayerController
{
	GENERATED_BODY()

public:
	ADecibel_Player_Controller(const FObjectInitializer &object_initializer);

protected:
	virtual void SetupInputComponent();
	virtual void BeginPlay();

private:
	//UFUNCTION() void Load_Save();  // !!! Debug
	//UFUNCTION() void Save_Game();  // !!! Debug
	UFUNCTION() void Toggle_Pause();
};
//------------------------------------------------------------------------------------------------------------
