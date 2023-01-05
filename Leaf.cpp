#include "Leaf.h"
#include "Point.h"
#include "PlayScene.h"

#define MAX_VY 0.02f

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	ax = 0;
	ay = LEAF_GRAVITY;
	isUp = false;
	isChange = false;
	isFlyLow = false;
	SetState(LEAF_STATE_FLY_UP);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	vy += ay * dt;
	vx += ax * dt;
	if (isUp && vy > 0)
	{
		SetState(LEAF_STATE_CHANGE);
		vx = LEAF_SPEED_X;
	}
	else if (isChange && CountDownTimer(LEAF_TIME_CHANGE))
	{
		SetState(LEAF_STATE_FLY_LOW);
	}
	else if (isFlyLow && CountDownTimer(LEAF_TIME_FLY_LOW))
	{
		SetState(LEAF_STATE_CHANGE);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = ID_ANI_LEAF_LEFT;
	if (vx > 0)
	{
		aniId = ID_ANI_LEAF_RIGHT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_FLY_UP:
	{
		isUp = true;
		vx = 0;
		vy = -LEAF_SPEED_Y;
		break;
	}
	case LEAF_STATE_CHANGE:
	{
		isChange = true;
		isUp = false;
		isFlyLow = false;
		time_line = GetTickCount64();
		ay = LEAF_GRAVITY;
		vx = -vx;
		vy = LEAF_SPEED_Y / 4;
		break;
	}
	case LEAF_STATE_FLY_LOW:
	{
		isFlyLow = true;
		isChange = false;
		ay = -LEAF_GRAVITY * LEAF_AY_FALL_SLOW;
		break;
	}
	default:
		break;
	}
	
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;
	if (e->ny != 0)
	{
		ax = 0;
		ay = 0;
		vx = 0;
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = 0;
	}
}

bool CLeaf::CountDownTimer(int time)
{
	if (GetTickCount64() - time_line > time)
	{
		return true;
	}
	return false;
}

void CLeaf::SummonScore()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CPoint* point = new CPoint(x, y, POINT_TYPE_1000);
	scene->CreateObject(point);
	point->SetState(POINT_STATE_MOVE_UP);
}