#pragma once

#include "Sound_Stimulus.generated.h"

// ESound_Type
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class ESound_Type: uint8
{
	None,
	Walk,
	Run,
	Loud,
	High_Priority
};
//------------------------------------------------------------------------------------------------------------

// FSound_Stimulus
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct DECIBEL_API FSound_Stimulus
{
	GENERATED_BODY()

	FSound_Stimulus();
	FSound_Stimulus(ESound_Type type, const FVector &pos, AActor *instigator);

	static TMap<ESound_Type, double> Sounds_Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ESound_Type Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector Pos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor *Instigator = 0;
};
//------------------------------------------------------------------------------------------------------------
