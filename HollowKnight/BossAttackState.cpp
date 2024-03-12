#include "BossAttackState.h"
#include "BossBrain.h"
#include "Player.h"

BossAttackState::BossAttackState(Brain* _brain) : AttackState(_brain)
{
	attackToChase = new AttackToChase(_brain->GetBlackBoard());
	transitions.push_back(attackToChase);
}

void BossAttackState::Init()
{
	attackToChase->Init(dynamic_cast<BossBrain*>(brain)->GetChaseState());
}

void BossAttackState::Start()
{
	AttackState::Start();

	movement->SetCanMove(false);

	animation->RunAnimation("Attack", animation->GetCurrentAnimation()->GetDirectionX());

	new Timer([&]()
		{
			if (inspect->GetHitInfo().actor)
			{
				Player* _player = dynamic_cast<Player*>(inspect->GetHitInfo().actor);
				_player->GetStats()->UpdateLife(-1);
			}
		}, seconds(1.2f), true, false);


}
