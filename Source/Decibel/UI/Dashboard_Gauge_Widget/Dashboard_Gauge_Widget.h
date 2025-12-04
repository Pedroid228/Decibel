#pragma once

#include "Blueprint/UserWidget.h"

#include "Dashboard_Gauge_Widget.generated.h"

class UImage;

// UDashboard_Gauge_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UDashboard_Gauge_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UDashboard_Gauge_Widget(const FObjectInitializer &object_initializer);
	void Set_Needle_Angles(double max_angle, double min_angle);
	UFUNCTION(BlueprintCallable) void Set_Target_Ratio(double new_target_ratio);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry &my_geometry, float delta_time) override;

	UPROPERTY(meta = (BindWidget)) UImage *Needle_Image = 0;
	UPROPERTY(meta = (BindWidget)) UImage *Gauge_Image = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double Min_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double Max_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double Animation_Speed;

private:
	void Update_Needle(float delta_time);

	bool Is_Needle_Moving;
	double Current_Ratio;
	double Target_Ratio;
};
//------------------------------------------------------------------------------------------------------------
