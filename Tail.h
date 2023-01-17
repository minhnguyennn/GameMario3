#pragma once

#include "GameObject.h"

//ANIMATION
#define ID_ANI_TAIL			14000

//BBOX
#define TAIL_BBOX_WIDTH		20
#define TAIL_BBOX_HEIGHT	5

//STATE
#define TAIL_STATE_RIGHT	1
#define TAIL_STATE_LEFT		2

//TIME
#define TAIL_TIMEOUT	100

//PROPRERTY
#define TAIL_SUMMON_EFFECT_X_ADJUST	10

class CTail : public CGameObject 
{
	ULONGLONG time_line;
	bool collision_one_number;

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
public:
	CTail(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	void SetState(int state);
	void SummonEffect();
};

