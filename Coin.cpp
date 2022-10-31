#include "Coin.h"
#include "Point.h"
#include "debug.h"
#include "PlayScene.h"


void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	//DebugOut(L"[TEST] y of coin: %d\n", y);
	if ((start_y - y) > COIN_DISTANCE_UP)
	{
		SetState(COIN_STATE_MOVE_DOWN);
		SetCoppyPosition(x, y);
		SummonAndMovePoint();
	}
	if ((vy > 0) && (y > (start_y - COIN_DISTANCE_DOWN)))
	{
		SetState(COIN_STATE_DELETE);
		check_delete_coin = 1;
	}
	if (check_delete_coin = 1) {


	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

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
		vy = MAX_VY;
		break;
	case COIN_STATE_DELETE:
	{
		Delete();
		break;
	}
	case COIN_STATE_MOVE_UP:
		vy = -MAX_VY;
		break;
	case COIN_STATE_IDLE:
		vy = 0;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CCoin::SummonAndMovePoint() {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CPoint* point = new CPoint(coppy_x, coppy_y, POINT_TYPE_100);
	scene->CreateObject(point);
	point->SetState(POINT_STATE_ADD_100);
}