#pragma once

#include "Blueprint/UserWidget.h"
#include "Data/Localization_Data/Localization_Data.h"
#include "Game_Saving_Widget.generated.h"

class UTextBlock;

// UGame_Saving_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UGame_Saving_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UGame_Saving_Widget(const FObjectInitializer &object_initializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UTextBlock *Saving_Text = 0;
};
//------------------------------------------------------------------------------------------------------------
