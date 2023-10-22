// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override; // 重写PossessedBy方法，完成ASC在服务器端的初始化
	virtual void OnRep_PlayerState() override; // 重写OnRep_PlayerState方法，完成ASC在客户端的初始化

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent; // 摄像机组件

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom; // 摄像机摇臂组件

	void InitAbilityActorInfo(); // 初始化技能角色信息方法
	
};
