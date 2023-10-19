// Copyright CREATOR-JIA


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
// #include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); // 设置能力系统的网络复制模式（多人游戏时，应选用Mixed模式）

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	// 当服务器上游戏状态发生变化时，那么服务器将向所有客户端发送更新，它们将更新任何应该复制的变量，更新频率为1毫秒。以便客户端能与服务端保持同步；
	NetUpdateFrequency = 100.f; // 游戏状态的网络更新频率为1毫秒（服务器更新客户端的频率）
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
