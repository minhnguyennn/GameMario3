#pragma once
#include "GameObject.h"

#define ID_ANI_PPLANT_MOVING_UP 5020
#define ID_ANI_PPLANT_MOVING_DOWN 5021

#define ID_ANI_PPLANT 10200
#define ID_ANI_PPLANT_GREEN 10200
#define ID_ANI_PPLANT_RED 10201

#define PPLANT_GRAVITY 0.00042f
#define PPLANT_MOVING_SPEED 0.1f

#define PPLANT_BBOX_WIDTH 17
#define PPLANT_BBOX_HEIGHT 26
#define PPLANT_BBOX_HEIGHT_DIE 7

#define PPLANT_STATE_IDLE 0
#define PPLANT_STATE_UP 400
#define PPLANT_STATE_DOWN 600

class CPiranhaPlant : public CGameObject
{
protected:
	float ax;
	float ay;
	int type_pplant;
	ULONGLONG die_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
public:
	CPiranhaPlant(float x, float y);
	virtual void SetState(int state);
};


