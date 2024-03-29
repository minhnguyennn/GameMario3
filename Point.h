#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//ANIMATION
#define ID_ANI_100_SCORE	15001
#define ID_ANI_200_SCORE	15002
#define ID_ANI_400_SCORE	15003
#define ID_ANI_800_SCORE	15004
#define ID_ANI_1000_SCORE	15005
#define ID_ANI_2000_SCORE	15006
#define ID_ANI_4000_SCORE	15007
#define ID_ANI_8000_SCORE	15018
#define ID_ANI_1_UP			15009
#define ID_ANI_BIG_UP		15109

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
#define POINT_TYPE_100	100
#define POINT_TYPE_200	200
#define POINT_TYPE_400	400
#define POINT_TYPE_800	800
#define POINT_TYPE_1000 1000
#define POINT_TYPE_2000 2000
#define POINT_TYPE_4000 4000
#define POINT_TYPE_8000 8000
#define POINT_TYPE_UP	10
#define POINT_TYPE_BIG_UP	11

//NUMBER
#define POINT_NUMBER_10		10
#define POINT_NUMBER_100	100
#define POINT_NUMBER_200	200
#define POINT_NUMBER_400	400
#define POINT_NUMBER_800	800
#define POINT_NUMBER_1000	1000
#define POINT_NUMBER_2000	2000
#define POINT_NUMBER_4000	4000
#define POINT_NUMBER_8000	8000
#define POINT_NUMBER_1UP	1


//PROPERTY
#define POINT_MOVE_SPEED 0.07f

//TIME
#define POINT_FLY_TIMEOUT 500

class CPoint : public CGameObject {
	int type_point;
	ULONGLONG time_score_fly;
public:
	CPoint(float x, float y, int type_point) : CGameObject(x, y) {
		time_score_fly = 0;
		this->type_point = type_point;
	}
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
	void StorageScore();
};