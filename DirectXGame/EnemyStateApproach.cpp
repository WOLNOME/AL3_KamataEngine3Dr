#include "EnemyStateApproach.h"
#include "Function.h"

void EnemyStateApproach::Update(Enemy* pEnemy) { 
	// 移動
	pEnemy->SetTranslation(Add(pEnemy->GetTranslation(), velocity_));
	// 既定の位置に達したら離脱
	if (pEnemy->GetTranslation().z < 0.0f) {
		pEnemy->ChangeState(new EnemyStateLeave());
	}
}
