#pragma once
#include "GameObject.h"

//PROPERTY
#define GOOMBA_GRAVITY 0.0001f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_DIE_TIMEOUT 500
#define PARA_GOOMBA_FLY_SPEED 0.06f
#define PARA_GOOMBA_MAX_FLY_SPEED 0.09f

//BBOX
#define PARA_GOOMBA_BBOX_WIDTH 19
#define PARA_GOOMBA_BBOX_HEIGHT 23
#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

//STATE
#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

//ANIMATION
#define ID_ANI_PARA_GOOMBA_WALKING 5040
#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

//LEVEL
#define	PARA_GOOMBA_LEVEL_BIG 1
#define	PARA_GOOMBA_LEVEL_SMALL 2

class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	int count_number_jumps;
	int level;
	ULONGLONG die_start;

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CParaGoomba(float x, float y, int level);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void LowerLevel();
	void SetLevel(int l);
};

