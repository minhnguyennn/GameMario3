#include "Koopa.h"
#include"debug.h"
#include"Platform.h"


void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if ((isDefense)  || (isWaiting ))
	{
		left = x - KOOPA_BBOX_WAITING / 2;
		top = y - KOOPA_BBOX_WAITING / 2;
		right = left + KOOPA_BBOX_WAITING;
		bottom = top + KOOPA_BBOX_WAITING;
	}
	else 
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatForm(e);
}

void CKoopa::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	float plant_form_y = platform->GetY();
	float plat_form_x_start = platform->GetX() - 8;
	float plat_form_x_end = platform->GetX() + (platform->GetLength() * 15);
	if (!platform->IsBlocking()) {
		if (e->ny < 0) {
			vy = 0;
			if (!isDefense) {
				y = plant_form_y - KOOPA_DISTANCE_WITH_PLANTFORM;
				if (x < plat_form_x_start) {
					vx = -vx;
				}
				if (x > plat_form_x_end) {
					vx = -vx;
				}
			
			}
		}
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	DebugOut(L"AY VY %f %f \n", ay, vy);
	//DebugOut(L"[OKE] x: %f\n", start_x);
	//DebugOut(L"[OKE] isDefense  %d  \n", isDefense);

	if ( isDefense == true && (GetTickCount64() - close_start > KOOPA_CLOSE_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_WAITING);
		//DebugOut(L"[OKE] isDefense isWaiting waiting_start %d %d %f \n", isDefense, isWaiting, waiting_start);
		
	}

	if (isWaiting == true && (GetTickCount64() - waiting_start > KOOPA_CLOSE_SHELL_TIMEOUT))
	{
		DebugOut(L"[OKE]\n");
		SetState(KOOPA_STATE_RETURN_WALKING);
	}
	
	
	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	//Type of animation
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (isWaiting == true)
	{
		//DebugOut(L"[OKE]\n");
		aniId = ID_ANI_KOOPA_WAITING;
	}
	else if (isDefense == true)
	{
		//DebugOut(L"[OKE]\n");
		aniId = ID_ANI_KOOPA_CLOSE_SHELL;
	}
	else if (vx > 0)
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	//DebugOut(L"[OKE] aniId: %d\n", aniId);
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	switch (state)
	{
	case KOOPA_STATE_WAITING:
	
		vx = 0;
		ay = 0;
		//DebugOut(L"[OKE]\n");
		isWaiting = true;
		isDefense = false;
		isTurnOver = false;
		//DebugOut(L"[KOOPA_STATE_WAITING] isDefense: %d\n", isDefense);
		waiting_start = GetTickCount64();
		//DebugOut(L"[OKE] waiting_start: %d\n", waiting_start);
		break;
	case KOOPA_STATE_CLOSE_SHELL:
		//DebugOut(L"[OKE]\n");
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_WAITING) / 2;
		vx = 0;
		ay = 0;
		close_start = GetTickCount64();
		//DebugOut(L"[OKE] close_start: %d\n", close_start);
		isDefense = true;
		isTurnOver = false;
		isWaiting = false;
		break;
	case KOOPA_STATE_WALKING:
		ay = KOOPA_GRAVITY;
		vx = -KOOPA_WALKING_SPEED;
		if (isWaiting) {
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_WAITING) / 2;

		}
		isWaiting = false;
		isDefense = false;
		isTurnOver = false;
		break;
	default:
		break; 
	}
	CGameObject::SetState(state);

}
