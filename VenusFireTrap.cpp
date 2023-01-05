#include "VenusFireTrap.h"
#include"debug.h"
#include "Time.h"
#include "PlayScene.h"
#include "FireBalls.h"
#include "Point.h"
#include "Mario.h"

CVenusFireTrap::CVenusFireTrap(float x, float y, int type) :CGameObject(x, y)
{
	isIdle = false;
	this->type = type;
	this->start_y = y;
	SetState(VFTRAP_STATE_UP);
}

void CVenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (type == VFTRAP_TYPE_RED)
	{
		left = x - VFTRAP_BBOX_RED_WIDTH / 2;
		top = y - VFTRAP_BBOX_RED_HEIGHT / 2;
		right = left + VFTRAP_BBOX_RED_WIDTH;
		bottom = top + VFTRAP_BBOX_RED_HEIGHT;
	}
	else if (type == VFTRAP_TYPE_GREEN)
	{
		left = x - VFTRAP_BBOX_GREEN_WIDTH / 2;
		top = y - VFTRAP_BBOX_GREEN_HEIGHT / 2;
		right = left + VFTRAP_BBOX_GREEN_WIDTH;
		bottom = top + VFTRAP_BBOX_GREEN_HEIGHT;
	}
	else if (type == VFTRAP_TYPE_PIRANHA)
	{
		left = x - VFTRAP_BBOX_PIRANHA_WIDTH / 2;
		top = y - VFTRAP_BBOX_PIRANHA_HEIGHT / 2;
		right = left + VFTRAP_BBOX_PIRANHA_WIDTH;
		bottom = top + VFTRAP_BBOX_PIRANHA_HEIGHT;
	}
}

