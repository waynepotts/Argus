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
