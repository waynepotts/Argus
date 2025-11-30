// Copyright Karazaa. This is a part of an RTS project called Argus.

#pragma once

#include "ArgusUIElement.h"
#include "Slate/SlateBrushAsset.h"
#include "MarqueeCanvas.generated.h"

class ArgusEntity;
class UArgusInputManager;
class UCanvasPanel;

UENUM(BlueprintType)
enum class EModifierType : uint8
{
	NoModifier = 0
	, Shift = 1
	, Control = 2
	, Alt = 3
	, Super = 4
	, Meta = 5

};
ENUM_CLASS_FLAGS(EModifierType);

UCLASS()
class UMarqueeCanvas : public UArgusUIElement
{
	GENERATED_BODY()

public:
	UMarqueeCanvas();
	virtual void UpdateDisplay(const UpdateDisplayParameters& updateDisplayParams) override;
	UFUNCTION(BlueprintCallable, Category = "Marquee Canvas")
	void AddModifierKey(EModifierType modifierKey) { m_modifierKeysNum |= (static_cast<uint8>(modifierKey)); }
	void RemoveModifierKey(EModifierType modifierKey) { m_modifierKeysNum &= ~(static_cast<uint8>(modifierKey)); }
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Marquee Canvas")
	TMap<EModifierType, FLinearColor> m_modifierKeys;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Marquee Canvas")
	uint8 m_modifierKeysNum = 0u;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor m_marqueeBoxColor = FColor::Green;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor m_marqueeBoxFillColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.2f);

	UPROPERTY(EditDefaultsOnly)
	float m_marqueeBoxThickness = 1.0f;
	
	UPROPERTY(Transient)
	TObjectPtr<USlateBrushAsset> m_marqueeBoxBrushAsset = nullptr;
	virtual void NativeOnInitialized() override;
	virtual int32 NativePaint(const FPaintArgs& args, const FGeometry& allottedGeometry, const FSlateRect& myCullingRect, FSlateWindowElementList& outDrawElements, int32 layerId, const FWidgetStyle& inWidgetStyle, bool parentEnabled) const override;

	TArray<FVector2D> m_marqueeBoxPoints;
};