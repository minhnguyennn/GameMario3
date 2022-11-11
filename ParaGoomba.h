#pragma once
#include "GameObject.h"

//PROPERTY
#define GOOMBA_GRAVITY 0.0001f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_FLY_SPEED 0.09f
#define GOOMBA_DIE_TIMEOUT 500

//BBOX
#define GOOMBA_BBOX_WIDTH 19
#define GOOMBA_BBOX_HEIGHT 23
#define GOOMBA_BBOX_HEIGHT_DIE 7

//STATE
#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

//ANIMATION
#define ID_ANI_GOOMBA_WALKING 5040
#define ID_ANI_GOOMBA_DIE 5041

class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG die_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);
};

