#pragma once

#include "Blueprint/UserWidget.h"
#include "Data/Keycard_Type/Keycard_Type.h"
#include "Keycards_Widget.generated.h"

class UImage;

// UKeycards_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UKeycards_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UKeycards_Widget(const FObjectInitializer &object_initializer);
	void Add_Keycard(EKeycard_Type keycard_type);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UImage *Yellow_Keycard = 0;
	UPROPERTY(meta = (BindWidget)) UImage *Blue_Keycard = 0;
	UPROPERTY(meta = (BindWidget)) UImage *Red_Keycard = 0;
};
//------------------------------------------------------------------------------------------------------------
