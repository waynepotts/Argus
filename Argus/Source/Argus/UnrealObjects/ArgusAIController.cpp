// Copyright Karazaa. This is a part of an RTS project called Argus.


#include "ArgusAIController.h"

#include "Engine/World.h"
#include "ArgusGameInstance.h"
#include "ArgusEntity.h"
#include "ArgusActor.h"
#include "ArgusLogging.h"
#include "ArgusGameModeBase.h"
#include "Systems/SpawningSystems.h"

AArgusAIController::AArgusAIController()
{
}

void AArgusAIController::UpdateHiddenActors()
{
	for (auto& argusActor : GetAllTeamActors())
	{
		AArgusActor* argusTargetActor = argusActor->GetCurrentTargetActor();
		if (argusTargetActor)
		{
			ArgusEntity argusEntity = argusTargetActor->GetEntity();
			if (const IdentityComponent* identityComponent = argusEntity.GetComponent<IdentityComponent>())
			{
				if (identityComponent->m_team != m_playerTeam)
				{
					if (!identityComponent->IsSeenBy(m_playerTeam))
					{
						argusActor->SetMoveToLocation(argusActor->GetActorLocation(), true);
					}
				}
			}
		}

	}
}

bool AArgusAIController::GetArgusActorsFromArgusEntityIds(const TArray<uint16>& inArgusEntityIds, TArray<AArgusActor*>& outArgusActors)
{
	outArgusActors.SetNumZeroed(inArgusEntityIds.Num());

	const UWorld* world = GetWorld();
	ARGUS_RETURN_ON_NULL_BOOL(world, ArgusUnrealObjectsLog);

	const UArgusGameInstance* gameInstance = world->GetGameInstance<UArgusGameInstance>();
	ARGUS_RETURN_ON_NULL_BOOL(gameInstance, ArgusUnrealObjectsLog);

	for (int i = 0; i < inArgusEntityIds.Num(); ++i)
	{
		outArgusActors[i] = gameInstance->GetArgusActorFromArgusEntity(ArgusEntity::RetrieveEntity(inArgusEntityIds[i]));
	}

	return true;
}

bool AArgusAIController::GetArgusActorsFromArgusEntities(const TArray<ArgusEntity>& inArgusEntities, TArray<AArgusActor*>& outArgusActors)
{
	const UWorld* world = GetWorld();
	ARGUS_RETURN_ON_NULL_BOOL(world, ArgusUnrealObjectsLog);

	const UArgusGameInstance* gameInstance = world->GetGameInstance<UArgusGameInstance>();
	ARGUS_RETURN_ON_NULL_BOOL(gameInstance, ArgusUnrealObjectsLog);
	outArgusActors.SetNumZeroed(inArgusEntities.Num());

	for (int i = 0; i < inArgusEntities.Num(); ++i)
	{
		outArgusActors[i] = gameInstance->GetArgusActorFromArgusEntity(inArgusEntities[i]);
	}

	return true;
}

void  AArgusAIController::FilterArgusActorsToPlayerTeam(TArray<AArgusActor*>& argusActors) const
{
	argusActors = argusActors.FilterByPredicate
	(
		[this](AArgusActor* actorToCheck)
		{
			if (!actorToCheck)
			{
				return false;
			}

			return actorToCheck->GetEntity().IsAlive() && !actorToCheck->GetEntity().IsPassenger() && IsArgusActorOnPlayerTeam(actorToCheck);
		}
	);

}
bool  AArgusAIController::IsArgusActorOnPlayerTeam(const AArgusActor* actor) const
{
	ARGUS_RETURN_ON_NULL_BOOL(actor, ArgusUnrealObjectsLog);

	const IdentityComponent* identityComponent = actor->GetEntity().GetComponent<IdentityComponent>();
	if (!identityComponent)
	{
		return false;
	}

	return identityComponent->m_team == m_playerTeam;
}

bool AArgusAIController::HasRequiredEntities()
{
	UWorld* world = GetWorld();
	if (!world)
	{
		return false;
	}
	UArgusGameInstance* argusGameInstance = Cast<UArgusGameInstance>(world->GetGameInstance());
	if (!argusGameInstance)
	{
		return false;
	}
	TArray<uint16> EntityIds = argusGameInstance->GetAllRegisteredArgusEntityIds();
	TArray<AArgusActor*> argusActors;
	if (GetArgusActorsFromArgusEntityIds(EntityIds, argusActors))
	{
		FilterArgusActorsToPlayerTeam(argusActors);
		TSet<TSubclassOf<AArgusActor>> requiredClasses(m_requiredClasses);

		for (AArgusActor* actor : argusActors)
		{
			if (requiredClasses.IsEmpty())
			{
				return true;
			}
			if (!actor)
			{
				continue;
			}
			for (TSubclassOf<AArgusActor>& requiredClass : requiredClasses.Array())
			{
				if (actor->IsA(requiredClass))
				{
					requiredClasses.Remove(requiredClass);
				}
			}
		}
		return requiredClasses.IsEmpty();
	}
	
	return false;
}

TArray<AArgusActor*> AArgusAIController::GetAllTeamActors()
{
	TArray<AArgusActor*> allActors = GetAllArgusActors();
	FilterArgusActorsToPlayerTeam(allActors);
	return allActors;
}

TArray<AArgusActor*> AArgusAIController::GetAllArgusActors()
{
	const UWorld* world = GetWorld();
	if (!world)
	{
		return TArray<AArgusActor*>();
	}

	const UArgusGameInstance* gameInstance = world->GetGameInstance<UArgusGameInstance>();
	if (!gameInstance)
	{
		return TArray<AArgusActor*>();
	}

	TArray<AArgusActor*> allActors;
	GetArgusActorsFromArgusEntityIds(gameInstance->GetAllRegisteredArgusEntityIds(), allActors);
	return allActors;
}

TArray<AArgusActor*> AArgusAIController::GetArgusActorsWithTeamRelationship(const TSet<ETeamRelationship> relationships)
{
	// just call the parent, this is just to expose to blueprint
	return IArgusController::GetArgusActorsWithTeamRelationship(relationships);
}

AArgusActor* AArgusAIController::GetNearestTeamActorOfClass(const TSubclassOf<AArgusActor> actorClass, const TArray<AArgusActor*> ignoreActors, FVector location)
{
	// just call the parent, this is just to expose to blueprint
	return IArgusController::GetNearestTeamActorOfClass(actorClass, ignoreActors, location);
}

void AArgusAIController::UpdateThreatLevels()
{
}

void AArgusAIController::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* world = GetWorld();
	if (!world)
	{
		return;
	}
	if(AArgusGameModeBase* gameMode = Cast<AArgusGameModeBase>(world->GetAuthGameMode()))
	{
		gameMode->RegisterArgusAIController(m_playerTeam, this);
	}
}


