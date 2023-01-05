#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//ANIMATION
#define ID_ANI_100_SCORE 15000
#define ID_ANI_1000_SCORE 15001

//BBOX
#define	POINT_WIDTH 10
#define POINT_BBOX_WIDTH 10
#define POINT_BBOX_HEIGHT 7

//STATE
#define POINT_STATE_IDLE 0
#define POINT_STATE_MOVE_UP 1
#define POINT_STATE_MOVE_DOWN 2
#define POINT_STATE_ADD_100 3

//TYPE
#define POINT_TYPE_100 100
#define POINT_TYPE_1000 1000

//PROPERTY
#define POINT_MOVE_SPEED 0.07f

//TIME
#define POINT_FLY_TIMEOUT 500

class CPoint : public CGameObject {
	float start_y;
	int type_point;
	ULONGLONG time_score_fly;
public:
	CPoint(float x, float y, int type_point) : CGameObject(x, y) {
		time_score_fly = 0;
		start_y = y;
		this->type_point = type_point;
	}
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};