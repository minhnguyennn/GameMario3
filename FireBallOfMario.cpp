#include "FireBallOfMario.h"
#include "debug.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Pipeline.h"
#include"Platform.h"

#define FIREBALLS_SPEED_Y 0.09f
#define FIREBALLS_SPEED_X 0.06f

CFireBallOfMario::CFireBallOfMario(float x, float y) :CGameObject(x, y)
{
	SetState(FIREBALLS_STATE_SHOOT);
}

void CFireBallOfMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	//if (vy < 0 && abs(x - start_x) > FIREBALLS_DISTANCE_MAX_UP) {
	//	//DebugOut(L"[OK1] \n");
	//	SetState(FIREBALLS_STATE_DOWN);
	//}

	//if (vy > 0 && abs(x - start_x) > FIREBALLS_DISTANCE_MAX_DOWN) {
	//	//DebugOut(L"[OK2] \n");
	//	SetState(FIREBALLS_STATE_UP);
	//}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBallOfMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL_OF_MARIO)->Render(x, y);
	//RenderBoundingBox();
}

void CFireBallOfMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALLS_BBOX_WIDTH / 2;
	t = y - FIREBALLS_BBOX_HEIGHT / 2;
	r = l + FIREBALLS_BBOX_WIDTH;
	b = t + FIREBALLS_BBOX_HEIGHT;
}

void CFireBallOfMario::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;

}

void CFireBallOfMario::OnCollisionWith(LPCOLLISIONEVENT e){
	if (e->obj->IsBlocking())
	{
		vy = -FIREBALLS_SPEED_Y;
	}
}

void CFireBallOfMario::SetState(int state)
{
	switch (state)
	{
	case FIREBALLS_STATE_RIGHT:
		vx = FIREBALLS_SPEED_X;
		break;
	case FIREBALLS_STATE_LEFT:
		vx = -FIREBALLS_SPEED_X;
		break;
	/*case FIREBALLS_STATE_DOWN:
		vy = FIREBALLS_SPEED_Y;
		start_x = x;
		break;*/
	case FIREBALLS_STATE_DELETE:
	{
		Delete();
		break;
	}
	case FIREBALLS_STATE_SHOOT:
		ay = FIREBALLS_GRAVITY;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}



