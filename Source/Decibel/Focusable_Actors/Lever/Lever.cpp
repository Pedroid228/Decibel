#include "Lever.h"

// ALever
//------------------------------------------------------------------------------------------------------------
ALever::ALever(): Min_Angle(0.0), Max_Angle(360.0), Curr_Angle(0.0)
{
	Curr_Angle = Min_Angle;
}
//------------------------------------------------------------------------------------------------------------
void ALever::Tick(float delta_time)
{
	Super::Tick(delta_time);

    if (Is_Interacting)
		Update_Rotation();
}
//------------------------------------------------------------------------------------------------------------
void ALever::Update_Rotation()
{
	double vertical_movement;
	FRotator new_rotation;

	vertical_movement = Mouse_Move_Vector.Y * Sensivity;

	Curr_Angle = FMath::Clamp(Curr_Angle + vertical_movement, Min_Angle, Max_Angle);

	new_rotation = FRotator(Curr_Angle, 0.0, 0.0);
	Mesh->SetRelativeRotation(new_rotation);
}
//------------------------------------------------------------------------------------------------------------
