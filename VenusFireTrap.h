#pragma once
#include "GameObject.h"

#define VFTRAP_BBOX_WIDTH 15
#define VFTRAP_BBOX_HEIGHT 32
#define VFTRAP_BBOX_HEIGHT_DIE 7

#define ID_ANI_VFTRAP_MOVING_LEFT 5020
#define ID_ANI_VFTRAP_MOVING_RIGHT 5021
#define ID_ANI_VFTRAP_MOVING_UP_LEFT 5022
#define ID_ANI_VFTRAP_MOVING_UP_RIGHT 5023

#define ID_ANI_VFTRAP 10200
#define ID_ANI_VFTRAP_GREEN 10200
#define ID_ANI_VFTRAP_RED 10201

#define VFTRAP_GRAVITY 0.00001f
#define VFTRAP_MOVING_SPEED 0.02f
#define VFTRAP_DISTANCE_MAX_UP 31
#define VFTRAP_DISTANCE_MAX_DOWN 13
#define	VFTRAP_WAITING_MAX	1000

#define VFTRAP_STATE_IDLE 0
#define VFTRAP_STATE_UP 1
#define VFTRAP_STATE_DOWN 2


#define VFTRAP_TYPE_FIRE_BALL 1
#define VFTRAP_TYPE_POINT 2

class CVenusFireTrap : public CGameObject
{
protected:
	float ax;
	float ay;
	float start_y;
	ULONGLONG time_line;
public:
	CVenusFireTrap(float x, float y);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void ChangeStateMotionDown();
	void ChangeStateMotionUp();
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void SetSummonItems(int type);
};


