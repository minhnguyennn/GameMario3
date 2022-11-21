#pragma once

#include "GameObject.h"

//ANIMATION
#define ID_ANI_TAIL 14000

//BBOX
#define TAIL_BBOX_WIDTH 44
#define TAIL_BBOX_HEIGHT 3

#define FIREBALLS_STATE_MOVE_RIGHT 0
#define FIREBALLS_STATE_MOVE_LEFT 4
#define FIREBALLS_STATE_MOVE_RIGHT_TOP 5
#define FIREBALLS_STATE_MOVE_LEFT_TOP 6
#define FIREBALLS_STATE_UP 1
#define FIREBALLS_STATE_DELETE 2
#define FIREBALLS_STATE_DOWN 3

#define FIREBALLS_DISTANCE_UP 40
#define FIREBALLS_DISTANCE_DOWN 20

#define FIREBALLS_DISTANCE_MAX_UP 15
#define FIREBALLS_DISTANCE_MAX_DOWN 15
#define FIREBALLS_SPEED_Y 0.02f
#define FIREBALLS_SPEED_X 0.09f
#define FIREBALLS_GRAVITY 0.0001f


class CTail : public CGameObject {
	ULONGLONG time_line;

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
public:
	CTail(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void ChangePositionFollowMario();
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
};

