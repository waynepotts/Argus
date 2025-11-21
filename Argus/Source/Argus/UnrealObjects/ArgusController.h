// Copyright Karazaa. This is a part of an RTS project called Argus.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ArgusEntity.h"
#include "ComponentDefinitions/IdentityComponent.h"
#include "ArgusActor.h"
#include "ArgusController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UArgusController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARGUS_API IArgusController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ETeam GetControlledTeam();

	virtual bool HasRequiredEntities();

	virtual TArray<TSubclassOf<AArgusActor>> GetRequredEntityClasses();	

	virtual bool GetArgusActorsFromArgusEntityIds(const TArray<uint16>& inArgusEntityIds, TArray<AArgusActor*>& outArgusActors) = 0;
	virtual bool GetArgusActorsFromArgusEntities(const TArray<ArgusEntity>& inArgusEntities, TArray<AArgusActor*>& outArgusActors) = 0;

	virtual TArray<AArgusActor*> GetAllTeamActors();

	virtual TArray<AArgusActor*> GetAllArgusActors();

	virtual TArray<AArgusActor*> GetArgusActorsWithTeamRelationship(const TSet<ETeamRelationship> relationships);

	virtual AArgusActor* GetNearestTeamActorOfClass(const TSubclassOf<AArgusActor> actorClass, const TArray<AArgusActor*> ignoreActors, FVector location = FVector::ZeroVector);

	/**
	* Returns the threat level of a team, enemy teams will be minimum of 0.1, friendly or inactive teams will be 0.0f.
	* threat levels for enemy teams are a minimum of 0.1 (low threat), 1.0 (equal threat), or over 1.0 (high threat)
	*/
	virtual float GetTeamThreatLevel(ETeam team);

	/** 
	* Returns the mean threat level of all enemy teams
	*/
	virtual float GetThreatLevel();

	/**
	* As the threat levels probably won't change very quickly, this function can be called to update the threat levels
	*/
	virtual void UpdateThreatLevels();
};
