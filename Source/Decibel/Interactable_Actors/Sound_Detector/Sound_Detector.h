#pragma once

#include "Interactable_Actors/Interactable_Actor/Interactable_Actor.h"
#include "Data/Interaction_Type/Interaction_Type.h"
#include "Sound_Detector.generated.h"

class UWidgetComponent;
class UDashboard_Gauge_Widget;
class USoundBase;
class UAudioComponent;

// ASound_Detector
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API ASound_Detector: public AInteractable_Actor
{
	GENERATED_BODY()

public:
	ASound_Detector();
	void Set_Active(bool is_active);

protected:
	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual void On_Interact_Begin_Implementation(AActor *interacting_actor);
	virtual void On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component);
	virtual void On_Trace_Leave_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Distance_To_Hush;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Distance_To_Hush;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Needle_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Needle_Angle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) UWidgetComponent *Dashboard_Gauge_Widget_Component = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UAudioComponent *Detector_Audio_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USoundBase *Detector_Meta_Sound = 0;

private:
	void Update_Dashboard_Gauge_Widget(double ratio);
	double Get_Min_Distance_To_Hush();
	bool Is_Grabbed;
	bool Is_Active;
	UDashboard_Gauge_Widget *Dashboard_Gauge_Widget = 0;
};
//------------------------------------------------------------------------------------------------------------
