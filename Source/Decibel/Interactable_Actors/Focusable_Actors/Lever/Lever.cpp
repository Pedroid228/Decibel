#include "Lever.h"
#include "Kismet/GameplayStatics.h"
#include "Interactable_Actors/Keycard_Scanner/Keycard_Scanner.h"
#include "Components/AudioComponent.h"
#include "Engine/PointLight.h"

// ALever
//------------------------------------------------------------------------------------------------------------
ALever::ALever(): Min_Angle(0.0), Max_Angle(360.0), Curr_Angle(0.0), Is_Active(false)
{
}
//------------------------------------------------------------------------------------------------------------
void ALever::On_Save_Implementation(FActor_Save_Data &save_data)
{
	Super::On_Save_Implementation(save_data);

	save_data.Lever_Angle = Curr_Angle;
}
//------------------------------------------------------------------------------------------------------------
void ALever::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	Super::On_Load_Implementation(save_data);

	Curr_Angle = save_data.Lever_Angle;
}
//------------------------------------------------------------------------------------------------------------
void ALever::BeginPlay()
{
	Super::BeginPlay();

	Curr_Angle = Min_Angle;
	Update_Rotation();

	check(Point_Light != 0);
	Point_Light->SetActorHiddenInGame(true);

	if (Generator_Sound != 0)
		Audio_Component->SetSound(Generator_Sound);
}
//------------------------------------------------------------------------------------------------------------
void ALever::Tick(float delta_time)
{
	Super::Tick(delta_time);

	if (Is_Interacting)
		Update_Angle();
}
//------------------------------------------------------------------------------------------------------------
void ALever::Update_Angle()
{
	bool new_active;
	double complete_percent;
	double vertical_movement;
	AKeycard_Scanner *curr_keycard_scanner = 0;
	TArray<AActor *> keycard_scanners;

	vertical_movement = Mouse_Move_Vector.Y * Sensivity;
	Curr_Angle = FMath::Clamp(Curr_Angle + vertical_movement, Min_Angle, Max_Angle);

	complete_percent = (Curr_Angle - Min_Angle) / (Max_Angle - Min_Angle);

	if (complete_percent >= 0.7)
		new_active = true;
	else
		new_active = false;

	if (Is_Active != new_active)
	{
		if (new_active)
		{
			Audio_Component->Play();
			Point_Light->SetActorHiddenInGame(false);
		}
		else
		{
			Audio_Component->Stop();
			Point_Light->SetActorHiddenInGame(true);
		}	

		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Keycard_Scanner_Tag"), keycard_scanners);

		for (AActor *keycard_scanner_actor : keycard_scanners)
		{
			check(keycard_scanner_actor != 0);
			curr_keycard_scanner = Cast<AKeycard_Scanner>(keycard_scanner_actor);
			check(curr_keycard_scanner != 0);
			curr_keycard_scanner->Activate(new_active);
		}
	}
	Is_Active = new_active;

	Update_Rotation();
}
//------------------------------------------------------------------------------------------------------------
void ALever::Update_Rotation()
{
	FRotator new_rotation;

	new_rotation = FRotator(0.0, 0.0, Curr_Angle);
	Mesh->SetRelativeRotation(new_rotation);
}
//------------------------------------------------------------------------------------------------------------
