#pragma once
#include"GameObject.h"

//animation
#define ID_ANI_CURTAIN		100105
#define ID_ANI_LOGO			100106

//state
#define LOGO_STATE_DOWN	1

//property
#define CURTAIN_VY					0.1f
#define TIME_CURTAIN_UP				2000

//RANDOM
#define CURTAIN_SUM_RANDOM			2
#define CURTAIN_NUMBER_RANDOM_0		0
#define CURTAIN_NUMBER_RANDOM_1		1

//TIME
#define CURTAIN_TIME_1800	1800
#define CURTAIN_TIME_1000	1000
#define CURTAIN_ADJUST_Y	2

class CCurTain : public CGameObject
{
	bool isLogo;
	bool isCurTain;
	bool isVibrate;
	bool isStop;

	int random;

	ULONGLONG time_curtain_up;
	ULONGLONG time_logo_down;
	ULONGLONG time_vibrate;
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
	void SetupRandom();
};