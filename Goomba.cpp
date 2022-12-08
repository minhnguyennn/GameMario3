#include "Platform.h"
#include "debug.h"
#include "Goomba.h"
#include "Koopa.h"
#include "PlayScene.h"
#include "Platform.h"

CGoomba::CGoomba(float x, float y, int level, int type) :CGameObject(x, y)
{
	this->type = type;
	this->level = level;
	isCloseWing = false;
	isTurnOver = false;
	isDie = false;
	isWalk = false;
	ay = GOOMBA_GRAVITY;
	count_number_jumps = 0;
	time_line = 0;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isTurnOver) return;
	if (state == GOOMBA_STATE_DIE) {
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_DIE;
	}
	else 
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
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

	if (e->ny < 0)
	{
		if (level == GOOMBA_LEVEL_BIG) 
		{
			if (count_number_jumps == 3)
			{
				SetState(GOOMBA_STATE_FLY_MAX);
			}
			else if (isWalk)
			{
				SetState(GOOMBA_STATE_CLOSE_WING);
			}
			else if (GetTickCount64() - time_close > 1000)
			{
				SetState(GOOMBA_STATE_FLY);
			}
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
	if (!checkObjectInCamera()) return;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario->GetIsChangeLevel()) return;
	vy += ay * dt;
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
	if (!checkObjectInCamera()) return;

	int aniId = 0;

	if (isTurnOver)
	{
		if (type == GOOMBA_TYPE_BROWN)
		{
			aniId = ID_ANI_GOOMBA_BROWN_TURN_OVER;
		}
		else
		{
			aniId = ID_ANI_GOOMBA_RED_TURN_OVER;
		}
	}
	else if (isDie)
	{
		if (type == GOOMBA_TYPE_BROWN)
		{
			aniId = ID_ANI_GOOMBA_BROWN_DIE;
		}
		else
		{
			aniId = ID_ANI_GOOMBA_RED_DIE;
		}
	}
	else if (level == GOOMBA_LEVEL_BIG)
	{
		if (type == GOOMBA_TYPE_BROWN)
		{
			if (isCloseWing)
			{
				aniId = ID_ANI_GOOMBA_BROWN_CLOSE_WING;
			}
			else
			{
				aniId = ID_ANI_GOOMBA_BROWN_LEVEL_BIG;
			}
		}
		else
		{
			if (isCloseWing)
			{
				aniId = ID_ANI_GOOMBA_RED_CLOSE_WING;
			}
			else
			{
				aniId = ID_ANI_GOOMBA_RED_LEVEL_BIG;
			}
		}
	}
	else if (level == GOOMBA_LEVEL_SMALL)
	{
		if (type == GOOMBA_TYPE_BROWN)
		{
			aniId = ID_ANI_GOOMBA_BROWN_LEVEL_SMALL;
		}
		else
		{
			aniId = ID_ANI_GOOMBA_RED_LEVEL_SMALL;
		}
	}

	if (level == GOOMBA_LEVEL_BIG)
	{
		CAnimations::GetInstance()->Get(aniId)->Render(x, y - 3);
	}
	else
	{
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}

	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	//DebugOut(L"state: ay: %d %f\n", state, ay);
	switch (state)
	{
	case GOOMBA_STATE_DIE_TURN_OVER:
	{
		isTurnOver = true;
		vx = -0.05f;
		vy = -0.05f;
		break;
	}
	case GOOMBA_STATE_DIE:
		time_line = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_FLY:
		count_number_jumps++;
		vy = -GOOMBA_FLY_SPEED;
		isCloseWing = false;
		break;
	case GOOMBA_STATE_CLOSE_WING:
		isWalk = false;
		vy = 0;
		isCloseWing = true;
		time_close = GetTickCount64();
		break;
	case GOOMBA_STATE_FLY_MAX:
		isWalk = true;
		vy = -GOOMBA_MAX_FLY_SPEED;
		count_number_jumps = 0;
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

