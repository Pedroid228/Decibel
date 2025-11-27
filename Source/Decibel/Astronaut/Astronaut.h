#pragma once

#include "GameFramework/Character.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"

#include "Components/Footsteps_Sound_Component/Footsteps_Sound_Component.h"

#include "Astronaut.generated.h"

class UInputMappingContext;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class USpringArmComponent;
class UTrace_Interaction_Component;
class USound_Emitter_Component;

struct FInputActionValue;

// AAstronaut
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AAstronaut: public ACharacter, public ISaveable_Actor_Interface
{
	GENERATED_BODY()

public:
	AAstronaut();
	virtual void On_Save_Implementation(FActor_Save_Data &save_data) override;
    virtual void On_Load_Implementation(const FActor_Save_Data &save_data) override;

protected:
	virtual void Tick(float delta_time) override;
	virtual void SetupPlayerInputComponent(UInputComponent *player_input_component) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Walk_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Run_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USpringArmComponent *Spring_Arm = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UCameraComponent *Player_Camera = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USkeletalMeshComponent *Arms_Mesh = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UTrace_Interaction_Component *Trace_Interaction_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UFootsteps_Sound_Component *Footsteps_Sound_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USound_Emitter_Component *Sound_Emitter_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputMappingContext *IMC_Default = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Move = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Look = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Crouch = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Sprint = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Interact = 0;

private:
	void Set_State(EAstronaut_State new_state);
	void On_Action_Move_Begin(const FInputActionValue &value);
	void On_Action_Move_End();
	void On_Action_Look(const FInputActionValue &value);
	void On_Action_Crouch_Begin();
	void On_Action_Crouch_End();
	void On_Action_Sprint_Begin();
	void On_Action_Sprint_End();
	void On_Action_Interact_Begin();
	void On_Action_Interact_End();

	void Set_Character_Speed(double speed);

	APlayerController *Get_Player_Controller();

	EAstronaut_State Astronaut_State;
	AActor *Interacting_Actor = 0;
};
//------------------------------------------------------------------------------------------------------------
