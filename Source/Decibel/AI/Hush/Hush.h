#pragma once

#include "GameFramework/Character.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"

#include "Hush.generated.h"

class UStaticMeshComponent;
class UBehaviorTree;
class UAI_Hearing_Component;
class UAI_Patrol_Component;

// AHush
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AHush: public ACharacter, public ISaveable_Actor_Interface
{
	GENERATED_BODY()

public:
	AHush();
	virtual void On_Save_Implementation(FActor_Save_Data &save_data) override;
	virtual void On_Load_Implementation(const FActor_Save_Data &save_data) override;
	UBehaviorTree *Get_BT();

protected:
	virtual void BeginPlay();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") UAI_Hearing_Component *Hearing_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") UAI_Patrol_Component *Patrol_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UBehaviorTree *BT = 0;
};
//------------------------------------------------------------------------------------------------------------
