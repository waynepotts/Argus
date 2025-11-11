// Copyright Wayne Potts

#include "RandomLocationInRange.h"
#include "Engine/World.h"
#include "NavigationSystem.h"

void URandomLocationInRange::OnArgusStartTask()
{
	bool bSuccess = false;
	AArgusActor* actor = nullptr;
	for (TSubclassOf<AArgusActor> actorClass : m_actorClasses)
	{
		AArgusActor* nearest = m_aiController->GetNearestIdleActorOfClass(actorClass);
		if (nearest)
		{
			actor = nearest;
			break;
		}
	}
	if (actor)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FVector location = m_aiController->GetNearestLocationToSearch(actor->GetActorLocation(), m_range);
			UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(world);
			if (navSystem)
			{
				FNavLocation navLocation;
				if (navSystem->GetRandomReachablePointInRadius(location, m_range, navLocation))
				{
					actor->SetMoveToLocation(navLocation.Location, true);
					bSuccess = true;
				}
			}
		}
	}
	FinishTask(bSuccess);

}
