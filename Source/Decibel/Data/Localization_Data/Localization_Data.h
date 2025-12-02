#pragma once

#include "Localization_Data.generated.h"

// ELanguage
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class ELanguage: uint8
{
	None,
    En,
    Ru
};
//------------------------------------------------------------------------------------------------------------




// FLocalization_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct DECIBEL_API FLocalization_Data
{
	GENERATED_BODY()

	static const TMap<FString, ELanguage> Languages;
	static const TMap<ELanguage, FString> Reverse_Languages;
};
//------------------------------------------------------------------------------------------------------------
