#include "FireBallOfMario.h"
#include "debug.h"
#include "PlayScene.h"
#include"Koopa.h"
#include"VenusFireTrap.h"
#include"Goomba.h"
#include"Goomba.h"

CFireBallOfMario::CFireBallOfMario(float x, float y) :CGameObject(x, y)
{
	SetState(FIREBALLS_STATE_SHOOT);
}

void CFireBallOfMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
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

void CFireBallOfMario::OnNoCollision(DWORD dt) 
{
	x += vx * dt;
	y += vy * dt;
}

void CFireBallOfMario::OnCollisionWith(LPCOLLISIONEVENT e){
	if (e->ny != 0 && e->obj->IsBlocking()) {
		vy = -FIREBALLS_MARIO_SPEED_Y;
	}
	else if (e->nx != 0 && e->obj->IsBlocking()) {
		vx = -vx;
	} 
	if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CVenusFireTrap*>(e->obj))
		OnCollisionWithVenusFireTrap(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
}

void CFireBallOfMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	//Koopa will turned over and died.
	CGoomba* para_goomba = dynamic_cast<CGoomba*>(e->obj);
	para_goomba->SetState(GOOMBA_STATE_DIE);
}

void CFireBallOfMario::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	//Koopa will turned over and died.
	CVenusFireTrap* venus_fire_trap = dynamic_cast<CVenusFireTrap*>(e->obj);
	venus_fire_trap->SetState(VFTRAP_STATE_DIE);
}

void CFireBallOfMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	//Koopa will turned over and died.
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	koopa->SetState(KOOPA_STATE_DIE_TURN_OVER);
}

void CFireBallOfMario::SetState(int state)
{
	switch (state)
	{
	case FIREBALLS_STATE_RIGHT:
		vx = FIREBALLS_MARIO_SPEED_X;
		break;
	case FIREBALLS_STATE_LEFT:
		vx = -FIREBALLS_MARIO_SPEED_X;
		break;
	case FIREBALL_MARIO_STATE_DELETE:
	{
		Delete();
		break;
	}
	case FIREBALLS_STATE_SHOOT:
		ay = FIREBALLS_MARIO_GRAVITY;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}