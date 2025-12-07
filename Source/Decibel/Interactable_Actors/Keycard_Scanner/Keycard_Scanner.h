#pragma once

#include "Interactable_Actors/Interactable_Actor/Interactable_Actor.h"
#include "Interfaces/Trace_Interaction_Interface/Trace_Interaction_Interface.h"
#include "Data/Interaction_Type/Interaction_Type.h"
#include "Data/Keycard_Type/Keycard_Type.h"
#include "Keycard_Scanner.generated.h"

class ALocked_Door;
class UPointLightComponent;

// AKeycard_Scanner
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AKeycard_Scanner: public AInteractable_Actor
{
	GENERATED_BODY()

public:
	AKeycard_Scanner();

protected:
	virtual void BeginPlay();
	virtual void On_Interact_Begin_Implementation(AActor *interacting_actor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly) EKeycard_Type Keycard_Type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Open_Time_Sec;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) ALocked_Door *Locked_Door = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) UPointLightComponent *Red_Light = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) UPointLightComponent *Green_Light = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interaction_Tip) UWidgetComponent *Keycard_Slot_Widget_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UMaterialInterface *Base_Color_Material = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound) USoundBase *Interaction_Sound_Success = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound) USoundBase *Interaction_Sound_Unsuccess = 0;


private:
	void Block_Door();
	void Update_Light(bool has_access);
	void Setup_Keycard_Slot_Widget();

	bool Is_Unlocked;
	FTimerHandle Door_Unlocked_Timer_Handle;
	UMaterialInstanceDynamic *MI_Color = 0;
};
//------------------------------------------------------------------------------------------------------------
