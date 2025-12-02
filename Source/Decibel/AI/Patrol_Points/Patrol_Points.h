#pragma once

#include "GameFramework/Actor.h"

#include "Patrol_Points.generated.h"

// APatrol_Points
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API APatrol_Points: public AActor
{
	GENERATED_BODY()

public:
	APatrol_Points();
	int32 Num();
	FVector Get_Point_By_Index(int32 index);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true")) TArray<FVector> Points;
};
//------------------------------------------------------------------------------------------------------------
