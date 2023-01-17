#pragma once
#include "GameObject.h"
#include "Data.h"

//ANIMATION
#define ID_ANI_EFFECT_SMOKE 14001
#define ID_ANI_EFFECT_STAR 14002

//TIME
#define EFFECT_SMOKE_TIMEOUT 500
#define EFFECT_STAR_TIMEOUT 200

//TYPE EFFECTS
#define EFFECT_TYPE_SMOKE 1
#define EFFECT_TYPE_STAR 2

class CEffect : public CGameObject 
{
	int type;
	ULONGLONG time_line;
public:
	CEffect(float x, float y, int type) : CGameObject(x, y)
	{
		time_line = GetTickCount64();
		this->type = type;
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; };
	void OnNoCollision(DWORD dt) {};
	ULONGLONG GetTimeSMOKE() { return time_line; }
};

