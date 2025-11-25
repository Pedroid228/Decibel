#pragma once

#include "Misc/Guid.h"

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




// FActor_Component_Save_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FActor_Component_Save_Data
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FString Component_Path_Name;
};
//------------------------------------------------------------------------------------------------------------




// FActor_Save_Data
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FActor_Save_Data
{
	GENERATED_BODY()

	FActor_Save_Data();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FString Actor_Path_Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FTransform Transform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FAstronaut_Save_Data Astronaut_Save_Data;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) TArray<FActor_Component_Save_Data> Components_Save_Data;

};
//------------------------------------------------------------------------------------------------------------
