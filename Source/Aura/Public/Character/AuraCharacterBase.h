// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract) // 将类声明为抽象基类，这样会阻止用户在虚幻编辑器中向这个世界中添加这个类的Actor
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	// 获取两个指针，一个是能力系统组件，一个是属性集
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // 因继承了IAbilitySystemInterface，因此需要重写GetAbilitySystemComponent这个函数
	UAttributeSet* GetAttributeSet () const {return AttributeSet;}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent>Weapon; // TObjectPtr对象指针类型，提供编辑器下动态解析和访问追踪功能。

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent; // 行为系统组件
	
	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet; // 属性集

};