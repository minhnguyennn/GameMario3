#pragma once
#include "GameObject.h"
#include "debug.h"

#define KOOPA_GRAVITY 0.0002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_WALKING_ATTACKING_SPEED (KOOPA_WALKING_SPEED * 3)
#define KOOPA_CLOSE_SHELL_TIMEOUT 3000

#define KOOPA_BBOX_WIDTH 17
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_WAITING 16

#define KOOPA_UP_DISTANCE_MOVE 21
#define KOOPA_UP_DISTANCE  16
#define KOOPA_JUMP_DEFLECT_SPEED 0.02f
#define KOOPA_WIDTH_OF_BOX  16
#define KOOPA_REMAINDER_OF_DISTANCE 8

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_WAITING 200
#define KOOPA_STATE_TURNING_AROUND 500
#define KOOPA_STATE_CLOSE_SHELL 700
#define KOOPA_STATE_RETURN_WALKING 800
#define KOOPA_STATE_ATTACKING 900
#define KOOPA_STATE_TURN_OVER 300
#define KOOPA_STATE_DIE_TURN_OVER 320
#define KOOPA_STATE_DIE 400

#define ID_ANI_KOOPA_WALKING_LEFT 5010
#define ID_ANI_KOOPA_WALKING_RIGHT 5011
#define ID_ANI_KOOPA_WAITING 5012
#define ID_ANI_KOOPA_CLOSE_SHELL 5013
#define ID_ANI_KOOPA_ATTACKING 5014
#define ID_ANI_KOOPA_TURN_OVER 5015

#define KOOPA_TYPE 0
#define KOOPA_TYPE_PARATROOPA 1

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	float start_x;
	int type_koopa;

	bool isDefense;
	bool isTurnOver;
	bool isWaiting;
	bool isAttacking;
	bool isDie;
	bool isSummon;
	bool isHeld;
	

	ULONGLONG close_start;
	ULONGLONG waiting_start;
	ULONGLONG die_start;
	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithDifferentKoopa(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y) : CGameObject(x , y)
	{
		this->ay = KOOPA_GRAVITY;
		this->start_x = x;
		isDie = false;
		isDefense = false;
		isTurnOver = false;
		isWaiting = false;
		isAttacking = false;
		isSummon = false;
		isHeld = false;
		close_start = -1;
		waiting_start = -1;
		SetState(KOOPA_STATE_WALKING);
	};
	void SetState(int state);
	

	void SetIsSummon(bool isSummon) { this->isSummon = isSummon; };
	bool GetIsDefense() { return isDefense; };

	void SetIsHeld(bool isHeld) { this->isHeld = isHeld; };
	bool GetIsHeld() { return isHeld; };


	bool GetIsTurnOver () { return isTurnOver; };
	bool GetIsWaiting() { return isWaiting; };
	bool GetIsAttacking (){ return isAttacking; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	int isLeftWithMario();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void ChangePositionFollowMario();
};
