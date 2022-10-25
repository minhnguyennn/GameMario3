#pragma once

#include "GameObject.h"

#define ID_ANI_FIREBALLS 12010

#define FIREBALLS_BBOX_WIDTH 8
#define FIREBALLS_BBOX_HEIGHT 8

#define FIREBALLS_STATE_IDLE 0
#define FIREBALLS_STATE_UP 1
#define FIREBALLS_STATE_DELETE 2
#define FIREBALLS_STATE_DOWN 3

#define FIREBALLS_DISTANCE_UP 40
#define FIREBALLS_DISTANCE_DOWN 20

#define FIREBALLS_DISTANCE_MAX_UP 15
#define FIREBALLS_DISTANCE_MAX_DOWN 15
#define FIREBALLS_MOVING_SPEED 0.02f
#define FIREBALLS_GRAVITY 0.00001f
#define FIREBALLS_ACCEL_X	0.00001f


class CFireBalls : public CGameObject {
	float ax;
	float ay;
	float start_x;
	ULONGLONG time_line;
	bool check_delete_bullet = 0;
public:
	CFireBalls(float x, float y);
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};
