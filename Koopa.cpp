#include "Koopa.h"
#include"debug.h"
#include"Platform.h"


void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_CLOSE)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_CLOSE / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_CLOSE;
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
	if (!platform->IsBlocking()) {
		if (e->ny < 0) {
			vy = 0;
			y = plant_form_y - KOOPA_DISTANCE_WITH_PLANTFORM;
		}
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	
	//DebugOut(L"[OKE] x: %f\n", start_x);

	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	/*if (abs(start_x - x) > KOOPA_DISTANCE_MAX) {
		vx = -vx;
	}*/

	//if ((vx < 0) && ((start_x - x) > KOOPA_DISTANCE_MAX)) {
	//	SetState(KOOPA_STATE_IDLE);
	//	vx = -vx;
	//}

	//if ((vx > 0) && ((x - start_x) > (KOOPA_DISTANCE_MAX + 24))) {
	//	DebugOut(L"[OKE]\n");
	//	SetState(KOOPA_STATE_IDLE);
	//	vx = -vx;
	//	//vx = vx;
	//}
	
	if ((state == KOOPA_STATE_WALKING) && (start_x - x) > KOOPA_DISTANCE_MAX) {
		SetState(KOOPA_STATE_TURNING_AROUND);
	}

	if (state == KOOPA_STATE_TURNING_AROUND) {
		if (abs(start_x - x) > (KOOPA_DISTANCE_MAX + 24)) {
			SetState(KOOPA_STATE_TURNING_AROUND);
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	//Type of animation
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_DIE;
	}
	if (vx>0)
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	if (state == KOOPA_STATE_CLOSE)
	{
		aniId = ID_ANI_KOOPA_CLOSE;
	}
	/*if (type_koopa == KOOPA_TYPE)
	{
		aniId = 
	}*/
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	switch (state)
	{
	case KOOPA_STATE_TURNING_AROUND:
		start_x = x;
		vx = -vx;
		break;
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_CLOSE:
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_CLOSE) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_OPEN:
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	default:
		//SetState(KOOPA_STATE_OPEN);
		break; 
	}
	CGameObject::SetState(state);

}
