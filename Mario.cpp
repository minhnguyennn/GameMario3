#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "MushRoom.h"
#include "Leaf.h"
#include "QuestionBrick.h"
#include "Point.h"
#include "Koopa.h"
#include "FireBalls.h"
#include "Platform.h"
#include "Collision.h"
#include "PlayScene.h"
#include "FireBallOfMario.h"
#include "Goomba.h"
#include "Tail.h"
#include "VenusFireTrap.h"
#include "FlowerBox.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{	
	/*DebugOutTitle(L"isAttack: %d and isfly: %d", isAttack, isFlying);*/
	DebugOutTitle(L"isIncreasePower: %d and time_power: %d", isDecreasePower, time_power);
	
	DebugOut(L"--STATE-- %d\n", state);
	ChangeLevelMario(dt);
	AccelerationFunction();
	CalculatePowerToFly();
	CalculateHeartAndCoin();
	CountDown1Second();
	
	if (canReturnWorldMap) {
		//sau 2s
		//doi canh world map
	}
	if (disableKey && isOnPlatform) {
		if (MarioOutWorld())
		{
			SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else
		{
			vx = 0;
			vy = 0;
			ax = 0;
			ay = 0;
		}
	}
	

	if (isAttack && CountDownTimer(MARIO_ATTACK_TIMEOUT))
	{
		isAttack = false;
	}

	if (isSlowFly && CountDownTimer(MARIO_FALL_SLOWLY_TIMEOUT))
	{
		isSlowFly = false;
	}

	if (isKick && CountDownTimer(MARIO_KICK_TIMEOUT))
	{
		isKick = false;
	}
	
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
		if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (isHolding) MarioHoldKoopaFunction();
}

//ONCOLLISION
void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking()) 
	{
		vy = 0;
		
		if (e->ny < 0) 
		{ 
			isOnPlatform = true; 
			isGhostBox = false;
		}
		else
		{
			if (!isDecreasePower) time_power = GetTickCount64();
			isDecreasePower = true;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking()) 
	{
		vx = 0;
		if(!isDecreasePower) time_power = GetTickCount64();
		isDecreasePower = true;
	}


	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMushRoom*>(e->obj))
		OnCollisionWithMushRoom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CFireBalls*>(e->obj))
		OnCollisionWithFireBalls(e);
	else if (dynamic_cast<CVenusFireTrap*>(e->obj))
		OnCollisionWithVenusFireTrap(e);
	else if (dynamic_cast<CFlowerBox*>(e->obj))
		OnCollisionWithFlowerBox(e);
}

void CMario::OnCollisionWithFlowerBox(LPCOLLISIONEVENT e)
{
	CFlowerBox* flower_box = dynamic_cast<CFlowerBox*>(e->obj);

		disableKey = true;
		SetState(MARIO_STATE_IDLE);
		flower_box->SetState(FLOWER_BOX_STATE_UP);
	
}

void CMario::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e) 
{
	this->LowerLevel();
}

void CMario::OnCollisionWithFireBalls(LPCOLLISIONEVENT e) 
{
	this->LowerLevel();
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e) 
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (e->ny < 0) 
	{
		goomba->LowerLevel();
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else 
	{
		LowerLevel();
	}
}

