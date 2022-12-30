#pragma once

#include "GameObject.h"

//ANIMATION
#define ID_ANI_FIREBALLS 12010

//BBOX
#define FIREBALLS_BBOX_WIDTH 8
#define FIREBALLS_BBOX_HEIGHT 8

//STATE
#define FIREBALLS_STATE_MOVE_RIGHT 0
#define FIREBALLS_STATE_MOVE_LEFT 4

#define FIREBALLS_STATE_MOVE_RIGHT_TOP 5
#define FIREBALLS_STATE_MOVE_LEFT_TOP 6

#define FIREBALLS_STATE_RIGHT_BOTTOM 1
#define FIREBALLS_STATE_LEFT_BOTTOM 3

#define FIREBALLS_STATE_DELETE 2

//DISTANCE
#define FIREBALLS_DISTANCE_UP 40
#define FIREBALLS_DISTANCE_DOWN 20
#define FIREBALLS_DISTANCE_MAX_UP 15
#define FIREBALLS_DISTANCE_MAX_DOWN 15

//PROPERTY
#define FIREBALLS_SPEED_Y 0.03f
#define FIREBALLS_SPEED_Y_RIGHT_AND_LEFT 0.01f
#define FIREBALLS_SPEED_X 0.05f
#define FIREBALLS_GRAVITY 0.1f


class CFireBalls : public CGameObject {
	float ax;
	float ay;
	float start_x;
	ULONGLONG time_line;
	bool check_delete_bullet = 0;
	bool isMario;
public:
	CFireBalls(float x, float y);
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

