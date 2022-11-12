#pragma once
#include "GameObject.h"

//PROPERTY
#define PARA_GOOMBA_GRAVITY 0.0001f
#define PARA_GOOMBA_WALKING_SPEED 0.05f
#define PARA_GOOMBA_FLY_SPEED 0.06f
#define PARA_GOOMBA_MAX_FLY_SPEED 0.09f
#define PARA_GOOMBA_DIE_TIMEOUT 500

//BBOX
#define PARA_GOOMBA_BBOX_WIDTH 19
#define PARA_GOOMBA_BBOX_HEIGHT 23
#define PARA_GOOMBA_BBOX_HEIGHT_DIE 7

//STATE
#define PARA_GOOMBA_STATE_WALKING 100
#define PARA_GOOMBA_STATE_DIE 200

//ANIMATION
#define ID_ANI_PARA_GOOMBA_WALKING 5040
#define ID_ANI_PARA_GOOMBA_DIE 5041

class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	int count_number_jumps;
	ULONGLONG die_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);
};

