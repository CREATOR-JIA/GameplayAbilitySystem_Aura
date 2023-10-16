// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();
	
	/** Highlight Interface 突出显示接口函数*/
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	
	
};
