#pragma once

#include "Misc/Guid.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"
#include "Actor_Save_Data.generated.h"

// FAstronaut_Save_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FAstronaut_Save_Data
{
	GENERATED_BODY()

	FAstronaut_Save_Data();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) bool Has_Key_Card;
};
//------------------------------------------------------------------------------------------------------------




// FHearing_Component_Save_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FHearing_Component_Save_Data
{
	GENERATED_BODY()

	FHearing_Component_Save_Data();
	FHearing_Component_Save_Data(bool has_heard_sound, bool has_high_priority_sound, ESound_Type curr_heard_sound_type, const FVector &curr_heard_sound_pos);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) bool Has_Heard_Sound;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) bool Has_High_Priority_Sound;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) ESound_Type Curr_Heard_Sound_Type;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FVector Curr_Heard_Sound_Pos;
};
//------------------------------------------------------------------------------------------------------------




// FActor_Component_Save_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FActor_Component_Save_Data
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FString Component_Class_Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) int32 Patrol_Point_Index;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FHearing_Component_Save_Data Hearing_Component_Save_Data;
};
//------------------------------------------------------------------------------------------------------------

// FActor_Save_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FActor_Save_Data
{
	GENERATED_BODY()

	FActor_Save_Data();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) double Hand_Door_Offset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) double Lever_Angle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) double Handwheel_Angle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FString Actor_Class_Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FTransform Transform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FAstronaut_Save_Data Astronaut_Save_Data;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) TArray<FActor_Component_Save_Data> Components_Save_Data;
};
//------------------------------------------------------------------------------------------------------------
