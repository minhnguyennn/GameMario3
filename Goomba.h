#pragma once
#include "GameObject.h"

//PROPERTY
#define GOOMBA_GRAVITY 0.0003f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_FLY_SPEED 0.06f
#define GOOMBA_MAX_FLY_SPEED 0.15f
#define GOOMBA_COUNT_JUMP 3
#define GOOMBA_BIG_Y_ADJUST 3
#define GOOMBA_DIE_VX 0.05f
#define GOOMBA_DIE_VY 0.05f

//TIME
#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_CLOSE_WING_TIMEOUT 1000

//BBOX
#define GOOMBA_BBOX_WIDTH 15
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_DIE 7

//STATE
#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_FLY 300
#define GOOMBA_STATE_CLOSE_WING 400
#define GOOMBA_STATE_FLY_MAX 500
#define GOOMBA_STATE_DIE_TURN_OVER 600
#define GOOMBA_STATE_Fall 700

//ANIMATION
///////////// BROWN ///////////////////
#define ID_ANI_GOOMBA_BROWN_LEVEL_BIG		5040
#define ID_ANI_GOOMBA_BROWN_LEVEL_SMALL		5041
#define ID_ANI_GOOMBA_BROWN_CLOSE_WING		5042
#define ID_ANI_GOOMBA_BROWN_DIE				5043
#define ID_ANI_GOOMBA_BROWN_TURN_OVER		5044
////////////// RED /////////////////
#define ID_ANI_GOOMBA_RED_LEVEL_BIG			5045
#define ID_ANI_GOOMBA_RED_LEVEL_SMALL		5046
#define ID_ANI_GOOMBA_RED_CLOSE_WING		5047
#define ID_ANI_GOOMBA_RED_DIE				5048
#define ID_ANI_GOOMBA_RED_TURN_OVER			5049

//LEVEL
#define	GOOMBA_LEVEL_SMALL 1
#define	GOOMBA_LEVEL_BIG 2

//TYPE
#define GOOMBA_TYPE_BROWN 1	
#define GOOMBA_TYPE_RED 2

class CGoomba : public CGameObject
{
protected:
	float ay;
	int count_number_jumps;
	int level;
	bool isCloseWing;
	bool isTurnOver;
	bool isDie;
	bool isWalk;
	int type;
	ULONGLONG time_line;
	ULONGLONG time_close;

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CGoomba(float x, float y, int type, int level);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void LowerLevel();
};

