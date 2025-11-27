#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_Get_Patrol_Point.generated.h"

class AAIController;

// UBTTask_Get_Patrol_Point
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API UBTTask_Get_Patrol_Point: public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Get_Patrol_Point(const FObjectInitializer &object_initializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory) override;

protected:
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Curr_Patrol_Point;
};
//------------------------------------------------------------------------------------------------------------
