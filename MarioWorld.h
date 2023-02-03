#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"



//ANIMATION
#define ID_ANI_SMALL_MARIO_WORLD	7000
#define ID_ANI_BIG_MARIO_WORLD		7100
#define ID_ANI_FIRE_MARIO_WORLD		7200
#define ID_ANI_RACCON_MARIO_WORLD	7300

//STATE
#define	MARIO_WORLD_STATE_UP		1
#define	MARIO_WORLD_STATE_DOWN		2
#define	MARIO_WORLD_STATE_LEFT		3
#define	MARIO_WORLD_STATE_RIGHT		4
#define	MARIO_WORLD_STATE_IDLE		5
#define MARIO_WORLD_STATE_GO_PLAYSCENE 6

//BBOX
#define MARIO_WORLD_SMALL_BBOX_WIDTH  10
#define MARIO_WORLD_SMALL_BBOX_HEIGHT 10

//PROPERTY
#define MARIO_WORLD_SPEED 0.1f
#define MARIO_WORLD_ID_PLAY_SCENE 5


class CMarioWorld : public CGameObject
{
	bool isGoLeft;
	bool isGoRight;
	bool isGoTop;
	bool isGoBottom;
	bool isCollisionDoor;

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithDoor(LPCOLLISIONEVENT e);
public:
	CMarioWorld(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetIsGoRight(bool isGoRight) { this->isGoRight = isGoRight; }

	bool GetIsGoTop() { return isGoTop; }
	bool GetIsGoLeft() { return isGoLeft; }
	bool GetIsGoRight() { return isGoRight; }
	bool GetIsGoBottom() { return isGoBottom; }
	void CheckTypeDoor(int type_door);

	void SetIsCollisionDoor(bool isCollisionDoor) { this->isCollisionDoor = isCollisionDoor; }
	bool GetIsCollisionDoor() { return isCollisionDoor; }
};