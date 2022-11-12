#include "Platform.h"
#include "debug.h"
#include "ParaGoomba.h"
#include "Goomba.h"
#include "Koopa.h"
#include "KoopaParatroopas.h"

CParaGoomba::CParaGoomba(float x, float y) :CGameObject(x, y)
{
	this->ay = PARA_GOOMBA_GRAVITY;
	this->count_number_jumps = 0;
	die_start = -1;
	SetState(PARA_GOOMBA_STATE_WALKING);
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARA_GOOMBA_STATE_DIE)
	{
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - PARA_GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + PARA_GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - PARA_GOOMBA_BBOX_HEIGHT / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + PARA_GOOMBA_BBOX_HEIGHT;
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
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CKoopaParatroopas*>(e->obj)) return;

	if (e->ny < 0) {
		count_number_jumps++;
		vy = -PARA_GOOMBA_FLY_SPEED;
	}
	else if (e->nx != 0 && e->obj->IsBlocking()) { 
		vx = -vx; 
	}

	/*if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatForm(e);*/
}

void CParaGoomba::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	if (!platform->IsBlocking() && e->ny < 0) {
		DebugOut(L"[OKE] \n");
		count_number_jumps++;
		vy = -PARA_GOOMBA_FLY_SPEED;
	}
	else {
		
		count_number_jumps++;
		vy = -PARA_GOOMBA_FLY_SPEED;
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
	
	if ((state == PARA_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > PARA_GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParaGoomba::Render()
{
	int aniId = ID_ANI_PARA_GOOMBA_WALKING;
	if (state == PARA_GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARA_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARA_GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARA_GOOMBA_BBOX_HEIGHT - PARA_GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARA_GOOMBA_STATE_WALKING:
		vx = -PARA_GOOMBA_WALKING_SPEED;
		break;
	}
}

