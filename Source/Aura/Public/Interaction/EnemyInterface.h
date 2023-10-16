// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 定义两个接口函数
	virtual void HighLightActor() = 0; // 突出显示，用于鼠标移动到敌人角色身上之后，高亮显示
	virtual void UnHighLightActor() = 0; // 取消突出显示
};
