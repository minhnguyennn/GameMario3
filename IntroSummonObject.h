#pragma once
#include"GameObject.h"
//STATE
#define INTRO_SUMMON_STATE_MARIO 1

//position
#define INTRO_NUMBER_120			120
#define INTRO_NUMBER_56			56
#define INTRO_NUMBER_26			26

class CIntroSummonObject : public CGameObject
{
	bool isMarioJump;
	ULONGLONG time_curtain_up;
	ULONGLONG time_mario_jump;
public:
	CIntroSummonObject(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void SetState(int state);
	void SummonMario();
};