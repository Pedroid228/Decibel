#pragma once

#include "Components/ActorComponent.h"
#include "Interfaces/Saveable_Actor_Component_Interface/Saveable_Actor_Component_Interface.h"
#include "AI_Patrol_Component.generated.h"

class APatrol_Points;

// UAI_Patrol_Component
//------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class DECIBEL_API UAI_Patrol_Component: public UActorComponent, public ISaveable_Actor_Component_Interface
{
	GENERATED_BODY()

public:
	UAI_Patrol_Component(const FObjectInitializer &object_initializer);
	virtual void On_Save_Implementation(FActor_Component_Save_Data &save_data) override;
	virtual void On_Load_Implementation(const FActor_Component_Save_Data &save_data) override;
	FVector Get_Target_Point();

protected:
	virtual void BeginPlay();
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool Is_Enable_Patrolling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool Is_Random_Patrol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) APatrol_Points *Patrol_Points = 0;

private:
	FVector Get_Next_Target_Point();
	FVector Get_Random_Target_Point();
	int32 Curr_Point_Index;
};
//------------------------------------------------------------------------------------------------------------
