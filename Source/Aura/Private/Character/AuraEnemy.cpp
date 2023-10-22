// Copyright CREATOR-JIA


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	// 设置Mesh的碰撞响应通道为ECC_Visibility，响应方式为Block阻塞
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true); // 开启能力系统的网络复制
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // 设置能力系统的网络复制模式（对于AI来说，应选用Minimal模式）

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true); // 突出显示Mesh的自定义深度
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); // 设置自定义深度颜色值
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false); // 取消突出显示Mesh的自定义深度
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	/**
	*初始化了Abilities的ActorInfo（参与者信息），该结构保存了有关我们正在对谁采取行动以及谁控制我们的信息。即OwnerActor和AvatarActor
	*OwnerActor是逻辑上拥有此组件的参与者。
	*AvatarActor是pawn。
	*/
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

