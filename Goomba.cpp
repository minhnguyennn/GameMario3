#include "Platform.h"
#include "debug.h"
#include "Goomba.h"
#include "Koopa.h"
#include "KoopaParatroopas.h"
#include "PlayScene.h"
#include "Platform.h"

CGoomba::CGoomba(float x, float y, int level, int type) :CGameObject(x, y)
{
	this->type = type;
	this->level = level;
	this->ay = GOOMBA_GRAVITY;
	this->count_number_jumps = 0;
	this->time_line = -1;
	this->isCloseWing = false;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE) {
		left = x - GOOMBA_SMALL_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_SMALL_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}

	if (level == GOOMBA_LEVEL_BIG && !isCloseWing)
	{
			left = x - GOOMBA_BIG_BBOX_WIDTH / 2;
			top = y - GOOMBA_BIG_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BIG_BBOX_WIDTH;
			bottom = top + GOOMBA_BIG_BBOX_HEIGHT;
	}
	else if (level == GOOMBA_LEVEL_SMALL && !isCloseWing)
	{
			left = x - GOOMBA_SMALL_BBOX_WIDTH / 2;
			top = y - GOOMBA_SMALL_BBOX_HEIGHT / 2;
			right = left + GOOMBA_SMALL_BBOX_WIDTH;
			bottom = top + GOOMBA_SMALL_BBOX_HEIGHT;
	}
	else if (isCloseWing) {
		left = x - GOOMBA_BIG_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_CLOSE_WING_HEIGHT / 2;
		right = left + GOOMBA_BIG_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_CLOSE_WING_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;
	if (dynamic_cast<CKoopaParatroopas*>(e->obj)) return;

	if (e->ny < 0)
	{
		if (level == GOOMBA_LEVEL_BIG) 
		{
			SetState(GOOMBA_STATE_FLY);
		}
		else
		{
			vy = 0;
		}
	}
	
	if (e->nx != 0 && e->obj->IsBlocking()) { 
		vx = -vx; 
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"[oke] isCloseWing: %d\n", isCloseWing);
	vy += ay * dt;
	/*DebugOut(L"[X] %f\n", x);
	DebugOut(L"[cam_X] %f\n", CGame::GetInstance()->GetCamX());*/

	if (!checkObjectInCamera()) {
		//SetState(PARA_GOOMBA_STATE_DIE);
	}

	if (count_number_jumps > 2 ) {
		SetState(GOOMBA_STATE_CLOSE_WING);
		if (GetTickCount64() - time_line > 1000) {
			SetState(GOOMBA_STATE_FLY_MAX);
		}
	}
	
	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - time_line > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGoomba::Render()
{
	int aniId = 0;
	if (state == GOOMBA_STATE_DIE)
		aniId = ID_ANI_GOOMBA_DIE;
	else if (level == GOOMBA_LEVEL_BIG && !isCloseWing && type == GOOMBA_TYPE_PARA_GOOMBA)
		aniId = ID_ANI_GOOMBA_BIG_WALKING;
	else if (level == GOOMBA_LEVEL_SMALL && type == GOOMBA_TYPE_PARA_GOOMBA)
		aniId = ID_ANI_GOOMBA_SMALL_WALKING;
	else if (isCloseWing)
		aniId = ID_ANI_GOOMBA_CLOSE_WING;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		time_line = GetTickCount64();
		y += (GOOMBA_SMALL_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_FLY:
		time_line = GetTickCount64();
		count_number_jumps++;
		vy = -GOOMBA_FLY_SPEED;
		break;
	case GOOMBA_STATE_CLOSE_WING:
		vy = 0;
		isCloseWing = true;
		break;
	case GOOMBA_STATE_FLY_MAX:
		vy = -GOOMBA_MAX_FLY_SPEED;
		count_number_jumps = 0;
		isCloseWing = false;
		break;
	default:
		break;
	}
}

void CGoomba::LowerLevel()
{
	if (level == GOOMBA_LEVEL_BIG )
	{
		level = GOOMBA_LEVEL_SMALL;
	}
	else
	{
		DebugOut(L">>> PARA KOOPA DIE >>> \n");
		SetState(GOOMBA_STATE_DIE);
	}
}

void CGoomba::SetLevel(int l)
{
	if (this->level == GOOMBA_LEVEL_SMALL)
	{
		y -= (GOOMBA_BIG_BBOX_HEIGHT - GOOMBA_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

