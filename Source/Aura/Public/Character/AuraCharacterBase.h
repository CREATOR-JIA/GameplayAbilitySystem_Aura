// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract) // 将类声明为抽象基类，这样会阻止用户在虚幻编辑器中向这个世界中添加这个类的Actor
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent>Weapon; // TObjectPtr对象指针类型，提供编辑器下动态解析和访问追踪功能。

};