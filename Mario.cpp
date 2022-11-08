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
#include "Platform.h"
#include "Collision.h"
#include "PlayScene.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{	
	//DebugOut(L"isHold %d \n", isHolding);
	//DebugOut(L"Level %d", level);
	// DebugOut(L"[test] vx ax state nx time vmax %f %f %d %d %d %f\n", vx , ax, state, nx,time,maxVx);
	//CountDown1Second();
	vy += ay * dt;
	vx += ax * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (isSitting || isDeceleration){
		//DebugOut(L"[oke]");
		ax = 0.0f;
		if (abs(maxVx) > MARIO_DECELERATION) {
			if (nx > 0) { maxVx -= MARIO_DECELERATION; }
			else if (nx < 0) { maxVx += MARIO_DECELERATION;  }
		} 
		else
		{
			maxVx = 0;
		}
	}
	
	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

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
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
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
}

void CMario::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{

	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	float plant_form_y = platform->GetY();
	if (!platform->IsBlocking()) {
		if (e->ny < 0) {
			vy = 0;
			if (level != MARIO_LEVEL_SMALL) {
				if (!isSitting) {
					y = (plant_form_y - MARIO_DISTANCE_WITH_GHOST_BOX);
				}
				else {
					y = (plant_form_y - (MARIO_DISTANCE_WITH_GHOST_BOX - 4));
				}
			}
			else {
				y = (plant_form_y - (MARIO_DISTANCE_WITH_GHOST_BOX - 6));
			}
			isOnPlatform = true;
		}
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		LowerLevel();
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		koopa->SetVY(-KOOPA_JUMP_DEFLECT_SPEED);
		if (!koopa->GetIsDefense() && !koopa->GetIsWaiting())
		{
			if (koopa->GetIsAttacking()) koopa->SetY(koopa->GetY() - 5);
			koopa->SetState(KOOPA_STATE_CLOSE_SHELL);
		}
		else koopa->SetState(KOOPA_STATE_ATTACKING);
	}
	else if (e->nx != 0) {
		
		if ((koopa->GetState() == KOOPA_STATE_WALKING) || (koopa->GetIsAttacking())) {
			LowerLevel();
		}
		else if (isRunning)
		{
			//DebugOut(L"[OKE2] \n");
			isHolding = true;
			koopa->SetIsHeld(true);
		}
		else {
			//DebugOut(L"[OKE1] \n");
			//isHolding = false;
			koopa->SetState(KOOPA_STATE_ATTACKING);
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

	if (level == MARIO_LEVEL_SMALL) {
		SetLevel(MARIO_LEVEL_BIG);
	}
	else {
		coin++;
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{

	CLeaf* p = (CLeaf*)e->obj;
	p->Delete();
	if ((level == MARIO_LEVEL_SMALL) || (level == MARIO_LEVEL_BIG)) {
		SetLevel(MARIO_LEVEL_FIRE);
	}
	else {
		coin++;
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{

	CQuestionBrick* p = dynamic_cast<CQuestionBrick*>(e->obj);
	if ((p->GetState() == QUESTION_STATE_IDLE) && (e->ny>0)){
		p->SetState(QUESTION_STATE_MOVE_UP);
	}

}


int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (!isHolding) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (!isHolding) {
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else {
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X) {
					if (!isHolding) { aniId = ID_ANI_MARIO_RUNNING_RIGHT; }
					else { aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT; }
				}
				else if (ax == MARIO_ACCEL_WALK_X || isDeceleration)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;	
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					if (!isHolding) { aniId = ID_ANI_MARIO_RUNNING_LEFT; }
					else { aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT; }
				else if (ax == -MARIO_ACCEL_WALK_X || isDeceleration)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}
	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (!isHolding) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (!isHolding) {
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				else {
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_HOLD_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (!isHolding) { aniId = ID_ANI_MARIO_RUNNING_RIGHT; }
					else { aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT; }
				}
				else if ((ax == MARIO_ACCEL_WALK_X) || isDeceleration)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X) {
					if (!isHolding) { aniId = ID_ANI_MARIO_RUNNING_LEFT; }
					else { aniId = ID_ANI_MARIO_HOLD_WALK_LEFT; }
				}
				else if ((ax == -MARIO_ACCEL_WALK_X) || isDeceleration)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdFire()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_FIRE_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_FIRE_JUMP_RUN_LEFT;
		}
		else
		{
			if (!isHolding) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_FIRE_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_FIRE_JUMP_WALK_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_FIRE_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_FIRE_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (!isHolding) {
					if (nx > 0) aniId = ID_ANI_MARIO_FIRE_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_FIRE_IDLE_LEFT;
				}
				else {
					if (nx > 0) aniId = ID_ANI_MARIO_FIRE_IDLE_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_FIRE_IDLE_HOLD_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_FIRE_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X) {
					if (!isHolding) { aniId = ID_ANI_MARIO_FIRE_RUNNING_RIGHT; }
					else { aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_RIGHT; }
				}
				else if (ax == MARIO_ACCEL_WALK_X || isDeceleration) {
					aniId = ID_ANI_MARIO_FIRE_WALKING_RIGHT; 
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_FIRE_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X) {
					if (!isHolding) { aniId = ID_ANI_MARIO_FIRE_RUNNING_LEFT; }
					else { aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_LEFT; }
				}
				else if (ax == -MARIO_ACCEL_WALK_X || isDeceleration) {
					 aniId = ID_ANI_MARIO_FIRE_WALKING_LEFT; 
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_FIRE_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (!isHolding) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT;
			}
			
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (!isHolding) {
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
				}
				else {
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || (isDeceleration)) {
					if (!isHolding) { aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT; }
					else { aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT; }
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || isDeceleration)
					if (!isHolding) { aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT; }
					else { aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT; }
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	
	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_FIRE)
		aniId = GetAniIdFire();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();
	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_SUMMON_KOOPA:
		isHolding = true;
		break;
	case MARIO_STATE_DECELERATION:
		isDeceleration = true;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		isDeceleration = false;
		isRunning = true;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		isDeceleration = false;
		isRunning = true;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		isDeceleration = false;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		isDeceleration = false;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		isDeceleration = false;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) { 
			isDeceleration = false;
			vy += MARIO_JUMP_SPEED_Y / 2; 
		}
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			isSitting = true;
			isDeceleration = false;
			vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST - 4;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			isDeceleration = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		isDeceleration = false;
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		isDeceleration = false;
		vx = 0;
		ax = 0;
		break;
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_RACCOON){
		
		if (isSitting)
		{
			left = x - MARIO_RACCOON_SITTING_BBOX_WIDTH / 2 ;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACCOON_BBOX_WIDTH / 2 ;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if ((level == MARIO_LEVEL_BIG) || (level == MARIO_LEVEL_FIRE))
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
	// Adjust position to avoid falling off platform
	if(this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::CountDown1Second() {
	//GetTickCount64() - x > y => x da chay y giay
	//x=GetTickCount64() => x bat dau ch�y 0 giay (khoi tao)
	if (time > 0) {
		if (GetTickCount64() - count_1_second > TIME_ONE_SECOND) {
			time--;
			//THUC HIEN SAU 1 GIAY
			count_1_second = GetTickCount64();
		}
	}
	else {
		time = 0;
		SetState(MARIO_STATE_DIE);
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

void CMario::Summon(CGameObject *game_object) {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CKoopa* koopa = new CKoopa(x, y);
	scene->CreateObject(koopa);
	koopa->SetIsSummon(true);
}