#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_IDLE 0
#define COIN_STATE_MOVE_UP 1
#define COIN_STATE_DELETE 2
#define COIN_STATE_MOVE_DOWN 3

class CCoin : public CGameObject {
	float start_y;
	int type_coin;

	int c;
	float coppy_x;
	float coppy_y;
	bool check_delete_coin = 0;
public:
	CCoin(float x, float y, int type_coin) : CGameObject(x, y) {
		SetState(COIN_STATE_IDLE);
		start_y = y;
		this->type_coin = type_coin;
	}
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SummonAndMovePoint();
	void SetCoppyPosition(float coppy_x, float coppy_y) { this->coppy_x = coppy_x, this->coppy_y = coppy_y; }
};