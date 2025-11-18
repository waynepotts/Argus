// Copyright Wayne Potts

#include "RandomLocationInRange.h"
#include "Engine/World.h"
#include "NavigationSystem.h"

void URandomLocationInRange::OnArgusStartTask()
{
	bool bSuccess = false;
	TArray<AArgusActor*> actors = m_aiController->GetAllTeamActors();
	UWorld* world = GetWorld();
	if (!world)
	{
		FinishTask(false);
		return;
	}
	UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(world);
	if (!navSystem)
	{
		FinishTask(false);
		return;
	}
	for (AArgusActor* actor : actors)
	{
		if(m_actorClasses.Contains(actor->GetClass()) && actor->IsIdle())
		{
			FVector location = m_aiController->GetNearestLocationToSearch(actor->GetActorLocation(), m_range);
			FNavLocation navLocation;
			if (navSystem->GetRandomReachablePointInRadius(location, m_range, navLocation))
			{
				//actor->SetMoveToLocation(navLocation.Location, true);
				actor->QyeueMoveToLocation(navLocation.Location);
			}
		}
	}
	FinishTask(true);

}
