#pragma once

#include "GameFramework/Actor.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"
#include "Save_Box.generated.h"

class UBoxComponent;

// ASave_Box
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API ASave_Box: public AActor, public ISaveable_Actor_Interface
{
	GENERATED_BODY()

public:
	ASave_Box();
	virtual void On_Save_Implementation(FActor_Save_Data &save_data) override;
	virtual void On_Load_Implementation(const FActor_Save_Data &save_data) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) UBoxComponent *Save_Trigger_Collision = 0;

private:
	UFUNCTION() void Save_Game(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool from_sweep, const FHitResult &sweep_result);
	bool Is_Active;
};
//------------------------------------------------------------------------------------------------------------
