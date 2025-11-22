#include "Astronaut.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Trace_Interaction_Component/Trace_Interaction_Component.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Subsystems/Sounds_Manager_Subsystem/Sounds_Manager_Subsystem.h"

// AAstronaut
//------------------------------------------------------------------------------------------------------------
AAstronaut::AAstronaut(): Walk_Speed(500.0), Run_Speed(700.0), Astronaut_State(EAstronaut_State::Base)
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

	enhanced_input_component->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Move);
	enhanced_input_component->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Look);

	enhanced_input_component->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Crouch_Begin);
	enhanced_input_component->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AAstronaut::On_Action_Crouch_End);

	enhanced_input_component->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &AAstronaut::On_Action_Sprint_Begin);
	enhanced_input_component->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AAstronaut::On_Action_Sprint_End);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::Set_State(EAstronaut_State new_state)
{
	if (new_state == Astronaut_State)
		return;

	switch (new_state)
	{
	case EAstronaut_State::Base:
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

	Astronaut_State = new_state;
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Move(const FInputActionValue &value)
{
	FVector2D movement_input_vector = value.Get<FVector2D>();
	FVector forward_vector = GetActorForwardVector();
	FVector right_vector = GetActorRightVector();

	AddMovementInput(forward_vector, movement_input_vector.Y);
	AddMovementInput(right_vector, movement_input_vector.X);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Look(const FInputActionValue &value)
{
	FVector2D look_axis_vector = value.Get<FVector2D>();

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
	if (Astronaut_State == EAstronaut_State::Crouch)
	{
		UnCrouch();
		Set_State(EAstronaut_State::Base);
	}
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Sprint_Begin()
{
	Set_State(EAstronaut_State::Sprint);
}
//------------------------------------------------------------------------------------------------------------
void AAstronaut::On_Action_Sprint_End()
{
	if (Astronaut_State == EAstronaut_State::Sprint)
	{
		Set_Character_Speed(Walk_Speed);
		Set_State(EAstronaut_State::Base);
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
