#include "Hush_AI_Controller.h"

#include "AI/Hush/Hush.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// AHush_AI_Controller
//------------------------------------------------------------------------------------------------------------
AHush_AI_Controller::AHush_AI_Controller(const FObjectInitializer &object_initializer): Super(object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void AHush_AI_Controller::OnPossess(APawn *in_pawn)
{
	AHush *hush = 0;
	UBehaviorTree *bt = 0;
	UBlackboardData *blackboard_asset = 0;
	UBlackboardComponent *blackboard_comp = 0;

	Super::OnPossess(in_pawn);

	hush = Cast<AHush>(in_pawn);
	check(hush != 0);

	bt = hush->Get_BT();
	check(bt != 0);

	blackboard_asset = bt->GetBlackboardAsset();
	check(blackboard_asset != 0);

	UseBlackboard(blackboard_asset, blackboard_comp);
	Blackboard = blackboard_comp;
	check(Blackboard != 0);

	RunBehaviorTree(bt);
}
//------------------------------------------------------------------------------------------------------------