void CMario::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	float plant_form_y = platform->GetY();
	if (!platform->IsBlocking()) 
	{
		if (e->ny < 0) 
		{
			vy = 0;
			isOnPlatform = true;
			isGhostBox = true;
			if (level != MARIO_LEVEL_SMALL) 
			{
				if (!isSitting) 
				{
					y = (plant_form_y - MARIO_DISTANCE_WITH_GHOST_BOX);
				}
				else 
				{
					y = (plant_form_y - (MARIO_DISTANCE_WITH_GHOST_BOX - 4));
				}
			}
			else 
			{
				y = (plant_form_y - (MARIO_DISTANCE_WITH_GHOST_BOX - 6));
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (e->ny < 0)
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		//koopa->SetVY(-KOOPA_JUMP_DEFLECT_SPEED);
		if (koopa->GetLevel() == KOOPA_LEVEL_BIG)
		{
			koopa->SetLevel(KOOPA_LEVEL_SMALL);
		}
		else 
		{
			if (koopa->GetIsAttacking() || koopa->GetState() == KOOPA_STATE_WALKING) 
			{
				koopa->SetY(koopa->GetY() - KOOPA_DISTANCE_WHEN_ATTACKING);
				koopa->SetState(KOOPA_STATE_CLOSE_SHELL);
			}
			else if (koopa->GetIsDefense() || koopa->GetIsWaiting())
			{
				koopa->SetState(KOOPA_STATE_ATTACKING);
			}
		}
	}
	else if (e->nx != 0) 
	{
		if (koopa->GetLevel() == KOOPA_LEVEL_SMALL) 
		{
			if ((koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetIsAttacking()) && (!isHolding)) 
			{
				LowerLevel();
			}
			else if (isRunning && !isHolding)
			{
				koopa_holding = koopa;
				SetState(MARIO_STATE_HOLDING);
			}
			else if (koopa->GetIsDefense() || koopa->GetIsWaiting() || koopa->GetIsTurnOver()) 
			{
				SetState(MARIO_STATE_KICK);
				koopa->SetState(KOOPA_STATE_ATTACKING);
			}
		}
		else 
		{
			LowerLevel();
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	//CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
	
}

void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	CMushRoom* p = (CMushRoom*)e->obj;
	p->Delete();
	if (level == MARIO_LEVEL_SMALL) 
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	else 
	{
		coin++;
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = (CLeaf*)e->obj;
	leaf->Delete();
	if (level == MARIO_LEVEL_SMALL) 
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	else if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_FIRE)
	{
		SetLevel(MARIO_LEVEL_RACCOON);
	}
	else 
	{
		coin++;
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* quest_brick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (quest_brick->GetState() == QUESTION_STATE_IDLE && e->ny > 0)
	{
		quest_brick->SetState(QUESTION_STATE_MOVE_UP);
		
	}
}

//GET ANIMATION
void CMario::Render()
{
	
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (isChangeLevel)
	{
		aniId = GetAniIdChangeLevel();
	}
	else if (state == MARIO_STATE_DIE)
	{
		aniId = ID_ANI_MARIO_DIE;
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		aniId = GetAniIdBig();
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		aniId = GetAniIdSmall();
	}
	else if (level == MARIO_LEVEL_FIRE)
	{
		aniId = GetAniIdFire();
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		aniId = GetAniIdRaccoon();
	}

	if (level != MARIO_LEVEL_RACCOON)
	{
		if (isGhostBox)
		{
			animations->Get(aniId)->Render(x, y - 1);
		}
		else
		{
			animations->Get(aniId)->Render(x, y);
		}
	}
	else
	{
		if (nx > 0)
		{
			if (isGhostBox)
			{
				animations->Get(aniId)->Render(x - 4, y - 1);
			}
			else
			{
				animations->Get(aniId)->Render(x - 4, y);
			}
		}
		else
		{
			if (isGhostBox)
			{
				animations->Get(aniId)->Render(x + 4, y - 1);
			}
			else
			{
				animations->Get(aniId)->Render(x + 4, y);
			}
		}
	}

	RenderBoundingBox();
}

int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx == 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT;
			else  aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT;
		}
	}
	else if (isKick)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
		else  aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
	}
	else if (isDeceleration)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
		else  aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (IsMaxPower())
		{
			if (nx >= 0) aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else
			{
				if (ax > 0) aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
	return aniId;
}

int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx == 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_IDLE_HOLD_RIGHT;
			else  aniId = ID_ANI_MARIO_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
		}
	}
	else if (isKick)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_KICK_RIGHT;
		else  aniId = ID_ANI_MARIO_KICK_LEFT;
	}
	else if (isDeceleration)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_WALKING_RIGHT;
		else  aniId = ID_ANI_MARIO_WALKING_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (vy < 0)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0) aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx > 0) aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FALL_RIGHT;
			else  aniId = ID_ANI_MARIO_FALL_LEFT;
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else
			{
				if (ax > 0) aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdFire()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx == 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FIRE_IDLE_HOLD_RIGHT;
			else  aniId = ID_ANI_MARIO_FIRE_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_LEFT;
		}
	}
	else if (isKick)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_FIRE_KICK_RIGHT;
		else  aniId = ID_ANI_MARIO_FIRE_KICK_LEFT;
	}
	else if (isDeceleration)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_FIRE_WALKING_RIGHT;
		else  aniId = ID_ANI_MARIO_FIRE_WALKING_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (vy < 0)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0) aniId = ID_ANI_MARIO_FIRE_JUMP_RUN_RIGHT;
				else aniId = ID_ANI_MARIO_FIRE_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx > 0) aniId = ID_ANI_MARIO_FIRE_JUMP_WALK_RIGHT;
				else aniId = ID_ANI_MARIO_FIRE_JUMP_WALK_LEFT;
			}
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_FALL_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_FALL_WALK_LEFT;
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FIRE_SIT_RIGHT;
			else aniId = ID_ANI_MARIO_FIRE_SIT_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_FIRE_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_FIRE_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = ID_ANI_MARIO_FIRE_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_FIRE_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_FIRE_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0) aniId = ID_ANI_MARIO_FIRE_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_FIRE_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_FIRE_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_FIRE_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx == 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_HOLD_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT;
		}
	}
	else if (isAttack)
	{
		aniId = ID_ANI_MARIO_RACCOON_ATTACK;
	}
	else if (isKick)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
		else  aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
	}
	else if (isDeceleration)
	{
		if (isFlying)
		{
			if (nx > 0)  aniId = ID_ANI_MARIO_RACCOON_FLYING_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_FLYING_LEFT;
		}
		else if (vy > 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_FALL_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_FALL_WALK_LEFT;
		}
		else
		{
			if (nx > 0)	aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
		}
	}
	else if (!isOnPlatform)
	{
		if (vy < 0)
		{
			if (isFlying)
			{
				if (nx > 0)  aniId = ID_ANI_MARIO_RACCOON_FLYING_RIGHT;
				else  aniId = ID_ANI_MARIO_RACCOON_FLYING_LEFT;
			}
			else
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
		}
		else
		{
			if (isSlowFly)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_FALL_SLOWLY_RIGHT;
				else  aniId = ID_ANI_MARIO_RACCOON_FALL_SLOWLY_LEFT;
			}
			else if (isFlying)
			{
				if (nx > 0)  aniId = ID_ANI_MARIO_RACCOON_FALL_RUN_RIGHT;
				else  aniId = ID_ANI_MARIO_RACCOON_FALL_RUN_LEFT;
			}
			else
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_FALL_WALK_RIGHT;
				else  aniId = ID_ANI_MARIO_RACCOON_FALL_WALK_LEFT;
			}
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0) 
				{
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				}
				else if (ax == MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else
			{
				if (ax > 0)
				{
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				}
				else if (ax == -MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}
		}
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
	return aniId;
}

