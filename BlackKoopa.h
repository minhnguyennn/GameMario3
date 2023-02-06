#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Koopa.h"

#define BLACK_KOOPA_STATE_UP_UP			1
#define BLACK_KOOPA_AUTO_GRAVITY		0.002f

class CBlackKoopa : public CGameObject
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
	bool isWalking;
	bool isHeld;
	bool isGhostBox;
	bool isCollisionTail;

	ULONGLONG die_start;
	ULONGLONG time_line;
	ULONGLONG time_waiting;
	ULONGLONG time_turn_over;
	ULONGLONG time_defense;
	ULONGLONG time_collision_tail;

	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithDifferentKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
public:
	CBlackKoopa(float x, float y, int level, int type) : CGameObject(x, y)
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
		isHeld = false;
		isGhostBox = false;
		isWalking = false;
		isCollisionTail = false;

		SetState(KOOPA_STATE_CLOSE_SHELL);

		time_waiting = 0;
		time_turn_over = 0;
		time_defense = 0;
		time_collision_tail = 0;
	};

	void SetIsCollisionTail(bool isCollisionTail)
	{
		this->isCollisionTail = isCollisionTail;
		time_collision_tail = GetTickCount64();
	};
	bool GetIsCollisionTail() { return isCollisionTail; };

	void SetAy(float ay) { this->ay = ay; };
	void SetAx(float ax) { this->ax = ax; };

	void SetState(int state);

	bool GetIsDefense() { return isDefense; }

	bool GetIsWalking() { return isWalking; }

	void SetIsAttacking(bool isAttacking) { this->isAttacking = isAttacking; };

	void SetIsHeld(bool isHeld) { this->isHeld = isHeld; };
	bool GetIsHeld() { return isHeld; };

	bool GetIsTurnOver() { return isTurnOver; };

	bool GetIsWaiting() { return isWaiting; };

	bool GetIsAttacking() { return isAttacking; };

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

