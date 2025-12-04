#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Chasing_Player.generated.h"

class AAIController;
class UBlackboardComponent;

// UBTTask_Chasing_Player
//------------------------------------------------------------------------------------------------------------
UCLASS() class UBTTask_Chasing_Player : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Chasing_Player(FObjectInitializer const &object_initializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory);
	virtual void TickTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory, float delta_seconds);

	UPROPERTY(EditAnywhere) FBlackboardKeySelector Player_Character_Key;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Is_Player_In_Chasing_Range_Key;
	UPROPERTY(EditAnywhere) float Acceptance_Radius;
	UPROPERTY(EditAnywhere) double Lose_Distance;

private:
	ACharacter *Get_Target_Character();

	AAIController *AI_Controller = 0;
	UBlackboardComponent *Blackboard_Comp = 0;
};
//------------------------------------------------------------------------------------------------------------
