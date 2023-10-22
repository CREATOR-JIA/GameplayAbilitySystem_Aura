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
	
	/** Enemy Interface : 两个接口函数*/
	virtual void HighLightActor() override; // 突出显示
	virtual void UnHighLightActor() override; // 禁用突出显示
	/** End Enemy Interface */

protected:
	
	virtual void BeginPlay() override; // 重写BeginPlay()方法，在该方法中，我们初始化技能ActorInfo
};
