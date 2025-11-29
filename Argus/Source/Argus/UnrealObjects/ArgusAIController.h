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
	
	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	virtual void UpdateThreatLevels() override;

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	float GetTeamThreatLevel(ETeam team) override { return m_teamThreatLevels.Contains(team) ? m_teamThreatLevels[team] : 0.0f; }

	UFUNCTION(BlueprintCallable, Category = "Argus AIController")
	float GetThreatLevel() override 
	{ 
		float threatLevel = 0.0f;
		for (auto teamThreatLevel : m_teamThreatLevels)
		{
			threatLevel += teamThreatLevel.Value;
		}
		return threatLevel / m_teamThreatLevels.Num();
	}
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Argus AIController")
	ETeam m_playerTeam = ETeam::TeamH;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Argus AIController")
	TArray<TSubclassOf<AArgusActor>> m_requiredClasses;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Argus AIController")
	TMap<ETeam, float> m_teamThreatLevels;

	virtual void BeginPlay() override;
};
