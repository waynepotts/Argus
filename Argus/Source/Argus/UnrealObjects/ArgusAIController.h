// Copyright Karazaa. This is a part of an RTS project called Argus.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ArgusController.h"
#include "ComponentDefinitions/IdentityComponent.h"
#include "MemoryComponent.h"
#include "HasMemory.h"
#include "ArgusAIController.generated.h"

class AArgusActor;
class ArgusEntity;

/**
 * 
 */
UCLASS(BlueprintType)
class ARGUS_API AArgusAIController : public AAIController, public IArgusController, public IHasMemory
{
	GENERATED_BODY()
	
public:
	AArgusAIController();
	/**
	* Updates which actors this controller can see based on team affiliation and fog of war.
	*/
	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	void UpdateHiddenActors();
	bool GetArgusActorsFromArgusEntityIds(const TArray<uint16>& inArgusEntityIds, TArray<AArgusActor*>& outArgusActors) override;
	bool GetArgusActorsFromArgusEntities(const TArray<ArgusEntity>& inArgusEntities, TArray<AArgusActor*>& outArgusActors) override;
	ETeam GetPlayerTeam() const { return m_playerTeam; }

	ETeam GetControlledTeam() override { return m_playerTeam; }

	void FilterArgusActorsToPlayerTeam(TArray<AArgusActor*>& argusActors) const;
	bool IsArgusActorOnPlayerTeam(const AArgusActor* actor) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Argus AIController")
	TArray<TSubclassOf<AArgusActor>> GetRequredEntityClasses() override { return m_requiredClasses; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Argus AIController")
	bool HasRequiredEntities() override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	TArray<AArgusActor*> GetAllTeamActors() override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	TArray<AArgusActor*> GetAllArgusActors() override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	TArray<AArgusActor*> GetArgusActorsWithTeamRelationship(const TSet<ETeamRelationship> relationships) override;

	/**
	* Returns the nearest idle actor of the specified class this controller can give commands to.
	* 
	* The idea behind this function is so that we've got a quick way for the AI to get an available unit to give instructions to.
	* 
	* return null if there is no available actor of the specified class.
	* 
	* @param actorClass The class of the actor to find.
	* @param location The location to search from.
	*/
	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	AArgusActor* GetNearestTeamActorOfClass(TSubclassOf<AArgusActor> actorClass, FVector location = FVector::ZeroVector) override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	void UpdateMemory() override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	void RemoveExpiredMemories(const float currentTime) override;

	FVector GetNearestLocationToSearch(const FVector location, const double range) override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	bool HasAnyMemories() override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	bool SeenActorOfClass(TSubclassOf<AActor> actorClass, FVector& location) override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	void AddMemory(AArgusActor* actor, const FLocationMemory& memory) override;

	void AddEnemySeen(const FVector location, const double currentTime) override;

	void AddResourcesSeen(const FVector location, const double currentTime) override;
	void AddVisitedLocation(const FVector location, const double currentTime) override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	void RemoveMemory(AArgusActor* actor) override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	bool GetMemory(AArgusActor* actor, FLocationMemory& memory) override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Argus AIController")
	ETeam m_playerTeam = ETeam::TeamA;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Argus AIController")
	TArray<TSubclassOf<AArgusActor>> m_requiredClasses;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Argus AIController")
	UMemoryComponent* m_memoryComponent;
};
