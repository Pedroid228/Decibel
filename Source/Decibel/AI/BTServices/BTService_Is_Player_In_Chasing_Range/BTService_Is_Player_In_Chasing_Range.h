#pragma once

#include "BehaviorTree/Services/BTService_BlackBoardBase.h"
#include "BTService_Is_Player_In_Chasing_Range.generated.h"

// UBTService_Is_Player_In_Chasing_Range
//------------------------------------------------------------------------------------------------------------
UCLASS() class UBTService_Is_Player_In_Chasing_Range: public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_Is_Player_In_Chasing_Range();

protected:
	virtual void TickNode(UBehaviorTreeComponent &owner_comp, uint8 *node_memory, float delta_seconds);

	UPROPERTY(EditAnywhere) double Chasing_Range;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Is_Player_Chasing_In_Range;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Player_Character_Key;
};
//------------------------------------------------------------------------------------------------------------
