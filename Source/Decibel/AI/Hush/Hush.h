#pragma once

#include "GameFramework/Character.h"

#include "Hush.generated.h"

class UStaticMeshComponent;
class UBehaviorTree;
class UAI_Hearing_Component;

// AHush
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AHush: public ACharacter
{
	GENERATED_BODY()

public:
	AHush();

	UBehaviorTree *Get_BT();

protected:
	virtual void BeginPlay();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UAI_Hearing_Component *Hearing_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UBehaviorTree *BT = 0;
};
//------------------------------------------------------------------------------------------------------------
