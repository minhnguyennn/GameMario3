#pragma once
#include "GameObject.h"

//BBOX
#define VFTRAP_BBOX_RED_WIDTH 15
#define VFTRAP_BBOX_RED_HEIGHT 32

#define VFTRAP_BBOX_GREEN_WIDTH 17
#define VFTRAP_BBOX_GREEN_HEIGHT 25

#define VFTRAP_BBOX_PIRANHA_WIDTH 15
#define VFTRAP_BBOX_PIRANHA_HEIGHT 25

//ANIMATION

//red
#define ID_ANI_VFTRAP_RED_TOP_LEFT_ATTACK 5031
#define ID_ANI_VFTRAP_RED_BOTTOM_LEFT_ATTACK 5032
#define ID_ANI_VFTRAP_RED_TOP_RIGHT_ATTACK 5033
#define ID_ANI_VFTRAP_RED_BOTTOM_RIGHT_ATTACK 5034
#define ID_ANI_VFTRAP_RED_TOP_LEFT 5020
#define ID_ANI_VFTRAP_RED_BOTTOM_LEFT 5021
#define ID_ANI_VFTRAP_RED_TOP_RIGHT 5022
#define ID_ANI_VFTRAP_RED_BOTTOM_RIGHT 5027
#define ID_ANI_VFTRAP_RED_DIE 5029

//green
#define ID_ANI_VFTRAP_GREEN_TOP_LEFT 5023
#define ID_ANI_VFTRAP_GREEN_BOTTOM_LEFT 5026

#define ID_ANI_VFTRAP_GREEN_TOP_RIGHT 5024
#define ID_ANI_VFTRAP_GREEN_BOTTOM_RIGHT 5025

#define ID_ANI_VFTRAP_GREEN_DIE 5130

//piranha
#define ID_ANI_PIRANHA_PLANT 5028

//PROPERTY
#define VFTRAP_GRAVITY 0.00001f
#define VFTRAP_MOVING_SPEED 0.02f

//TIME
#define	VFTRAP_WAITING_MAX		1000
#define	VFTRAP_WAITING_PIRAN	1490
#define VFTRAP_DIE_TIMEOUT		500

//DISTANCE
#define VFTRAP_DIS_UP_RED		31
#define VFTRAP_DIS_DOWN_RED		11

#define VFTRAP_DIS_UP_GREEN		34
#define VFTRAP_DIS_DOWN_GREEN	10

#define VFTRAP_DIST_UP_PIRA		26
#define VFTRAP_DIST_DOWN_PIRA	1

#define VFTRAP_DIST_FIREBALL	80
#define VFTRAP_DIST_MARIO		30

//STATE
#define VFTRAP_STATE_IDLE 0
#define VFTRAP_STATE_UP 1
#define VFTRAP_STATE_DOWN 2
#define VFTRAP_STATE_DIE 3

//TYPE OTHER
#define VFTRAP_TYPE_FIRE_BALL 1
#define VFTRAP_TYPE_POINT 2

//TYPE PLANT
#define VFTRAP_TYPE_GREEN 3
#define VFTRAP_TYPE_RED 4
#define VFTRAP_TYPE_PIRANHA 5


class CVenusFireTrap : public CGameObject
{
protected:
	float start_y;
	int type;
	ULONGLONG time_line;
	bool isIdle;
public:
	CVenusFireTrap(float x, float y, int type);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void ChangeStateMotionDown(ULONGLONG time_type);
	void ChangeStateMotionUp(ULONGLONG time_type);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void SetSummonItems(int type);
	bool isMarioLeftWithPlant();
	bool isMarioAboveWithPlant();
	void MoveFunctionPlant(float disUp, float disDown);
	bool CountDownTimer(ULONGLONG time);
	void SummonScore();
};