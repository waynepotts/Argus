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
class ARGUS_API AArgusAIController : public AAIController, public IArgusController
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

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	AArgusActor* GetNearestTeamActorOfClass(const TSubclassOf<AArgusActor> actorClass, const TArray<AArgusActor*> ignoreActors, FVector location = FVector::ZeroVector);
	

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Argus AIController")
	ETeam m_playerTeam = ETeam::TeamH;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Argus AIController")
	TArray<TSubclassOf<AArgusActor>> m_requiredClasses;

};
