#include "Astronaut.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Sound_Emitter_Component/Sound_Emitter_Component.h"
#include "Components/Trace_Interaction_Component/Trace_Interaction_Component.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Trace_Interaction_Interface/Trace_Interaction_Interface.h"
#include "Subsystems/Sounds_Manager_Subsystem/Sounds_Manager_Subsystem.h"

// AAstronaut
//------------------------------------------------------------------------------------------------------------
AAstronaut::AAstronaut(): Walk_Speed(500.0), Run_Speed(700.0), Is_Input_Disabled(false), Astronaut_State(EAstronaut_State::Idle)
{
	USceneComponent *root_comp = 0;

	root_comp = GetRootComponent();
	check(root_comp != 0);

	Spring_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring_Arm_Comp"));
	check(Spring_Arm != 0);
	Spring_Arm->SetupAttachment(root_comp);
	Spring_Arm->SetRelativeLocation(FVector(0.0, 0.0, 55.0));
	Spring_Arm->TargetArmLength = 0.0f;
	Spring_Arm->bUsePawnControlRotation = true;
	Spring_Arm->bEnableCameraLag = true;
	Spring_Arm->bEnableCameraRotationLag = true;

	Player_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player_Camera_Comp"));
	check(Player_Camera != 0);
	Player_Camera->SetupAttachment(Spring_Arm);

	Arms_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms_Mesh_Comp"));
	check(Arms_Mesh != 0);
	Arms_Mesh->SetupAttachment(Player_Camera);

	Trace_Interaction_Component = CreateDefaultSubobject<UTrace_Interaction_Component>(TEXT("Trace_Interaction_Comp"));
	check(Trace_Interaction_Component != 0);

	Footsteps_Sound_Component = CreateDefaultSubobject<UFootsteps_Sound_Component>(TEXT("Footsteps_Sound_Comp"));
	check(Footsteps_Sound_Component != 0);

	Sound_Emitter_Component = CreateDefaultSubobject<USound_Emitter_Component>(TEXT("Sound_Emitter_Comp"));
	check(Sound_Emitter_Component != 0);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Save_Implementation(FActor_Save_Data &save_data)
{
	save_data.Actor_Path_Name = GetPathNameSafe(this);
	save_data.Transform = GetActorTransform();
	save_data.Astronaut_Save_Data.Has_Key_Card = true;
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	SetActorTransform(save_data.Transform);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::Tick(float delta_time)
{
	FVector line_trace_start;
	FVector line_trace_dir;
	FRotator player_view_rotation;
	APlayerController *player_controller = 0;

	Super::Tick(delta_time);

	player_controller = Get_Player_Controller();
	player_controller->GetPlayerViewPoint(line_trace_start, player_view_rotation);

	line_trace_dir = player_view_rotation.Vector();

	Trace_Interaction_Component->Frame_Line_Trace(line_trace_start, line_trace_dir);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	UEnhancedInputComponent *enhanced_input_component = 0;
	APlayerController *player_controller = 0;
	UEnhancedInputLocalPlayerSubsystem *input_subsystem = 0;

	Super::SetupPlayerInputComponent(player_input_component);

	// Setup Mapping Context
	player_controller = Get_Player_Controller();

	input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer());
	input_subsystem->ClearAllMappings();
	input_subsystem->AddMappingContext(IMC_Default, 0);

	// Add bindings for input actions
	enhanced_input_component = Cast<UEnhancedInputComponent>(player_input_component);
	check(enhanced_input_component != 0);

	enhanced_input_component->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Move_Begin);
	enhanced_input_component->BindAction(IA_Move, ETriggerEvent::Completed, this, &AAstronaut::On_Action_Move_End);

	enhanced_input_component->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Look);

	enhanced_input_component->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Crouch_Begin);
	enhanced_input_component->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AAstronaut::On_Action_Crouch_End);

	enhanced_input_component->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Sprint_Begin);
	enhanced_input_component->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AAstronaut::On_Action_Sprint_End);

	enhanced_input_component->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Interact_Begin);
	enhanced_input_component->BindAction(IA_Interact, ETriggerEvent::Completed, this, &AAstronaut::On_Action_Interact_End);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::Set_State(EAstronaut_State new_state)
{
	if (new_state == Astronaut_State)
		return;

	switch (Astronaut_State)
	{
	case EAstronaut_State::Crouch:
		UnCrouch();
		break;

	case EAstronaut_State::Sprint:
		Set_Character_Speed(Walk_Speed);
	}

	switch (new_state)
	{
	case EAstronaut_State::Idle:
		break;

	case EAstronaut_State::Walk:
		Set_Character_Speed(Walk_Speed);
		break;

	case EAstronaut_State::Crouch:
		Crouch();
		break;

	case EAstronaut_State::Sprint:
		Set_Character_Speed(Run_Speed);
		break;

	default:
		checkf(false, TEXT("Invalid astronaut state: %d"), (int32)new_state);
	}

	check(Footsteps_Sound_Component != 0);
	Footsteps_Sound_Component->Set_State(new_state);

	Astronaut_State = new_state;
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Move_Begin(const FInputActionValue &value)
{
	FVector2D movement_input_vector = value.Get<FVector2D>();
	FVector forward_vector = GetActorForwardVector();
	FVector right_vector = GetActorRightVector();

	if (Is_Input_Disabled == true)
		return;

	AddMovementInput(forward_vector, movement_input_vector.Y);
	AddMovementInput(right_vector, movement_input_vector.X);

	if (Astronaut_State == EAstronaut_State::Idle)
		Set_State(EAstronaut_State::Walk);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Move_End()
{
	if (Astronaut_State == EAstronaut_State::Walk || Astronaut_State == EAstronaut_State::Sprint)
		Set_State(EAstronaut_State::Idle);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Look(const FInputActionValue &value)
{
	FVector2D look_axis_vector;

	if (Is_Input_Disabled == true)
		return;

	look_axis_vector = value.Get<FVector2D>();

	AddControllerYawInput(look_axis_vector.X);
	AddControllerPitchInput(-look_axis_vector.Y);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Crouch_Begin()
{
	Set_State(EAstronaut_State::Crouch);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Crouch_End()
{
	FVector velocity;
	velocity = GetVelocity();

	if (Astronaut_State == EAstronaut_State::Crouch)
	{
		if (velocity.IsNearlyZero())
			Set_State(EAstronaut_State::Idle);
		else
			Set_State(EAstronaut_State::Walk);
	}
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Sprint_Begin()
{
	if (Astronaut_State == EAstronaut_State::Walk || Astronaut_State == EAstronaut_State::Idle)
		Set_State(EAstronaut_State::Sprint);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Sprint_End()
{
	FVector velocity;
	velocity = GetVelocity();

	if (Astronaut_State == EAstronaut_State::Sprint)
	{
		if (velocity.IsNearlyZero())
			Set_State(EAstronaut_State::Idle);
		else
			Set_State(EAstronaut_State::Walk);
	}
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Interact_Begin()
{
	AActor *interactable_actor = 0;

	check(Trace_Interaction_Component != 0);
	interactable_actor = Trace_Interaction_Component->Get_Interactable_Actor();
	if (interactable_actor != 0)
	{
		Interacting_Actor = interactable_actor;
		ITrace_Interaction_Interface::Execute_On_Interact_Begin(interactable_actor, this);

		Is_Input_Disabled = true;
	}
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Interact_End()
{
	if (Interacting_Actor != 0)
	{
		ITrace_Interaction_Interface::Execute_On_Interact_End(Interacting_Actor);
		Interacting_Actor = 0;

		Is_Input_Disabled = false;
	}
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::Set_Character_Speed(double speed)
{
	UCharacterMovementComponent *movement_comp = 0;

	movement_comp = GetCharacterMovement();
	check(movement_comp != 0);

	movement_comp->MaxWalkSpeed = speed;
}
//------------------------------------------------------------------------------------------------------------
APlayerController *AAstronaut::Get_Player_Controller()
{
	UWorld *world = 0;
	APlayerController *player_controller = 0;

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

	return player_controller;
}
//------------------------------------------------------------------------------------------------------------
