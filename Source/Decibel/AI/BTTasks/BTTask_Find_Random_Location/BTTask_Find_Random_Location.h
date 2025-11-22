#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_Find_Random_Location.generated.h"

// UBTTask_Find_Random_Location
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API UBTTask_Find_Random_Location: public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Find_Random_Location(const FObjectInitializer &object_initializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Search_Radius;
};
//------------------------------------------------------------------------------------------------------------
