#include "Dashboard_Gauge_Widget.h"

#include "Components/Image.h"

// UDashboard_Gauge_Widget
//------------------------------------------------------------------------------------------------------------
UDashboard_Gauge_Widget::UDashboard_Gauge_Widget(const FObjectInitializer &object_initializer)
: Super(object_initializer), Min_Angle(60.0), Max_Angle(-60.0), Animation_Speed(2.0), Is_Needle_Moving(false), Current_Ratio(0.0), Target_Ratio(0.0)
{
}
//------------------------------------------------------------------------------------------------------------
void UDashboard_Gauge_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	check(Needle_Image != 0);
	check(Gauge_Image != 0);
}
//------------------------------------------------------------------------------------------------------------
void UDashboard_Gauge_Widget::NativeTick(const FGeometry &my_geometry, float delta_time)
{
	Super::NativeTick(my_geometry, delta_time);
	Update_Needle(delta_time);
}
//------------------------------------------------------------------------------------------------------------
void UDashboard_Gauge_Widget::Set_Target_Ratio(double new_target_ratio)
{
	if (!FMath::IsNearlyEqual(Target_Ratio, new_target_ratio, 0.01f))
	{
		Target_Ratio = FMath::Clamp(new_target_ratio, 0.0, 1.0);
		Is_Needle_Moving = true;
	}
}
//------------------------------------------------------------------------------------------------------------
void UDashboard_Gauge_Widget::Update_Needle(float delta_time)
{
	float current_needle_angle;

	if (Is_Needle_Moving)
	{
		Current_Ratio = FMath::FInterpTo(Current_Ratio, Target_Ratio, (double)delta_time, Animation_Speed);

		if (FMath::IsNearlyEqual(Current_Ratio, Target_Ratio, 0.01f))
		{
			Current_Ratio = Target_Ratio;
			Is_Needle_Moving = false;
		}
	}

	check(Needle_Image != 0);
	current_needle_angle = (float)FMath::Lerp(Min_Angle, Max_Angle, Current_Ratio);
	Needle_Image->SetRenderTransformAngle(current_needle_angle);
}
//------------------------------------------------------------------------------------------------------------
