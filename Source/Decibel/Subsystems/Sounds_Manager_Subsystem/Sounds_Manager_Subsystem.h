#pragma once

#include "Data/Sound_Stimulus/Sound_Stimulus.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Sounds_Manager_Subsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSound_Stimulus_Delegate, const FSound_Stimulus &, Sound);

// USounds_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API USounds_Manager_Subsystem: public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USounds_Manager_Subsystem();
	virtual void Initialize(FSubsystemCollectionBase &Collection) override;
	virtual void Deinitialize() override;
	UFUNCTION(BlueprintCallable) static void Emit_Sound_At_Pos(const FSound_Stimulus &sound);

	static UPROPERTY() FSound_Stimulus_Delegate On_Sound_Stimulus_Emit;
};
//------------------------------------------------------------------------------------------------------------
