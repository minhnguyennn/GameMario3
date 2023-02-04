#include "GoshBox.h"

void CGoshBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGoshBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GOSH_BOX)->Render(x, y);
	//RenderBoundingBox();
}

void CGoshBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GOSH_BOX_BBOX_WIDTH / 2;
	t = y - GOSH_BOX_BBOX_HEIGHT / 2;
	r = l + GOSH_BOX_BBOX_WIDTH;
	b = t + GOSH_BOX_BBOX_HEIGHT;
}