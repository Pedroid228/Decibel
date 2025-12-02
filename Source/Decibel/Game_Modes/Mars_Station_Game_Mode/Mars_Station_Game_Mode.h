#pragma once

#include "GameFramework/GameModeBase.h"

#include "Mars_Station_Game_Mode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Pause, bool, is_paused);

// AMars_Station_Game_Mode
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AMars_Station_Game_Mode: public AGameModeBase
{
	GENERATED_BODY()

public:
	AMars_Station_Game_Mode();
	FOn_Pause On_Pause;

protected:
	virtual void BeginPlay();
	virtual bool SetPause(APlayerController* PC, FCanUnpause can_unpause_delegate = FCanUnpause()) override;
	virtual bool ClearPause() override;
};
//------------------------------------------------------------------------------------------------------------
