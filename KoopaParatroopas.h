#pragma once
#include "GameObject.h"
#include "debug.h"

//PROPERTY OF Green Koopa Paratroopa
#define KOOPA_PARATROOPAS_GRAVITY 0.0002f
#define KOOPA_PARATROOPAS_WALKING_SPEED 0.05f
#define KOOPA_PARATROOPAS_ATTACKING_SPEED (KOOPA_PARATROOPAS_WALKING_SPEED * 3)
#define KOOPA_PARATROOPAS_CLOSE_SHELL_TIMEOUT 3000
#define KOOPA_PARATROOPAS_FLY_SPEED 0.09f
#define KOOPA_PARATROOPAS_DISTANCE_WHEN_ATTACKING 5

//BBOX OF Green Koopa Paratroopa
#define KOOPA_PARATROOPAS_BBOX_WIDTH 17
#define KOOPA_PARATROOPAS_BBOX_HEIGHT 26
#define KOOPA_PARATROOPAS_BBOX_WAITING 16

//DISTANCE OF Green Koopa Paratroopa
#define KOOPA_PARATROOPAS_UP_DISTANCE_MOVE 21
#define KOOPA_PARATROOPAS_UP_DISTANCE  16
#define KOOPA_PARATROOPAS_JUMP_DEFLECT_SPEED 0.02f
#define KOOPA_PARATROOPAS_WIDTH_OF_BOX  16
#define KOOPA_PARATROOPAS_REMAINDER_OF_DISTANCE 8

//STATE OF Green Koopa Paratroopa
#define KOOPA_PARATROOPAS_STATE_WALKING 100
#define KOOPA_PARATROOPAS_STATE_WAITING 200
#define KOOPA_PARATROOPAS_STATE_TURNING_AROUND 500
#define KOOPA_PARATROOPAS_STATE_CLOSE_SHELL 700
#define KOOPA_PARATROOPAS_STATE_RETURN_WALKING 800
#define KOOPA_PARATROOPAS_STATE_ATTACKING 900
#define KOOPA_PARATROOPAS_STATE_TURN_OVER 300
#define KOOPA_PARATROOPAS_STATE_DIE_TURN_OVER 320
#define KOOPA_PARATROOPAS_STATE_DIE 400

//ANIMATION OF Green Koopa Paratroopa
#define ID_ANI_KOOPA_PARATROOPAS_WALKING_LEFT 5030
#define ID_ANI_KOOPA_PARATROOPAS_WALKING_RIGHT 5031
#define ID_ANI_KOOPA_PARATROOPAS_WAITING 5032
#define ID_ANI_KOOPA_PARATROOPAS_CLOSE_SHELL 5033
#define ID_ANI_KOOPA_PARATROOPAS_ATTACKING 5034
#define ID_ANI_KOOPA_PARATROOPAS_TURN_OVER 5035

#define KOOPA_PARATROOPAS_TYPE_GREEN 0
#define KOOPA_PARATROOPAS_TYPE_RED 1

class CKoopaParatroopas : public CGameObject
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
	bool isHeld;

	ULONGLONG close_start;
	ULONGLONG waiting_start;
	ULONGLONG die_start;
	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithDifferentKoopaParatroopas(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
public:
	CKoopaParatroopas(float x, float y) : CGameObject(x, y)
	{
		ay = KOOPA_PARATROOPAS_GRAVITY;
		start_x = x;
		isDie = false;
		isDefense = false;
		isTurnOver = false;
		isWaiting = false;
		isAttacking = false;
		isHeld = false;
		close_start = -1;
		waiting_start = -1;
		SetState(KOOPA_PARATROOPAS_STATE_WALKING);
	};
	void SetState(int state);

	
	bool GetIsDefense() { return isDefense; };

	void SetIsHeld(bool isHeld) { this->isHeld = isHeld; };
	bool GetIsHeld() { return isHeld; };

	bool GetIsTurnOver() { return isTurnOver; };
	bool GetIsWaiting() { return isWaiting; };
	bool GetIsAttacking() { return isAttacking; };
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
