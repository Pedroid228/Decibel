#pragma once

#include "Components/Footsteps_Sound_Component/Footsteps_Sound_Component.h"
#include "GameFramework/Character.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"
#include "Data/Interaction_Type/Interaction_Type.h"
#include "Astronaut.generated.h"

class UInputMappingContext;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class USpringArmComponent;
class UTrace_Interaction_Component;
class USound_Emitter_Component;
class ULegacyCameraShake;
class ASound_Detector;
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
	bool Get_Has_Keycard();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void SetupPlayerInputComponent(UInputComponent *player_input_component) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool Has_Keycard;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Walk_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Run_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USpringArmComponent *Spring_Arm = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UCameraComponent *Player_Camera = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USceneComponent *Sound_Detector_Scene_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UTrace_Interaction_Component *Trace_Interaction_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UFootsteps_Sound_Component *Footsteps_Sound_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USound_Emitter_Component *Sound_Emitter_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputMappingContext *IMC_Default = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Move = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Look = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Crouch = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Sprint = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Instant_Interact = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Hold_Interact = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputAction *IA_Put_Away_Sound_Detector = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera_Shake) TSubclassOf<ULegacyCameraShake> Idle_Camera_Shake = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera_Shake) TSubclassOf<ULegacyCameraShake> Walk_Camera_Shake = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera_Shake) TSubclassOf<ULegacyCameraShake> Crouch_Camera_Shake = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera_Shake) TSubclassOf<ULegacyCameraShake> Run_Camera_Shake = 0;

private:
	void Set_State(EAstronaut_State new_state);
	void On_Action_Move_Begin(const FInputActionValue &value);
	void On_Action_Move_End();
	void On_Action_Look(const FInputActionValue &value);
	void On_Action_Crouch_Begin();
	void On_Action_Crouch_End();
	void On_Action_Sprint_Begin();
	void On_Action_Sprint_End();
	void On_Action_Instant_Interact();
	void On_Action_Hold_Interact_Begin();
	void On_Action_Hold_Interact_End();
	void On_Action_Put_Away_Sound_Detector();

	bool Start_Interact_By_Type(EInteraction_Type by_interaction_type);
	void Try_Attach_Sound_Detector(AActor *actor);
	void Set_Character_Speed(double speed);
	UFUNCTION() void On_Capsule_Hit(UPrimitiveComponent *hit_component, AActor *other_actor, UPrimitiveComponent *other_comp, FVector normal_impulse, const FHitResult &hit);
	void Die();
	APlayerController *Get_Player_Controller();

	bool Is_Input_Disabled;
	bool Is_Sound_Detector_In_Arms;
	EAstronaut_State Astronaut_State;
	TSubclassOf<ULegacyCameraShake> Curr_Camera_Shake = 0;
	ASound_Detector *Sound_Detector = 0;
	AActor *Interacting_Actor = 0;
};
//------------------------------------------------------------------------------------------------------------
