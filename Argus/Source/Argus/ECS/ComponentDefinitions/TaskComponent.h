// Copyright Karazaa. This is a part of an RTS project called Argus.

#pragma once

#include "ArgusMacros.h"
#include "ComponentDependencies/TaskComponentStates.h"
#include "ComponentObservers/TaskComponentObservers.h"

#include "ComponentDependencies/ArgusDeque.h"
#include "CoreMinimal.h"

struct QueuedTask
{
	FVector m_targetLocation = FVector::ZeroVector;
	uint16 m_targetEntityId = 0u;
	EMovementState m_movementState = EMovementState::None;
	EAbilityState m_abilityState = EAbilityState::None;
	EConstructionState m_constructionState = EConstructionState::None;
	ECombatState m_combatState = ECombatState::None;
	EResourceExtractionState m_resourceExtractionState = EResourceExtractionState::None;
	
	QueuedTask(uint16 targetEntityId) : m_targetEntityId(targetEntityId) 
	{
		m_movementState = EMovementState::ProcessMoveToEntityCommand;
	}

	QueuedTask(FVector targetLocation) : m_targetLocation(targetLocation) 
	{
		m_movementState = EMovementState::ProcessMoveToLocationCommand;
	}

	QueuedTask(EAbilityState abilityState) : m_abilityState(abilityState)
	{
	}
};

struct TaskComponent
{
	ARGUS_COMPONENT_SHARED;

	ARGUS_IGNORE()
	uint32 m_spawnedFromArgusActorRecordId = 0u;

	ARGUS_OBSERVABLE_DECLARATION(EBaseState, m_baseState, EBaseState::Alive)

	ARGUS_IGNORE()
	EMovementState m_movementState = EMovementState::None;

	ARGUS_IGNORE()
	ESpawningState m_spawningState = ESpawningState::None;

	ARGUS_IGNORE()
	EAbilityState m_abilityState = EAbilityState::None;

	ARGUS_IGNORE()
	EConstructionState m_constructionState = EConstructionState::None;

	ARGUS_IGNORE()
	ECombatState m_combatState = ECombatState::None;

	ARGUS_IGNORE()
	EResourceExtractionState m_resourceExtractionState = EResourceExtractionState::None;

	ARGUS_IGNORE()
	ArgusDeque<QueuedTask, ArgusContainerAllocator<10> > m_queuedCommands;

	ARGUS_OBSERVABLE_PROPERTY_DECLARATION(EFlightState, m_flightState, EFlightState::Grounded)

	bool IsExecutingMoveTask() const
	{
		return m_movementState == EMovementState::MoveToLocation || m_movementState == EMovementState::MoveToEntity;
	}

	void StartQueuedTask(QueuedTask queuedTask)
	{
		m_movementState = queuedTask.m_movementState;
		m_abilityState = queuedTask.m_abilityState;
		m_constructionState = queuedTask.m_constructionState;
		m_combatState = queuedTask.m_combatState;
		m_resourceExtractionState = queuedTask.m_resourceExtractionState;
	}

	void SetToKillState()
	{
		Set_m_baseState(EBaseState::Dead);
		m_movementState = EMovementState::None;
		m_spawningState = ESpawningState::None;
		m_abilityState = EAbilityState::None;
		m_constructionState = EConstructionState::None;
		m_combatState = ECombatState::None;
		m_resourceExtractionState = EResourceExtractionState::None;
		Set_m_flightState(EFlightState::Grounded);
		m_queuedCommands.Reset();
	}

	
};