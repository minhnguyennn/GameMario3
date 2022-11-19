#pragma once
#include "GameObject.h"

//PROPERTY
#define GOOMBA_GRAVITY 0.0003f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_FLY_SPEED 0.06f
#define GOOMBA_MAX_FLY_SPEED 0.09f

//TIME
#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_CLOSE_WING_TIMEOUT 1000

//BBOX
#define GOOMBA_BBOX_CLOSE_WING_HEIGHT 16
#define GOOMBA_BIG_BBOX_WIDTH 19
#define GOOMBA_BIG_BBOX_HEIGHT 22
#define GOOMBA_SMALL_BBOX_WIDTH 16
#define GOOMBA_SMALL_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

//STATE
#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_FLY 300
#define GOOMBA_STATE_CLOSE_WING 400
#define GOOMBA_STATE_FLY_MAX 500

//ANIMATION
#define ID_ANI_GOOMBA_BIG			5040
#define ID_ANI_GOOMBA_SMALL			5042
#define ID_ANI_GOOMBA_CLOSE_WING	5041
#define ID_ANI_GOOMBA_DIE			5043

//LEVEL
#define	GOOMBA_LEVEL_BIG 1
#define	GOOMBA_LEVEL_SMALL 2

//TYPE
#define GOOMBA_TYPE_GOOMBA 1
#define GOOMBA_TYPE_PARA_GOOMBA 2

class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	int count_number_jumps;
	int level;
	bool isCloseWing;
	int type;
	ULONGLONG time_line;

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CGoomba(float x, float y, int level, int type);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void LowerLevel();
	void SetLevel(int l);
};

