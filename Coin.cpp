#include "Coin.h"
#include "Point.h"
#include "debug.h"
#include "PlayScene.h"

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (!checkObjectInCamera()) return;
	if (state == COIN_STATE_MOVE_UP && GetTickCount64() - time_coin_up > COIN_UP_TIMEOUT)
	{
		time_coin_up = 0;
		SetState(COIN_STATE_MOVE_DOWN);
	}
	else if (!isSummonScore && state == COIN_STATE_MOVE_DOWN && GetTickCount64() - time_coin_down > COIN_DOWN_TIMEOUT)
	{
		time_coin_down = 0;
		SummonScore();
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::Render()
{
	if (!checkObjectInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = 0;
	if (type == COIN_TYPE_TURN_AROUND_SMALL) aniId = ID_ANI_COIN_AROUND_SMALL;
	else if (type == COIN_TYPE_TURN_AROUND_BIG) aniId = ID_ANI_COIN_AROUND_BIG;
	else aniId = ID_ANI_COIN_BRICK;
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CCoin::SetState(int state)
{
	switch (state)
	{
	case COIN_STATE_MOVE_DOWN:
	{
		time_coin_down = GetTickCount64();
		vy = MAX_VY;
		break;
	}
	case COIN_STATE_MOVE_UP:
	{
		vy = -MAX_VY;
		time_coin_up = GetTickCount64();
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CCoin::SummonScore()
{
	isSummonScore = true;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CPoint* point = new CPoint(x, y, POINT_TYPE_100);
	scene->CreateObject(point);
	point->SetState(POINT_STATE_MOVE_UP);
}