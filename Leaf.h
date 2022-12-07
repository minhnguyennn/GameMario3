#pragma once
#include "GameObject.h"
#include "debug.h"

//PROPERTY
#define LEAF_GRAVITY 0.00005f
#define LEAF_SPEED_Y 0.05f
#define LEAF_SPEED_X 0.05f

//STATE
#define LEAF_STATE_FLY_LOW 100
#define LEAF_STATE_CHANGE 200
#define LEAF_STATE_FLY_UP 300

//TIME
#define LEAF_TIME_CHANGE 500
#define LEAF_TIME_FLY_LOW LEAF_TIME_CHANGE * 2

//ANIMATION
#define ID_ANI_LEAF_LEFT 12000
#define ID_ANI_LEAF_RIGHT 12100

//BBOX
#define LEAF_BBOX_HEIGHT 14
#define LEAF_BBOX_WIDTH 16

class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	bool isUp;
	bool isChange;
	bool isFlyLow;
	ULONGLONG time_line;
public:
	CLeaf(float x, float y);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	bool CountDownTimer(int time);
};

