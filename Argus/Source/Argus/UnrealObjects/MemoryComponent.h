// Copyright Karazaa. This is a part of an RTS project called Argus.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"

#include "LocationMemory.h"
#include "ArgusGameInstance.h"
#include "HasMemory.h"

#include "MemoryComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARGUS_API UMemoryComponent : public UActorComponent, public IHasMemory
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMemoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<AArgusActor*, FLocationMemory> m_memoryMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FVector, FVector4> m_heatMap;

	UFUNCTION(BlueprintCallable)
	void RemoveExpiredMemories(const float currentTime) override;

	UFUNCTION(BlueprintCallable)
	void UpdateMemory() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double m_memoryLifetime = 30.0f;

	void AddMemory(AArgusActor* actor, const FLocationMemory& memory) override;

	bool HasAnyMemories() override;

	bool SeenActorOfClass(TSubclassOf<AActor> actorClass, FVector& location) override;

	void AddEnemySeen(const FVector location, const double currentTime) override;

	void AddResourcesSeen(const FVector location, const double currentTime) override;
	void AddVisitedLocation(const FVector location, const double currentTime) override;

	UFUNCTION(BlueprintCallable)
	FVector GetNearestLocationToSearch(FVector location, const double range);

	FVector CreateHeatMapKey(const FVector location) { return FVector((int32(location.X) / 100) * 100, (int32(location.Y) / 100) * 100, 0.0f); };

		
};
