#pragma once

#include "GameFramework/Actor.h"

#include "Controlled_Door.generated.h"

// AControlled_Door
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AControlled_Door: public AActor
{
	GENERATED_BODY()

public:
	AControlled_Door();
	void Update_Pos_Offset(double percent);

protected:
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Offset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Offset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) USceneComponent *Root_Scene = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) UStaticMeshComponent *Mesh = 0;
};
//------------------------------------------------------------------------------------------------------------
