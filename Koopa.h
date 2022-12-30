#pragma once
#include "GameObject.h"
#include "debug.h"

//PROPERTY
#define KOOPA_GRAVITY 0.0002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_WALKING_ATTACKING_SPEED (KOOPA_WALKING_SPEED * 3)
#define KOOPA_FLY_SPEED 0.1f
#define KOOPA_JUMP_DEFLECT_SPEED 0.02f
#define KOOPA_TURN_UP_JUMP_VX 0.05f
#define KOOPA_TURN_UP_JUMP_VY 0.05f
#define KOOPA_Y_ADJUST 1

//TIME
#define KOOPA_CLOSE_SHELL_TIMEOUT 30000

//BBOX
#define KOOPA_BBOX_WIDTH 17
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_WAITING 16

//DISTANCE
#define KOOPA_UP_DISTANCE_MOVE 21
#define KOOPA_UP_DISTANCE  16
#define KOOPA_WIDTH_OF_BOX  16
#define KOOPA_REMAINDER_OF_DISTANCE 8
#define KOOPA_DISTANCE_WHEN_ATTACKING 5

//STATE
#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_WAITING 200
#define KOOPA_STATE_TURNING_AROUND 500
#define KOOPA_STATE_CLOSE_SHELL 700
#define KOOPA_STATE_RETURN_WALKING 800
#define KOOPA_STATE_ATTACKING 900
#define KOOPA_STATE_TURN_OVER 300
#define KOOPA_STATE_DIE_TURN_OVER 320
#define KOOPA_STATE_DIE 400
#define KOOPA_STATE_FLY 401

//ANIMATION
//////////////////////// RED //////////////////////
#define ID_ANI_KOOPA_RED_SMALL_WALKING_LEFT 6110
#define ID_ANI_KOOPA_RED_SMALL_WALKING_RIGHT 6011
#define ID_ANI_KOOPA_RED_BIG_WALKING_LEFT 6012
#define ID_ANI_KOOPA_RED_BIG_WALKING_RIGHT 6013
#define ID_ANI_KOOPA_RED_WAITING 6014
#define ID_ANI_KOOPA_RED_CLOSE_SHELL 6015
#define ID_ANI_KOOPA_RED_ATTACKING 6016
#define ID_ANI_KOOPA_RED_TURN_OVER 6017
#define	ID_ANI_KOOPA_RED_TURN_OVER_ATTACKING 6018

//////////////////////// GREEN //////////////////////
#define ID_ANI_KOOPA_GREEN_SMALL_WALKING_LEFT 6050
#define ID_ANI_KOOPA_GREEN_SMALL_WALKING_RIGHT 6051
#define ID_ANI_KOOPA_GREEN_BIG_WALKING_LEFT 6052
#define ID_ANI_KOOPA_GREEN_BIG_WALKING_RIGHT 6053
#define ID_ANI_KOOPA_GREEN_WAITING 6054
#define ID_ANI_KOOPA_GREEN_CLOSE_SHELL 6055
#define ID_ANI_KOOPA_GREEN_ATTACKING 6056
#define ID_ANI_KOOPA_GREEN_TURN_OVER 6057
#define	ID_ANI_KOOPA_GREEN_TURN_OVER_ATTACKING 6058

//LEVEL
#define KOOPA_LEVEL_SMALL 1
#define KOOPA_LEVEL_BIG 2

//TYPE
#define KOOPA_TYPE_TROOPA 1
#define KOOPA_TYPE_PARATROOPA 2

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	float start_x;
	int type;
	int level;

	bool isDefense;
	bool isTurnOver;
	bool isWaiting;
	bool isAttacking;
	bool isDie;
	bool isSummon;
	bool isHeld; 
	bool isGhostBox;

	ULONGLONG die_start;
	ULONGLONG time_line;

	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithDifferentKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWitTail(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y, int level, int type) : CGameObject(x , y)
	{
		this->type = type;
		this->level = level;
		ay = KOOPA_GRAVITY;
		start_x = x;
		isDie = false;
		isDefense = false;
		isTurnOver = false;
		isWaiting = false;
		isAttacking = false;
		isSummon = false;
		isHeld = false;
		isGhostBox = false;
		SetState(KOOPA_STATE_WALKING);
	};

	void SetAy(float ay) { this->ay = ay; };
	void SetAx(float ax) { this->ax = ax; };

	void SetState(int state);
	void SetIsSummon(bool isSummon) { this->isSummon = isSummon; };

	bool GetIsDefense() { return isDefense; };

	void SetIsAttacking(bool isAttacking) { this->isAttacking = isAttacking; };

	void SetIsHeld(bool isHeld) { this->isHeld = isHeld; };
	bool GetIsHeld() { return isHeld; };

	bool GetIsTurnOver () { return isTurnOver; };

	bool GetIsWaiting() { return isWaiting; };

	bool GetIsAttacking (){ return isAttacking; };

	int GetLevel() { return level; };
	void SetLevel(int setLevel) { 
		if (setLevel == KOOPA_LEVEL_SMALL) {
			SetState(KOOPA_STATE_WALKING);
			this->level = setLevel;
		}
	};
	void LowerLevel();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	int isLeftWithMario();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	bool CountDownTimer(int time);
};
