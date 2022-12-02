#pragma once
#include "GameObject.h"

//ANIMATION
#define ID_ANI_FIREBALL_OF_MARIO 13000

//BBOX
#define FIREBALLS_BBOX_WIDTH 8
#define FIREBALLS_BBOX_HEIGHT 8

//STATE
#define FIREBALLS_STATE_SHOOT 1
#define FIREBALLS_STATE_DELETE 2
//#define FIREBALLS_STATE_DOWN 3
#define FIREBALLS_STATE_RIGHT 0
#define FIREBALLS_STATE_LEFT 4

//PROPERTY
//#define FIREBALLS_DISTANCE_UP 40
//#define FIREBALLS_DISTANCE_DOWN 20
//#define FIREBALLS_DISTANCE_MAX_UP 15
//#define FIREBALLS_DISTANCE_MAX_DOWN 15

#define FIREBALLS_MARIO_SPEED_Y 0.2f
#define FIREBALLS_MARIO_SPEED_X 0.15f
#define FIREBALLS_MARIO_GRAVITY 0.0006f


class CFireBallOfMario : public CGameObject {
	float ax;
	float ay;
	float start_x;
	ULONGLONG time_line;
	bool check_delete_bullet = 0;
public:
	CFireBallOfMario(float x, float y);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
};

