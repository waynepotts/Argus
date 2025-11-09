// Copyright Wayne Potts


#include "HasMemory.h"
#include "ArgusActor.h"

// Add default functionality here for any IHasMemory functions that are not pure virtual.

void  IHasMemory::RemoveExpiredMemories(const float currentTime)
{

}

void  IHasMemory::UpdateMemory()
{

}

bool IHasMemory::HasAnyMemories()
{
	return false;
}

bool IHasMemory::SeenActorOfClass(TSubclassOf<AActor> actorClass, FVector& location)
{
	return false;
}

void IHasMemory::AddMemory(AArgusActor* actor, const FLocationMemory& memory)
{

}