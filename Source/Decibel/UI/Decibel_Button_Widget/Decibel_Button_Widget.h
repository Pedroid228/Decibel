#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Decibel_Button_Widget.generated.h"

class UImage;
class UTextBlock;
class UButton;
class UWidgetAnimation;

// UDecibel_Button_Widget
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API UDecibel_Button_Widget: public UUserWidget
{
	GENERATED_BODY()

public:
	UDecibel_Button_Widget(const FObjectInitializer &object_initializer);
	void Set_Text_By_Key(const FString &key);
	FOnButtonClickedEvent &Get_On_Clicked();

protected:
	virtual void NativeConstruct();
	UPROPERTY(meta = (BindWidget)) UButton *Hitbox = 0;
	UPROPERTY(meta = (BindWidget)) UTextBlock *Button_Text = 0;
	UPROPERTY(meta = (BindWidget)) UImage *Button_Image = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) UTexture2D *Default_Image = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UTexture2D *Hovered_Image = 0;

private:
	UFUNCTION() void Set_Hovered_Image();
	UFUNCTION() void Set_Unhovered_Image();
};
//------------------------------------------------------------------------------------------------------------
