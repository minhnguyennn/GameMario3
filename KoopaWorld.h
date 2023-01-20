#pragma once
#include"GameObject.h"

//ANIMATION
#define ID_ANI_KOOPA_WORLD_LEFT		15100
#define ID_ANI_KOOPA_WORLD_RIGHT	15101

//PROPERTY
#define KOOPA_WORLD_WALKING_TIMEOUT	500
#define KOOPA_WORLD_SPEED	0.03f

class CKoopaWorld : public CGameObject
{
	ULONGLONG time_line;
public:
	CKoopaWorld(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};