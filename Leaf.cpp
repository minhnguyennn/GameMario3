#include "Leaf.h"

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = LEAF_GRAVITY;
	start_position = x;
	SetState(LEAF_STATE_WALKING);
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
	float distance_x = x - start_position;
	vy += ay * dt;
	vx += ax * dt;

	if (vy > 0) {
		if (abs(vy) > MAX_VY) {
			vy = MAX_VY;
			if ((distance_x < DISTANCE_LEAF_MAX) && (vx > 0)) {
				vx = LEAF_WALKING_SPEED;
			}
			else {
				//DebugOutTitle(L"OK")
				vx = -LEAF_WALKING_SPEED;
				if ((distance_x < -DISTANCE_LEAF_MAX) && (vx < 0)) { vx = LEAF_WALKING_SPEED; }
			}
		}
	}
	//DebugOut(L"[VX vy cua la cay] %f %f\n", vx,vy);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::Render()
{
	int aniId = ID_ANI_LEAF_WALKING;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		CGameObject::SetState(state);
		switch (state)
		{
		case  LEAF_STATE_WALKING:
			vx = -LEAF_WALKING_SPEED;
			break;
		default:
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
