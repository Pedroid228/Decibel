#include "Astronaut.h"

#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Sound_Emitter_Component/Sound_Emitter_Component.h"
#include "Components/Trace_Interaction_Component/Trace_Interaction_Component.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactable_Actors/Sound_Detector/Sound_Detector.h"
#include "Interfaces/Trace_Interaction_Interface/Trace_Interaction_Interface.h"
#include "Shakes/LegacyCameraShake.h"
#include "Subsystems/Sounds_Manager_Subsystem/Sounds_Manager_Subsystem.h"
#include "Decibel_Game_Instance/Decibel_Game_Instance.h"

// AAstronaut
//------------------------------------------------------------------------------------------------------------
AAstronaut::AAstronaut(): Has_Keycard(false), Walk_Speed(500.0), Run_Speed(700.0), Is_Input_Disabled(false), Astronaut_State(EAstronaut_State::None)
{
	UCapsuleComponent *player_capsule;

	check(RootComponent != 0);

	player_capsule = GetCapsuleComponent();
	check(player_capsule != 0);
	player_capsule->OnComponentHit.AddDynamic(this, &AAstronaut::On_Capsule_Hit);

	Spring_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring_Arm_Comp"));
	check(Spring_Arm != 0);
	Spring_Arm->SetupAttachment(RootComponent);
	Spring_Arm->SetRelativeLocation(FVector(0.0, 0.0, 55.0));
	Spring_Arm->TargetArmLength = 0.0f;
	Spring_Arm->bUsePawnControlRotation = true;
	Spring_Arm->bEnableCameraLag = true;
	Spring_Arm->bEnableCameraRotationLag = true;

	Player_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player_Camera_Comp"));
	check(Player_Camera != 0);
	Player_Camera->SetupAttachment(Spring_Arm);

	Sound_Detector_Scene_Component = CreateDefaultSubobject<USceneComponent>(TEXT("Sound_Detector_Scene_Comp"));
	check(Sound_Detector_Scene_Component != 0);
	Sound_Detector_Scene_Component->SetupAttachment(Player_Camera);

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
	save_data.Actor_Class_Name = GetClass()->GetName();
	save_data.Transform = GetActorTransform();
	save_data.Astronaut_Save_Data.Has_Key_Card = true;
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	SetActorTransform(save_data.Transform);
}
//------------------------------------------------------------------------------------------------------------
bool AAstronaut::Get_Has_Keycard()
{
	return Has_Keycard;
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::BeginPlay()
{
	Super::BeginPlay();

	check(Idle_Camera_Shake != 0);
	check(Walk_Camera_Shake != 0);
	check(Crouch_Camera_Shake != 0);
	check(Run_Camera_Shake != 0);

	Set_State(EAstronaut_State::Idle);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::Tick(float delta_time)
{
	FVector line_trace_start;
	FVector line_trace_dir;
	FRotator player_view_rotation;
	APlayerController *player_controller = 0;
	APlayerCameraManager *player_camera_manager = 0;

	Super::Tick(delta_time);

	player_controller = Get_Player_Controller();
	player_controller->GetPlayerViewPoint(line_trace_start, player_view_rotation);

	line_trace_dir = player_view_rotation.Vector();

	Trace_Interaction_Component->Frame_Line_Trace(line_trace_start, line_trace_dir);

	player_camera_manager = player_controller->PlayerCameraManager;
	check(player_camera_manager != 0);
	check(Curr_Camera_Shake != 0);
	player_camera_manager->StartCameraShake(Curr_Camera_Shake);
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

	enhanced_input_component->BindAction(IA_Instant_Interact, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Instant_Interact);

	enhanced_input_component->BindAction(IA_Hold_Interact, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Hold_Interact_Begin);
	enhanced_input_component->BindAction(IA_Hold_Interact, ETriggerEvent::Completed, this, &AAstronaut::On_Action_Hold_Interact_End);

	enhanced_input_component->BindAction(IA_Put_Away_Sound_Detector, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Put_Away_Sound_Detector);
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
		Curr_Camera_Shake = Idle_Camera_Shake;
		break;

	case EAstronaut_State::Walk:
		Set_Character_Speed(Walk_Speed);
		Curr_Camera_Shake = Walk_Camera_Shake;
		break;

	case EAstronaut_State::Crouch:
		Crouch();
		Curr_Camera_Shake = Crouch_Camera_Shake;
		break;

	case EAstronaut_State::Sprint:
		Set_Character_Speed(Run_Speed);
		Curr_Camera_Shake = Run_Camera_Shake;
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
void AAstronaut::On_Action_Instant_Interact()
{
	Start_Interact_By_Type(EInteraction_Type::Instant);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Hold_Interact_Begin()
{
	if (Start_Interact_By_Type(EInteraction_Type::Hold_And_Drag))
		Is_Input_Disabled = true;
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Hold_Interact_End()
{
	if (Interacting_Actor != 0)
	{
		ITrace_Interaction_Interface::Execute_On_Interact_End(Interacting_Actor);
		Interacting_Actor = 0;

		Is_Input_Disabled = false;
	}
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Put_Away_Sound_Detector()
{
	bool is_hidden;

	if (Sound_Detector == 0)
		return;

	if (Is_Sound_Detector_In_Arms)
	{
		is_hidden = true;
		Is_Sound_Detector_In_Arms = false;
	}
	else
	{
		is_hidden = false;
		Is_Sound_Detector_In_Arms = true;
	}

	Sound_Detector->Set_Active(Is_Sound_Detector_In_Arms);
	Sound_Detector->SetActorHiddenInGame(is_hidden);
}
//------------------------------------------------------------------------------------------------------------
bool AAstronaut::Start_Interact_By_Type(EInteraction_Type by_interaction_type)
{
	EInteraction_Type interaction_type;
	AActor *interactable_actor = 0;

	check(Trace_Interaction_Component != 0);
	interactable_actor = Trace_Interaction_Component->Get_Interactable_Actor();

	if (interactable_actor != 0)
	{
		interaction_type = ITrace_Interaction_Interface::Execute_Get_Interaction_Type(interactable_actor);

		if (interaction_type != by_interaction_type)
			return false;

		if (interaction_type == EInteraction_Type::Hold_And_Drag && Is_Sound_Detector_In_Arms)
			return false;

		ITrace_Interaction_Interface::Execute_On_Interact_Begin(interactable_actor, this);

		if (interaction_type == EInteraction_Type::Instant)
			Try_Attach_Sound_Detector(interactable_actor);
		else if (interaction_type == EInteraction_Type::Hold_And_Drag)
			Interacting_Actor = interactable_actor;

		return true;
	}

	return false;
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::Try_Attach_Sound_Detector(AActor *actor)
{
	if (Sound_Detector != 0)
		return;

	Sound_Detector = Cast<ASound_Detector>(actor);
	if (Sound_Detector != 0)
	{
		Sound_Detector->AttachToComponent(Sound_Detector_Scene_Component, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Is_Sound_Detector_In_Arms = true;
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
void AAstronaut::On_Capsule_Hit(UPrimitiveComponent *hit_component, AActor *other_actor, UPrimitiveComponent *other_comp, FVector normal_impulse, const FHitResult &hit)
{
	check(other_actor != 0);

	if (other_actor->ActorHasTag(TEXT("Hush_Tag")))
		Die();
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::Die()
{
	UDecibel_Game_Instance *game_inst = 0;

	game_inst = GetGameInstance<UDecibel_Game_Instance>();
	check(game_inst != 0);

	game_inst->Load_Curr_Game();
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
