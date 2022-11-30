#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"


//PROPERTY



//STATE



//BBOX
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24



class CMarioWorld : public CGameObject
{
public:
	CMarioWorld(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	/*int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}*/

	//int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};