#include "Platform.h"
#include "debug.h"
#include "ParaGoomba.h"
#include "Koopa.h"
#include "KoopaParatroopas.h"
#include "PlayScene.h"

CParaGoomba::CParaGoomba(float x, float y) :CGameObject(x, y)
{
	this->level = PARA_GOOMBA_LEVEL_BIG;
	this->ay = 0.0001f;
	this->count_number_jumps = 0;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE) {
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}

	if (level == PARA_GOOMBA_LEVEL_BIG) 
	{
			left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
			top = y - PARA_GOOMBA_BBOX_HEIGHT / 2;
			right = left + PARA_GOOMBA_BBOX_WIDTH;
			bottom = top + PARA_GOOMBA_BBOX_HEIGHT;
	}
	else 
	{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CParaGoomba*>(e->obj)) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;
	if (dynamic_cast<CKoopaParatroopas*>(e->obj)) return;

	if (level == PARA_GOOMBA_LEVEL_BIG) {
		if (e->ny < 0) 
		{
			count_number_jumps++;
			vy = -PARA_GOOMBA_FLY_SPEED;
		}
	} 
	else
	{
		if (e->ny < 0)
		{
			vy = 0;
		}
	}
	
	if (e->nx != 0 && e->obj->IsBlocking()) { 
		vx = -vx; 
	}
}


void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	/*DebugOut(L"[X] %f\n", x);
	DebugOut(L"[cam_X] %f\n", CGame::GetInstance()->GetCamX());*/

	if (!checkObjectInCamera()) {
		//SetState(PARA_GOOMBA_STATE_DIE);
	}

	if (count_number_jumps == 2) {
		
		vy = -PARA_GOOMBA_MAX_FLY_SPEED;
		count_number_jumps = 0;
	}
	
	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParaGoomba::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == GOOMBA_STATE_DIE)
		aniId = ID_ANI_GOOMBA_DIE;
	else if (level == PARA_GOOMBA_LEVEL_BIG)
		aniId = ID_ANI_PARA_GOOMBA_WALKING;
	else if (level == PARA_GOOMBA_LEVEL_SMALL)
		aniId = ID_ANI_GOOMBA_WALKING;
	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	default:
		break;
	}
}

void CParaGoomba::LowerLevel()
{
	if (level == PARA_GOOMBA_LEVEL_BIG)
	{
		level = PARA_GOOMBA_LEVEL_SMALL;
	}
	else
	{
		DebugOut(L">>> PARA KOOPA DIE >>> \n");
		SetState(GOOMBA_STATE_DIE);
	}
}

void CParaGoomba::SetLevel(int l)
{
	if (this->level == PARA_GOOMBA_LEVEL_SMALL)
	{
		y -= (PARA_GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT) / 2;
	}
	level = l;
}

