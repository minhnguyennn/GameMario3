#pragma once
#include"GameObject.h"

//animation
#define ID_ANI_CURTAIN		100105

//state
#define CURTAIN_STATE_UP	1

//property
#define CURTAIN_VY			0.1f
#define TIME_CURTAIN_UP		2000


class CCurTain : public CGameObject
{
	ULONGLONG time_curtain_up;
public:
	CCurTain(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void SetState(int state);
};