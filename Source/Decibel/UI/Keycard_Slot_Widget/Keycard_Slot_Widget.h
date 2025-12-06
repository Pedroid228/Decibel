#pragma once

#include "Blueprint/UserWidget.h"
#include "Keycard_Slot_Widget.generated.h"

class UImage;

// UKeycard_Slot_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UKeycard_Slot_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UKeycard_Slot_Widget(const FObjectInitializer &object_initializer);
	void Set_Color(UMaterialInstanceDynamic *color_material);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UImage *Color_Image = 0;
	UPROPERTY(meta = (BindWidget)) UImage *Logo_Image = 0;
};
//------------------------------------------------------------------------------------------------------------
