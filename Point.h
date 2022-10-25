#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_100_POINT 13000

#define	POINT_WIDTH 10
#define POINT_BBOX_WIDTH 10
#define POINT_BBOX_HEIGHT 7

#define POINT_STATE_IDLE 0
#define POINT_STATE_MOVE_UP 1
#define POINT_STATE_MOVE_DOWN 2
#define POINT_STATE_ADD_100 3

#define POINT_TYPE_100 100
#define POINT_MOVE_SPEED 0.07f


class CPoint : public CGameObject {
	float start_y;
	int type_point;
	int number_point = 0;
public:
	CPoint(float x, float y, int type_point) : CGameObject(x, y) {
		SetState(POINT_STATE_IDLE);
		start_y = y;
		this->type_point = type_point;
	}
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; };
	void AdditionPoint();
};
