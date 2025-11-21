// Copyright Wayne Potts

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ArgusAIController.h"
#include "ArgusController.h"
#include "HasMemory.h"
#include "ArgusAIController_RTS.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ARGUS_API AArgusAIController_RTS : public AArgusAIController, public IHasMemory
{
	GENERATED_BODY()
	
public:
	AArgusAIController_RTS();
	
	UFUNCTION(BlueprintCallable, Category = "ArgusAIControllerRTS")
	void UpdateMemory() override;

	UFUNCTION(BlueprintCallable, Category = "ArgusAIControllerRTS")
	void RemoveExpiredMemories(const float currentTime) override;

	FVector GetNearestLocationToSearch(const FVector location, const double range) override;

	UFUNCTION(BlueprintCallable, Category = "ArgusAIControllerRTS")
	bool HasAnyMemories() override;

	UFUNCTION(BlueprintCallable, Category = "ArgusAIControllerRTS")
	bool SeenActorOfClass(TSubclassOf<AActor> actorClass, FVector& location) override;

	UFUNCTION(BlueprintCallable, Category = "ArgusAIControllerRTS")
	void AddMemory(AArgusActor* actor, const FLocationMemory& memory) override;

	void AddEnemySeen(const FVector location, const double currentTime) override;

	void AddResourcesSeen(const FVector location, const double currentTime) override;
	void AddVisitedLocation(const FVector location, const double currentTime) override;

	UFUNCTION(BlueprintCallable, Category = "ArgusAIControllerRTS")
	void RemoveMemory(AArgusActor* actor) override;

	UFUNCTION(BlueprintCallable, Category = "ArgusAIControllerRTS")
	bool GetMemory(AArgusActor* actor, FLocationMemory& memory) override;

	void UpdateThreatLevels() override;

protected:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArgusAIControllerRTS")
	//TArray<TSubclassOf<AArgusActor>> m_requiredClasses;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArgusAIControllerRTS")
	TObjectPtr<UMemoryComponent> m_memoryComponent;
};
