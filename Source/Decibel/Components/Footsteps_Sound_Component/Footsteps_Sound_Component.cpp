#include "Footsteps_Sound_Component.h"
#include "Components/Sound_Emitter_Component/Sound_Emitter_Component.h"
#include "Kismet/GameplayStatics.h"

// UFootsteps_Sound_Component
//------------------------------------------------------------------------------------------------------------
UFootsteps_Sound_Component::UFootsteps_Sound_Component(const FObjectInitializer &object_initializer)
: Super(object_initializer), Footstep_Interval_Walk(0.5), Footstep_Interval_Sprint(0.3), Sound_Type(ESound_Type::None), Curr_Footstep_Interval(0.0)
{
	PrimaryComponentTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void UFootsteps_Sound_Component::Set_State(EAstronaut_State new_state)
{
	switch (new_state)
	{
	case EAstronaut_State::Idle:
		Stop_Footsteps();
		break;

	case EAstronaut_State::Walk:
		Curr_Footstep_Interval = Footstep_Interval_Walk;
		Sound_Type = ESound_Type::Walk;
		Start_Footsteps();
		break;

	case EAstronaut_State::Sprint:
		Curr_Footstep_Interval = Footstep_Interval_Sprint;
		Sound_Type = ESound_Type::Run;
		Start_Footsteps();
		break;

	case EAstronaut_State::Crouch:
		Stop_Footsteps();
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void UFootsteps_Sound_Component::BeginPlay()
{
	Super::BeginPlay();
	check(Footstep_Sound != 0);
}
//------------------------------------------------------------------------------------------------------------
void UFootsteps_Sound_Component::Start_Footsteps()
{
	UWorld *world = 0;

	world = GetWorld();
	check(world != 0);

	world->GetTimerManager().ClearTimer(Footsteps_Timer_Handle);
    world->GetTimerManager().SetTimer(Footsteps_Timer_Handle, this, &UFootsteps_Sound_Component::Play_Footstep_Sound, Curr_Footstep_Interval, true);
}
//------------------------------------------------------------------------------------------------------------
void UFootsteps_Sound_Component::Stop_Footsteps()
{
	UWorld *world = 0;

	world = GetWorld();
	check(world != 0);

	Curr_Footstep_Interval = 0.0;
	Sound_Type = ESound_Type::None;
	world->GetTimerManager().ClearTimer(Footsteps_Timer_Handle);
}
//------------------------------------------------------------------------------------------------------------
void UFootsteps_Sound_Component::Play_Footstep_Sound()
{
	AActor *owner = 0;
	FVector owner_pos;

	owner = GetOwner();
	check(owner != 0)

	owner_pos = owner->GetActorLocation();

	UGameplayStatics::PlaySoundAtLocation(this, Footstep_Sound, owner_pos);
	Emit_Sound(owner, owner_pos);
}
//------------------------------------------------------------------------------------------------------------
void UFootsteps_Sound_Component::Emit_Sound(AActor *owner, const FVector &owner_pos)
{
	USound_Emitter_Component *sound_emitter_comp = 0;
	FSound_Stimulus sound_stimulus;

	sound_emitter_comp = owner->GetComponentByClass<USound_Emitter_Component>();
	check(sound_emitter_comp != 0);

	sound_stimulus = FSound_Stimulus(Sound_Type, owner_pos, owner);
	sound_emitter_comp->Emit_Sound_At_Pos(sound_stimulus);
}
//------------------------------------------------------------------------------------------------------------
