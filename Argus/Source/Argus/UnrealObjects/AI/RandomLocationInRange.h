// Copyright Wayne Potts

#pragma once

#include "CoreMinimal.h"
#include "Argus_STTask_Base.h"
#include "RandomLocationInRange.generated.h"

/**
 * 
 */
UCLASS()
class ARGUS_API URandomLocationInRange : public UArgus_STTask_Base
{
	GENERATED_BODY()
	
public:
	void OnArgusStartTask();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_range = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AArgusActor>> m_actorClasses;
};
