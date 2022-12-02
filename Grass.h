#pragma once
#include"GameObject.h"
//ANIMATION
#define ID_ANI_GRASS		15000
//PROPERTY



//STATE



//BBOX
#define MARIO_WORLD_SMALL_BBOX_WIDTH  13
#define MARIO_WORLD_SMALL_BBOX_HEIGHT 15



class CGrass : public CGameObject
{
public:
	CGrass(float x, float y);
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