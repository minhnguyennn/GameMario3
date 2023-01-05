#include "Effect.h"
#include "debug.h"

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (GetTickCount64() - time_line > EFFECT_SMOKE_TIMEOUT)
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int AniId = 0;
	if (type == EFFECT_TYPE_SMOKE)
		AniId = ID_ANI_EFFECT_SMOKE;
	animations->Get(AniId)->Render(x, y);
	//RenderBoundingBox();
}