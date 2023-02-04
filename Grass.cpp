#include "Grass.h"

void CGrass::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGrass::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GRASS)->Render(x, y);
	//RenderBoundingBox();
}