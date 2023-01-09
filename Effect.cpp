#include "Effect.h"
#include "debug.h"

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (type == EFFECT_TYPE_SMOKE && GetTickCount64() - time_line > EFFECT_SMOKE_TIMEOUT)
	{
		isDeleted = true;
		time_line = 0;
		return;
	}
	else if (type == EFFECT_TYPE_STAR && GetTickCount64() - time_line > EFFECT_STAR_TIMEOUT)
	{
		isDeleted = true;
		time_line = 0;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int AniId = 0;
	if (type == EFFECT_TYPE_SMOKE) AniId = ID_ANI_EFFECT_SMOKE;
	else if (type == EFFECT_TYPE_STAR) AniId = ID_ANI_EFFECT_STAR;
	animations->Get(AniId)->Render(x, y);
	//RenderBoundingBox();
}