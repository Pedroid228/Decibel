#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_Move_To_Last_Sound.generated.h"

class AAIController;

// UBTTask_Move_To_Last_Sound
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API UBTTask_Move_To_Last_Sound: public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Move_To_Last_Sound(const FObjectInitializer &object_initializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory) override;
	virtual void TickTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory, float delta_seconds) override;

protected:
	UPROPERTY(EditAnywhere) float Acceptance_Radius;
	UPROPERTY(EditAnywhere) float Wait_Time;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Curr_Sound_Pos_Key;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Curr_Sound_Type_Key;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Has_High_Priority_Sound_Key;

private:
	void Start_Move_To_Target(const FVector &new_target_pos);
	void Waiting(UBehaviorTreeComponent &owner_comp, float delta_seconds);
	void Complete_Task(UBehaviorTreeComponent &owner_comp);

	bool Is_Waiting;
	float Curr_Wait_Time;
	FVector Curr_Target_Pos;
	AAIController *AI_Controller = 0;
	APawn *NPC = 0;
	UBlackboardComponent *Blackboard = 0;
};
//------------------------------------------------------------------------------------------------------------
