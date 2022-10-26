#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.0002f
#define KOOPA_WALKING_SPEED 0.05f

#define KOOPA_BBOX_WIDTH 17
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DIE 7
#define KOOPA_BBOX_HEIGHT_CLOSE 16
#define KOOPA_DISTANCE_WITH_PLANTFORM 21
#define KOOPA_DISTANCE_MAX 64

#define KOOPA_DIE_TIMEOUT 500
#define KOOPA_STATE_WALKING 100

#define KOOPA_STATE_DIE 200
#define KOOPA_STATE_CLOSE 400
#define KOOPA_STATE_OPEN 600
#define KOOPA_STATE_TURNING_AROUND 500

#define ID_ANI_KOOPA_WALKING_LEFT 5010
#define ID_ANI_KOOPA_WALKING_RIGHT 5012
#define ID_ANI_KOOPA_DIE 5011
#define ID_ANI_KOOPA_CLOSE 5013
#define ID_ANI_KOOPA_OPEN 5014

#define KOOPA_TYPE 0
#define KOOPA_TYPE_PARATROOPA 1

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int type_koopa;
	bool isDefense;
	bool isUpside;
	bool isHolding;
	float start_x;
	ULONGLONG die_start;

	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y) : CGameObject(x , y)
	{
		this->ay = KOOPA_GRAVITY;
		this->start_x = x;
		isDefense = false;
		isUpside = false;
		die_start = -1;
		SetState(KOOPA_STATE_WALKING);
	};
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};
