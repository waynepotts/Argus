// Copyright Karazaa. This is a part of an RTS project called Argus.


#include "ArgusController.h"
#include "Engine/World.h"

#include "ArgusLogging.h"
#include "ArgusActor.h"
#include "ArgusGameInstance.h"

// Add default functionality here for any IArgusController functions that are not pure virtual.

ETeam IArgusController::GetControlledTeam()
{
	return ETeam::None;
}

bool IArgusController::HasRequiredEntities()
{
	return false;
}

TArray<TSubclassOf<AArgusActor>> IArgusController::GetRequredEntityClasses()
{
	return TArray<TSubclassOf<AArgusActor>>();
}

TArray<AArgusActor*> IArgusController::GetAllTeamActors()
{
	return TArray<AArgusActor*>();
}

TArray<AArgusActor*> IArgusController::GetAllArgusActors()
{
	return TArray<AArgusActor*>();
}

TArray<AArgusActor*> IArgusController::GetArgusActorsWithTeamRelationship(const TSet<ETeamRelationship> relationships)
{
	TArray<AArgusActor*> allActors = GetAllTeamActors();
	const ETeam team = GetControlledTeam();
	return allActors.FilterByPredicate([relationships, team](AArgusActor* actor) { return relationships.Contains(actor->GetEntity().GetTeamRelationship(team)); });
}

AArgusActor* IArgusController::GetNearestTeamActorOfClass(const TSubclassOf<AArgusActor> actorClass, const TArray<AArgusActor*> ignoreActors, FVector location)
{
	TArray<AArgusActor*> allActors = GetAllTeamActors();
	AArgusActor* nearestActor = nullptr;
	double distance = 999999999.0f;
	for (AArgusActor* actor : allActors)
	{
		if (ignoreActors.Contains(actor))
		{
			continue;
		}
		if (actor->IsA(actorClass))
		{
			if (nearestActor)
			{
				double otherDistance = FVector::Dist(nearestActor->GetActorLocation(), location);
				if (distance > otherDistance)
				{
					nearestActor = actor;
					distance = otherDistance;
				}
			}
			else
			{
				nearestActor = actor;
				distance = FVector::Dist(nearestActor->GetActorLocation(), location);
			}
		}
	}
	return nearestActor;
}

float IArgusController::GetTeamThreatLevel(ETeam team)
{
	return 1.0f;
}
