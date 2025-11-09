// Copyright Wayne Potts

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"

#include "ArgusActor.h"
#include "LocationMemory.h"

#include "HasMemory.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasMemory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARGUS_API IHasMemory
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void RemoveExpiredMemories(const float currentTime);

	virtual void UpdateMemory();

	virtual bool HasAnyMemories();

	virtual bool SeenActorOfClass(TSubclassOf<AActor> actorClass, FVector& location);

	virtual void AddMemory(AArgusActor* actor, const FLocationMemory& memory);

};