void CVenusFireTrap::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CVenusFireTrap::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CVenusFireTrap*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario->GetIsChangeLevel()) return;
	if (type == VFTRAP_TYPE_PIRANHA) 
		MoveFunctionPlant(VFTRAP_DIST_UP_PIRA, VFTRAP_DIST_DOWN_PIRA);
	else if (type == VFTRAP_TYPE_GREEN)
		MoveFunctionPlant(VFTRAP_DIS_UP_GREEN, VFTRAP_DIS_DOWN_GREEN);
	else 
		MoveFunctionPlant(VFTRAP_DIS_UP_RED, VFTRAP_DIS_DOWN_RED);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CVenusFireTrap::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = 0;
	if (type == VFTRAP_TYPE_GREEN)
	{
		if (!isMarioLeftWithPlant())
		{
			if (isMarioAboveWithPlant())
			{
				aniId = ID_ANI_VFTRAP_GREEN_TOP_RIGHT;
			}
			else
			{
				aniId = ID_ANI_VFTRAP_GREEN_BOTTOM_RIGHT;
			}
		}
		else
		{
			if (isMarioAboveWithPlant())
			{
				aniId = ID_ANI_VFTRAP_GREEN_TOP_LEFT;
			}
			else 
			{
				aniId = ID_ANI_VFTRAP_GREEN_BOTTOM_LEFT;
			}
		}

		if (state == VFTRAP_STATE_DIE)
		{
			aniId = ID_ANI_VFTRAP_GREEN_DIE;
		}
	}
	else if (type == VFTRAP_TYPE_RED)
	{
		if (!isMarioLeftWithPlant())
		{
			if (isMarioAboveWithPlant())
			{
				if (isIdle) aniId = ID_ANI_VFTRAP_RED_TOP_RIGHT_ATTACK;
				else aniId = ID_ANI_VFTRAP_RED_TOP_RIGHT;
			}
			else
			{
				if (isIdle) aniId = ID_ANI_VFTRAP_RED_BOTTOM_RIGHT_ATTACK;
				else aniId = ID_ANI_VFTRAP_RED_BOTTOM_RIGHT;
			}
		}
		else if (isMarioLeftWithPlant())
		{
			if (isMarioAboveWithPlant())
			{
				if (isIdle) aniId = ID_ANI_VFTRAP_RED_TOP_LEFT_ATTACK;
				else aniId = ID_ANI_VFTRAP_RED_TOP_LEFT;
			}
			else
			{
				if (isIdle) aniId = ID_ANI_VFTRAP_RED_BOTTOM_LEFT_ATTACK;
				else aniId = ID_ANI_VFTRAP_RED_BOTTOM_LEFT;
			}
		}
		else if (state == VFTRAP_STATE_DIE)
		{
			aniId = ID_ANI_VFTRAP_RED_DIE;
		}
	}
	else
	{
		aniId = ID_ANI_PIRANHA_PLANT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CVenusFireTrap::SetState(int state)
{
	switch (state)
	{
	case VFTRAP_STATE_UP:
	{
		vy = -VFTRAP_MOVING_SPEED;
		isIdle = false;
		break;
	}
	case VFTRAP_STATE_DOWN:
	{
		vy = VFTRAP_MOVING_SPEED;
		isIdle = false;
		break;
	}
	case VFTRAP_STATE_IDLE:
	{
		isIdle = true;
		vy = 0;
		time_line = GetTickCount64();
		break;
	}
	case VFTRAP_STATE_DIE:
	{
		isDeleted = true;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CVenusFireTrap::ChangeStateMotionDown(ULONGLONG time_type) 
{
	if (CountDownTimer(time_type))
	{
		if (type == VFTRAP_TYPE_RED) 
		{
			SetSummonItems(VFTRAP_TYPE_FIRE_BALL);
			
		}
		SetState(VFTRAP_STATE_DOWN);
	}
}

void CVenusFireTrap::ChangeStateMotionUp(ULONGLONG time_type) 
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (abs(x - mario->GetX()) < VFTRAP_DIST_MARIO) return;
	if (CountDownTimer(time_type)) SetState(VFTRAP_STATE_UP);
}

void CVenusFireTrap::SetSummonItems(int type) 
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	switch (type)
	{
	case VFTRAP_TYPE_FIRE_BALL:
	{
		CMario* mario = (CMario*)scene->GetPlayer();
		CFireBalls* fire_balls = new CFireBalls(x, y);
		scene->CreateObject(fire_balls);
		if (!isMarioLeftWithPlant())
		{
			if (isMarioAboveWithPlant()) fire_balls->SetState(FIREBALLS_STATE_MOVE_RIGHT_TOP);
			else
			{
				if (mario->GetX() - x < VFTRAP_DIST_FIREBALL) fire_balls->SetState(FIREBALLS_STATE_RIGHT_BOTTOM);
				else fire_balls->SetState(FIREBALLS_STATE_MOVE_RIGHT);
			}
		}
		else
		{
			if (isMarioAboveWithPlant()) fire_balls->SetState(FIREBALLS_STATE_MOVE_LEFT_TOP);
			else
			{
				if (x - mario->GetX() < VFTRAP_DIST_FIREBALL) fire_balls->SetState(FIREBALLS_STATE_LEFT_BOTTOM);
				else fire_balls->SetState(FIREBALLS_STATE_MOVE_LEFT);
			}
		}
		break;
	}
	case VFTRAP_TYPE_POINT:
	{
		CPoint* point_100 = new CPoint(x, y, POINT_TYPE_100);
		scene->CreateObject(point_100);
		break;
	}
	default:
		break;
	}
}

bool CVenusFireTrap::isMarioLeftWithPlant()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario->GetX() < x) return true;
	else return false;
}

bool CVenusFireTrap::isMarioAboveWithPlant()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario->GetY() < y) return true;
	else return false;
}

void CVenusFireTrap::MoveFunctionPlant(float disUp, float disDown) 
{
	if ((start_y - y) > disUp)
	{
		if (state == VFTRAP_STATE_UP) SetState(VFTRAP_STATE_IDLE);
		else
		{
			if (type == VFTRAP_TYPE_PIRANHA) ChangeStateMotionDown(VFTRAP_WAITING_PIRAN);
			else ChangeStateMotionDown(VFTRAP_WAITING_MAX);
		}
	}

	if ((y - start_y) > disDown)
	{
		if (state == VFTRAP_STATE_DOWN) SetState(VFTRAP_STATE_IDLE);
		else
		{
			if (type == VFTRAP_TYPE_PIRANHA) ChangeStateMotionUp(VFTRAP_WAITING_PIRAN);
			else ChangeStateMotionUp(VFTRAP_WAITING_MAX);
		}
	}
}

bool CVenusFireTrap::CountDownTimer(ULONGLONG time)
{
	if (GetTickCount64() - time_line > time)
	{
		return true;
	}
	return false;
}

void CVenusFireTrap::SummonScore()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CPoint* point = new CPoint(x, y, POINT_TYPE_100);
	scene->CreateObject(point);
	point->SetState(POINT_STATE_MOVE_UP);
}