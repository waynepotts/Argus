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

	virtual void AddEnemySeen(const FVector location, const double currentTime);

	virtual void AddResourcesSeen(const FVector location, const double currentTime);
	virtual void AddVisitedLocation(const FVector location, const double currentTime);

	virtual FVector GetNearestLocationToSearch(FVector location, const double range);

	virtual FVector CreateHeatMapKey(const FVector location) { return FVector((int32(location.X) / 100) * 100, (int32(location.Y) / 100) * 100, 0.0f); };

	virtual void RemoveMemory(AArgusActor* actor);

	virtual bool GetMemory(AArgusActor* actor, FLocationMemory& memory);

};
