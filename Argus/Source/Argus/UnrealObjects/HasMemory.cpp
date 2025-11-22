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

void IHasMemory::AddEnemySeen(const FVector location, const double currentTime) {}

void IHasMemory::AddResourcesSeen(const FVector location, const double currentTime) {}
void IHasMemory::AddVisitedLocation(const FVector location, const double currentTime) {}

FVector IHasMemory::GetNearestLocationToSearch(FVector location, const double range) { return FVector(); }

void IHasMemory::RemoveMemory(AArgusActor* actor)
{
}

bool IHasMemory::GetMemory(AArgusActor* actor, FLocationMemory& memory)
{
	return false;
}

TArray<FVector> IHasMemory::GetNearestSafeLocations(const FVector location, const double thratLevel, const float range)
{
	return TArray<FVector>();
}

