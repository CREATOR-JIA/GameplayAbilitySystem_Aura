// Copyright CREATOR-JIA


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	// 设置Mesh的碰撞响应通道为ECC_Visibility，响应方式为Block阻塞
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
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

