// Copyright Wayne Potts

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "ArgusAIController_RTS.h"
#include "Argus_STTask_Base.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "ST Task: Base", Category = "Argus AI")
class ARGUS_API UArgus_STTask_Base : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BLueprintReadWrite, EditAnywhere)
	AArgusAIController_RTS* m_aiController;

	EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

	virtual void OnArgusStartTask() {};
};
