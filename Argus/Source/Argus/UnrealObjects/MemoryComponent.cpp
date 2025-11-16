// Copyright Karazaa. This is a part of an RTS project called Argus.



#include "MemoryComponent.h"
#include "Engine/World.h"
#include "ArgusGameInstance.h"
#include "ArgusActor.h"

#include "ArgusController.h"

// Sets default values for this component's properties
UMemoryComponent::UMemoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UMemoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UMemoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UpdateMemory();
	// ...
}

void UMemoryComponent::RemoveExpiredMemories(const float currentTime)
{
	{
		TArray<AArgusActor*> keysToRemove;
		for (auto& [actor, mem] : m_memoryMap)
		{
			if (!UKismetSystemLibrary::IsValid(actor) || mem.IsExpired(currentTime))
			{
					keysToRemove.Add(actor);
			}
		}
		for (const AArgusActor* key : keysToRemove)
		{
			m_memoryMap.Remove(key);
		}
	}
}

void UMemoryComponent::UpdateMemory()
{
	
	UWorld* world = GetWorld();
	if (!world)
	{
		//m_memoryMap.Empty();
		return;
	}
	UArgusGameInstance* argusGameInstance = Cast<UArgusGameInstance>(world->GetGameInstance());
	if (!argusGameInstance)
	{
		//m_memoryMap.Empty();
		return;
	}
	const double time = world->GetTimeSeconds();
	RemoveExpiredMemories(time);
	if (IArgusController* argusController = Cast<IArgusController>(GetOwner()))
	{
		ETeam playerTeam = argusController->GetControlledTeam();
		TArray<uint16> entityIds = argusGameInstance->GetAllRegisteredArgusEntityIds();
		for (const uint16 entityId : entityIds)
		{
			ArgusEntity entity = ArgusEntity::RetrieveEntity(entityId);
			// ignore entities on our team
			
			
			// create a memory if it's not on our team, it can be killed or has extractable resources, and we can see it.

			if (AArgusActor* argusActor = argusGameInstance->GetArgusActorFromArgusEntity(entity))
			{
				if (!argusActor)
				{
					continue;
				}
				if (entity.IsOnTeam(playerTeam))
				{
					AddVisitedLocation(argusActor->GetActorLocation(), time);
					continue;
				}

				if (argusActor->IsSeenBy(playerTeam))
				{
					bool bHasResources = entity.HasExtractableResources();
					bool bIsEnemy = entity.IsOnEnemyTeam(playerTeam) && entity.IsAlive();
					if (bHasResources)
					{
						AddResourcesSeen(argusActor->GetActorLocation(), time);
						AddMemory(argusActor, FLocationMemory(time, argusActor->GetActorLocation(), m_memoryLifetime));
					}
					if (bIsEnemy)
					{
						AddEnemySeen(argusActor->GetActorLocation(), time);
						AddMemory(argusActor, FLocationMemory(time, argusActor->GetActorLocation(), m_memoryLifetime));
					}
				}
			}
		}
		
	}
		
	
}

void UMemoryComponent::AddMemory(AArgusActor* actor, const FLocationMemory& memory)
{
	m_memoryMap.Add(actor, memory);
}

bool UMemoryComponent::HasAnyMemories()
{
	return m_memoryMap.Num() > 0;
}

bool UMemoryComponent::SeenActorOfClass(TSubclassOf<AActor> actorClass, FVector& location)
{
	if (m_memoryMap.Num() > 0)
	{

		for (auto& [actor, mem] : m_memoryMap)
		{
			if (actor->IsA(actorClass))
			{
				location = actor->GetActorLocation();
				return true;
			}
		}
	}
	else
	{
		//UpdateMemory();
	}

	return false;
}

void UMemoryComponent::AddEnemySeen(const FVector location, const double currentTime)
{
	FVector loc = CreateHeatMapKey(location);
	FVector4 loc4 = FVector4(1.0f, 0.0f, currentTime, 0.0f);
	if (m_heatMap.Contains(loc))
	{
		FVector4 mapped = m_heatMap[loc];
		loc4.X += mapped.X;
		loc4.Y += mapped.Y;
		loc4.Z += currentTime;
	}
	m_heatMap.Add(loc, loc4);
}

void UMemoryComponent::AddResourcesSeen(const FVector location, const double currentTime)
{
	FVector loc = CreateHeatMapKey(location);
	FVector4 loc4 = FVector4(0.0f, 1.0f, currentTime, 0.0f);
	if (m_heatMap.Contains(loc))
	{
		FVector4 mapped = m_heatMap[loc];
		loc4.X += mapped.X;
		loc4.Y += mapped.Y;
		loc4.Z += currentTime;
	}
	m_heatMap.Add(loc, loc4);
}

void UMemoryComponent::AddVisitedLocation(const FVector location, const double currentTime)
{
	FVector loc = CreateHeatMapKey(location);
	FVector4 loc4 = FVector4(0.0f, 0.0f, currentTime, 0.0f);
	if (m_heatMap.Contains(loc))
	{
		FVector4 mapped = m_heatMap[loc];
		loc4.X = mapped.X;
		loc4.Y = mapped.Y;
		loc4.Z += currentTime;
	}
	m_heatMap.Add(loc, loc4);
}

FVector UMemoryComponent::GetNearestLocationToSearch(const FVector location, const double range)
{
	UWorld* world = GetWorld();
	if (!world)
	{
		return FVector();
	}
	double time = world->GetTimeSeconds() - 60.0;
	int32 xMax = int32(location.X) / 100 * 100 + range;
	int32 yMax = int32(location.Y) / 100 * 100 + range;
	int32 xMin = xMax - range * 2;
	int32 yMin = yMax - range * 2;
	TSet<FVector> locationsToCheck;
	for (int32 x = xMin; x <= xMax; x += 200)
	{
		for (int32 y = yMin; y <= yMax; y += 200)
		{
			FVector loc = FVector(x, y, 0.0f);
			locationsToCheck.Add(loc);
		}
	}
	locationsToCheck.Remove(CreateHeatMapKey(location));
	FVector foundLocation = *locationsToCheck.FindArbitraryElement();
	for (FVector loc : locationsToCheck.Array())
	{
		if (!m_heatMap.Contains(loc))
		{
			if (FVector::Dist(loc, location) < FVector::Dist(foundLocation, location))
			{
				foundLocation = loc;
			}
		}
		else
		{
			if (FVector::Dist(loc, location) < FVector::Dist(foundLocation, location) && m_heatMap[loc].Z < time)
			{
				foundLocation = loc;
				time = m_heatMap[loc].Z;
			}
		}
	}
	return foundLocation;
}

void UMemoryComponent::RemoveMemory(AArgusActor* actor)
{
	m_memoryMap.Remove(actor);
}

bool UMemoryComponent::GetMemory(AArgusActor* actor, FLocationMemory& memory)
{
	if (m_memoryMap.Contains(actor))
	{
		memory = m_memoryMap[actor];
		return true;
	}
	return false;
}