int CMario::GetAniIdChangeLevel()
{
	int aniId = -1;
	if (level == MARIO_LEVEL_BIG)
	{
		if (nx > 0)
		{
			aniId = ID_ANI_SMALL_TO_BIG_RIGHT;
		}
		else
		{
			aniId = ID_ANI_SMALL_TO_BIG_LEFT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (nx > 0)
		{
			aniId = ID_ANI_SMALL_TO_SMALL_RIGHT;
		}
		else
		{
			aniId = ID_ANI_SMALL_TO_SMALL_LEFT;
		}
	}
	else if (level == MARIO_LEVEL_FIRE)
	{
		if (nx > 0)
		{
			aniId = ID_ANI_BIG_TO_FIRE_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BIG_TO_FIRE_LEFT;
		}
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		if (nx > 0)
		{
			aniId = ID_ANI_BIG_TO_RACCOON_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BIG_TO_RACCOON_LEFT;
		}
	}
	return aniId;
}

void CMario::SetState(int state)
{
	// DebugOut(L"STATE: %d\n", state);
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_KICK:
	{
		if (isSitting) break;
		time_line = GetTickCount64();
		isKick = true;
		break;
	}
	case MARIO_STATE_HOLDING:
	{
		if (isSitting) break;
		isHolding = true;
		koopa_holding->SetIsAttacking(true);
		break;
	}
	case MARIO_STATE_RELEASE_HOLDING:
	{
		isHolding = false;
		isRunning = false;
		break;
	}
	case MARIO_STATE_ATTACK:
	{
		if (isSitting || isChangeLevel) break;
		isAttack = true;
		time_line = GetTickCount64();
		break;
	}
	case MARIO_STATE_FALL_SLOWLY:
	{
		if (level != MARIO_LEVEL_RACCOON) break;
		time_line = GetTickCount64();
		isSlowFly = true;
		vy = - 0.001f;
		break;
	}
	case MARIO_STATE_FLYING:
	{
		if (isSitting) break;
		if (!isFlying) time_fly = GetTickCount64();
		isOnPlatform = false;
		isFlying = true;
		vy = -0.2f;
		break;
	}
	case MARIO_STATE_RELEASE_FLYING:
	{
		if (vy < 0)
		{
			vy += 0.2f / 2;
		}
		break;
	}
	case MARIO_STATE_DECELERATION:
	{
		isDeceleration = true;
		minVx = MARIO_DECELERATION_SPEED;
		if (vx < 0)
		{
			if (isRunning)
			{
				ax = MARIO_ACCEL_RUN_X;
			}
			else
			{
				ax = MARIO_ACCEL_WALK_X;
			}
		}
		else if (vx > 0)
		{
			if (isRunning)
			{
				ax = -MARIO_ACCEL_RUN_X;
			}
			else
			{
				ax = -MARIO_ACCEL_WALK_X;
			}
		}
		break;
	}
	case MARIO_STATE_RUNNING_RIGHT:
	{
		if (isSitting) break;
		isRunning = true;
		//isFlying = false;
		maxVx = MARIO_RUNNING_SPEED + power * MARIO_VMAX_X_ADJUST;;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	}
	case MARIO_STATE_RUNNING_LEFT:
	{
		if (isSitting) break;
		isRunning = true;
		maxVx = -MARIO_RUNNING_SPEED + power * MARIO_VMAX_X_ADJUST;;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	}
	case MARIO_STATE_WALKING_RIGHT:
	{
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	}
	case MARIO_STATE_WALKING_LEFT:
	{
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	}
	case MARIO_STATE_JUMP:
	{
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	}
	case MARIO_STATE_RELEASE_JUMP:
	{
		if (vy < 0)
		{
			vy += MARIO_JUMP_SPEED_Y / 2;
		}
		break;
	}
	case MARIO_STATE_SIT:
	{
		if (isAttack) break;
		if (isOnPlatform && level != MARIO_LEVEL_SMALL && vx == 0)
		{
			isSitting = true;
			vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	}
	case MARIO_STATE_SIT_RELEASE:
	{
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	}
	case MARIO_STATE_IDLE:
	{
		vx = 0.0f;
		ax = 0.0f;
		break;
	}
	case MARIO_STATE_DIE:
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if ((level == MARIO_LEVEL_BIG) || (level == MARIO_LEVEL_FIRE) || (level == MARIO_LEVEL_RACCOON))
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	if(this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	isChangeLevel = true;
	time_line = GetTickCount64();
	level = l;
}

void CMario::CountDown1Second() {
	//GetTickCount64() - x > y => x da chay y giay
	//x=GetTickCount64() => x bat dau chây 0 giay (khoi tao)
	if (time > 0) {
		if (MarioOutWorld()) {
			if (GetTickCount64() - count_1_second > TIME_ONE_SECOND) {
				time--;
				//THUC HIEN SAU 1 GIAY
				count_1_second = GetTickCount64();
			}
		}
		else {
			if (GetTickCount64() - count_1_second > 0) {
				time-=7;
				//THUC HIEN SAU 1 GIAY
				count_1_second = GetTickCount64();
			}
		}
	}
	else {
		time = 0;
		if (!disableKey) {
			SetState(MARIO_STATE_DIE);
		}
		else {
			canReturnWorldMap = true;
			//dem gio return worldmap = GetTickCount(64)
		}
	}
}

void CMario::LowerLevel() {
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::SummonFireBalls() {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CFireBallOfMario* frBalls = new CFireBallOfMario(x, y);
	scene->CreateObject(frBalls);
	if (this->nx > 0) {
		frBalls->SetState(FIREBALLS_STATE_RIGHT);
	} else {
		frBalls->SetState(FIREBALLS_STATE_LEFT);
	}
}

void CMario::SummonTail() 
{
	if (isChangeLevel || isSitting) return;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CTail* tail_right = new CTail(x, y);
	tail_right->SetState(TAIL_STATE_RIGHT);
	scene->CreateObject(tail_right);
	CTail* tail_left = new CTail(x, y);
	tail_left->SetState(TAIL_STATE_LEFT);
	scene->CreateObject(tail_left);

}

void CMario::MarioHoldKoopaFunction()
{
	if (state==MARIO_STATE_RUNNING_LEFT)
	{
		koopa_holding->SetX(x - 10);
	}
	else if(state == MARIO_STATE_RUNNING_RIGHT)
	{
		koopa_holding->SetX(x + 10);

	}
	koopa_holding->SetY(y - 2);
	koopa_holding->SetAy(0);
	koopa_holding->SetVX(vx);
}

void CMario::MarioThrowKoopaFunction()
{
	if (!isHolding && koopa_holding != NULL)
	{
		koopa_holding->SetState(KOOPA_STATE_ATTACKING);
		
		koopa_holding = NULL;
	}
}

bool CMario::CountDownTimer(int time)
{
	if (GetTickCount64() - time_line > time)
	{
		return true;
	}
	return false;
}

bool CMario::CountDownTimer2(ULONGLONG time_calculate, int time_out)
{
	if (GetTickCount64() - time_calculate > time_out)
	{
		return true;
	}
	return false;
}

void CMario::ChangeLevelMario(DWORD dt)
{
	if (isChangeLevel)
	{
		vx = 0;
		vy = 0;
	}
	else
	{
		vy += ay * dt;
		vx += ax * dt;
	}

	if (CountDownTimer(MARIO_CHANGE_LEVEL_TIMEOUT))
	{
		isChangeLevel = false;
	}
}

void CMario::AccelerationFunction()
{
	if (abs(vx) > abs(maxVx))
	{
		vx = maxVx;
	}
	else if (abs(vx) < abs(minVx))
	{
		SetState(MARIO_STATE_IDLE);
		isDeceleration = false;
	}
}

void CMario::CalculatePowerToFly()
{
	if (CountDownTimer2(time_power, 1000))
	{
		isDecreasePower = false;
		time_power = 0;
	}

	if (isFlying && IsMaxPower()) 
	{
		if (GetTickCount64() - time_fly > 5000) 
		{
			power = 0;
			isFlying = false;
			time_fly = 0;
		}
	}
	else 
	{
		if (isRunning && isOnPlatform && !isDecreasePower)
		{
			if (GetTickCount64() - time_running > 200)
			{
				if (power < 7)
				{
					power = power + 1;
				}
				time_running = GetTickCount64();
			}
		}
		else
		{
			if (GetTickCount64() - time_running > 200)
			{
				if (power > 0)
				{
					power = power - 1;
				}
				time_running = GetTickCount64();
			}
		}
	}
}

void CMario::CalculateHeartAndCoin()
{
	if (coin > 99)
	{
		heart++;
		coin = 0;
	}

	if (heart > 99)
	{
		heart = 99;
	}
}