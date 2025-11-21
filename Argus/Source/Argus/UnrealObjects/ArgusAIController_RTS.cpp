// Copyright Wayne Potts


#include "ArgusAIController_RTS.h"

AArgusAIController_RTS::AArgusAIController_RTS()
{
	TObjectPtr<UMemoryComponent> memory = CreateDefaultSubobject<UMemoryComponent>(TEXT("MemoryComponent"));
	m_memoryComponent = memory;

}

void AArgusAIController_RTS::UpdateMemory()
{
	m_memoryComponent->UpdateMemory();
}

void AArgusAIController_RTS::RemoveExpiredMemories(const float currentTime)
{
	m_memoryComponent->RemoveExpiredMemories(currentTime);
}

FVector AArgusAIController_RTS::GetNearestLocationToSearch(const FVector location, const double range)
{
	return m_memoryComponent->GetNearestLocationToSearch(location, range);
}

bool AArgusAIController_RTS::HasAnyMemories()
{
	return m_memoryComponent->HasAnyMemories();
}

bool AArgusAIController_RTS::SeenActorOfClass(TSubclassOf<AActor> actorClass, FVector& location)
{
	return m_memoryComponent->SeenActorOfClass(actorClass, location);
}

void AArgusAIController_RTS::AddMemory(AArgusActor* actor, const FLocationMemory& memory)
{
	m_memoryComponent->AddMemory(actor, memory);
}

void AArgusAIController_RTS::AddEnemySeen(const FVector location, const double currentTime)
{
	m_memoryComponent->AddEnemySeen(location, currentTime);
}

void AArgusAIController_RTS::AddResourcesSeen(const FVector location, const double currentTime)
{
	m_memoryComponent->AddResourcesSeen(location, currentTime);
}

void AArgusAIController_RTS::AddVisitedLocation(const FVector location, const double currentTime)
{
	m_memoryComponent->AddVisitedLocation(location, currentTime);
}

void AArgusAIController_RTS::RemoveMemory(AArgusActor* actor)
{
	m_memoryComponent->RemoveMemory(actor);
}

bool AArgusAIController_RTS::GetMemory(AArgusActor* actor, FLocationMemory& memory)
{
	return m_memoryComponent->GetMemory(actor, memory);
}

void AArgusAIController_RTS::UpdateThreatLevels()
{
	TMap<ETeam, float> threatLevels;
	UArgusGameInstance* gameInstance = Cast<UArgusGameInstance>(GetGameInstance<UArgusGameInstance>());

	TArray<AArgusActor*> allActors = GetAllArgusActors();
	for (AArgusActor* actor : allActors)
	{
		if (const IdentityComponent* identityComponent = actor->GetEntity().GetComponent<IdentityComponent>())
		{
			if (identityComponent->IsEnemyTeam(m_playerTeam))
			{
				float threatLevel = threatLevels.Contains(identityComponent->m_team) ? threatLevels[identityComponent->m_team] + 1.0f : 1.0f;
				threatLevels.Add(identityComponent->m_team, threatLevel);
			}
			else if(identityComponent->m_team == m_playerTeam)
			{
				float threatLevel = threatLevels.Contains(m_playerTeam) ? threatLevels[m_playerTeam] + 1.0f : 1.0f;
				threatLevel = identityComponent->IsSeenBy(m_playerTeam) ? threatLevel + 1.0f : threatLevel;
				threatLevels.Add(identityComponent->m_team, threatLevel);
			}
		}
	}
	const float myThreat = threatLevels.Contains(m_playerTeam) ? threatLevels[m_playerTeam] : 1.0f;
	threatLevels.Remove(m_playerTeam);
	m_teamThreatLevels.Empty(threatLevels.Num());
	for (auto& entry : threatLevels)
	{
		m_teamThreatLevels.Add(entry.Key, FMath::Max(0.1f, entry.Value / myThreat));
	}
}
