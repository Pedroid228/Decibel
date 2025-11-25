#pragma once

#include "Data/Save_Data/Actor_Save_Data/Actor_Save_Data.h"

#include "Decibel_Save_Data.generated.h"


// FDecibel_Save_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FDecibel_Save_Data
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) TArray<FActor_Save_Data> Actors_Save_Data;
};
//------------------------------------------------------------------------------------------------------------
