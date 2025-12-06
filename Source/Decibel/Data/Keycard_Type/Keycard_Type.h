#pragma once

#include "Keycard_Type.generated.h"

// EKeycard_Type
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class EKeycard_Type: uint8
{
	None,
	Yellow,
	Red,
	Blue
};
//------------------------------------------------------------------------------------------------------------




// FKeycard_Color_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct DECIBEL_API FKeycard_Color_Data
{
	GENERATED_BODY()

	static const TMap<EKeycard_Type, FLinearColor> Colors;
};
//------------------------------------------------------------------------------------------------------------