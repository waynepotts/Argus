// Copyright Karazaa. This is a part of an RTS project called Argus.

#pragma once

#include "ArgusUIElement.h"
#include "Slate/SlateBrushAsset.h"
#include "MarqueeCanvas.generated.h"

class ArgusEntity;
class UArgusInputManager;
class UCanvasPanel;

UCLASS()
class UMarqueeCanvas : public UArgusUIElement
{
	GENERATED_BODY()

public:
	virtual void UpdateDisplay(const UpdateDisplayParameters& updateDisplayParams) override;

protected:
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