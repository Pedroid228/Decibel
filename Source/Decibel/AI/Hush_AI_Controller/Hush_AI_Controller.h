#pragma once

#include "AIController.h"

#include "Hush_AI_Controller.generated.h"

// AHush_AI_Controller
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AHush_AI_Controller: public AAIController
{
	GENERATED_BODY()

public:
	AHush_AI_Controller(const FObjectInitializer &object_initializer);

protected:
	virtual void OnPossess(APawn *in_pawn);
};
//------------------------------------------------------------------------------------------------------------
