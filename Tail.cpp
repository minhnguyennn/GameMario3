#include "Tail.h"
#include "debug.h"
#include "koopa.h"
#include "PlayScene.h"
#include "VenusFireTrap.h"
#include "Goomba.h"


CTail::CTail(float x, float y) :CGameObject(x, y)
{
	//ChangePositionFollowMario();
	this->time_line = GetTickCount64();
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (GetTickCount64() - time_line > 100)
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TAIL)->Render(x, y);
	RenderBoundingBox();
}

void CTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TAIL_BBOX_WIDTH / 2;
	t = y - TAIL_BBOX_HEIGHT / 2;
	r = l + TAIL_BBOX_WIDTH;
	b = t + TAIL_BBOX_HEIGHT;
}

void CTail::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CVenusFireTrap*>(e->obj))
		OnCollisionWithVenusFireTrap(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
}

void CTail::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa->GetLevel() == KOOPA_LEVEL_BIG)
	{
		koopa->LowerLevel();
	}
	else
	{
		koopa->SetState(KOOPA_STATE_TURN_OVER);
	}
}

void CTail::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	CVenusFireTrap* vnf_trap = dynamic_cast<CVenusFireTrap*>(e->obj);
	vnf_trap->SetState(VFTRAP_STATE_DIE);
}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	goomba->LowerLevel();
}

void CTail::ChangePositionFollowMario()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	x = mario->GetX();
	y = mario->GetY();
}

void CTail::SetState(int state)
{

	switch (state)
	{
	case TAIL_STATE_RIGHT:
	{
		vx = 0.1f;
		break;
	}
	case TAIL_STATE_LEFT:
	{
		vx = -0.1f;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}
