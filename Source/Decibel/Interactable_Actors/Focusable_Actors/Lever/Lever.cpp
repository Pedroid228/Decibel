#include "Lever.h"

// ALever
//------------------------------------------------------------------------------------------------------------
ALever::ALever(): Min_Angle(0.0), Max_Angle(360.0), Curr_Angle(0.0)
{
	Curr_Angle = Min_Angle;
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
	Update_Rotation();
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
	double vertical_movement;

	vertical_movement = Mouse_Move_Vector.Y * Sensivity;
	Curr_Angle = FMath::Clamp(Curr_Angle + vertical_movement, Min_Angle, Max_Angle);

	Update_Rotation();
}
//------------------------------------------------------------------------------------------------------------
void ALever::Update_Rotation()
{
	FRotator new_rotation;

	new_rotation = FRotator(Curr_Angle, 0.0, 0.0);
	Mesh->SetRelativeRotation(new_rotation);
}
//------------------------------------------------------------------------------------------------------------
