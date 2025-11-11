// Copyright Wayne Potts

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "ArgusAIController.h"
#include "ArgusSTConditionBase.generated.h"

/**
 * 
 */
UCLASS()
class ARGUS_API UArgusSTConditionBase : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BLueprintReadWrite, EditAnywhere)
	AArgusAIController* m_aiController;
};
