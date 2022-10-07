#pragma once

#include "GameObject.h"

#define ID_ANI_MUSHROOM_RED 10200
#define ID_ANI_MUSHROOM_GREEN 10201

#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT_DIE 7

#define MUSHROOM_GRAVITY 0.0006f
#define MUSHROOM_UP_SPEED 0.04f
#define MUSHROOM_WALKING_SPEED 0.05f
#define DISTANCE_MAX 17

#define MUSHROOM_DIE_TIMEOUT 500

#define MUSHROOM_STATE_UP 1
#define MUSHROOM_STATE_WALKING 2

class CMushRoom : public CGameObject
{
protected:
	float ax;
	float ay;
	float start_y;
	ULONGLONG die_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CMushRoom(float x, float y);
	virtual void SetState(int state);
};

