#pragma once

#include "Blueprint/UserWidget.h"
#include "Interaction_Widget.generated.h"

class UImage;
class UTexture2D;

// UInteraction_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UInteraction_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UInteraction_Widget(const FObjectInitializer &object_initializer);
	void Set_Texture(UTexture2D *texture);

protected:
	virtual void NativeConstruct();
	UPROPERTY(meta = (BindWidget)) UImage *Interaction_Image = 0;
};
//------------------------------------------------------------------------------------------------------------
