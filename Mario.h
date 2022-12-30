#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"
#include "Koopa.h"

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 401
#define ID_ANI_MARIO_IDLE_LEFT 400

#define ID_ANI_MARIO_WALKING_RIGHT 501
#define ID_ANI_MARIO_WALKING_LEFT 500

#define ID_ANI_MARIO_RUNNING_RIGHT 601
#define ID_ANI_MARIO_RUNNING_LEFT 600

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 701
#define ID_ANI_MARIO_JUMP_WALK_LEFT 700

#define ID_ANI_MARIO_FALL_RIGHT 4501
#define ID_ANI_MARIO_FALL_LEFT 4500

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 801
#define ID_ANI_MARIO_JUMP_RUN_LEFT 800

#define ID_ANI_MARIO_SIT_RIGHT 901
#define ID_ANI_MARIO_SIT_LEFT 900

#define ID_ANI_MARIO_BRACE_RIGHT 1001
#define ID_ANI_MARIO_BRACE_LEFT 1000

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_IDLE_HOLD_RIGHT 3301
#define ID_ANI_MARIO_IDLE_HOLD_LEFT 3300

#define ID_ANI_MARIO_HOLD_WALK_RIGHT 3401
#define ID_ANI_MARIO_HOLD_WALK_LEFT 3400

#define ID_ANI_MARIO_KICK_RIGHT 3901
#define ID_ANI_MARIO_KICK_LEFT 3900

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1101
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1100

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1201
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1200

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1301
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1300

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1401
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1400

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1501
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1500

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1601
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1600

#define ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT 3501
#define ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT 3500

#define ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT 3601
#define ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT 3600

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 4001
#define ID_ANI_MARIO_SMALL_KICK_LEFT 4000

//FIRE MARIO
#define ID_ANI_MARIO_FIRE_IDLE_RIGHT 1701
#define ID_ANI_MARIO_FIRE_IDLE_LEFT 1700

#define ID_ANI_MARIO_FIRE_WALKING_RIGHT 1801
#define ID_ANI_MARIO_FIRE_WALKING_LEFT 1800

#define ID_ANI_MARIO_FIRE_RUNNING_RIGHT 1901
#define ID_ANI_MARIO_FIRE_RUNNING_LEFT 1900

#define ID_ANI_MARIO_FIRE_JUMP_WALK_RIGHT 2001
#define ID_ANI_MARIO_FIRE_JUMP_WALK_LEFT 2000

#define ID_ANI_MARIO_FIRE_JUMP_RUN_RIGHT 2101
#define ID_ANI_MARIO_FIRE_JUMP_RUN_LEFT 2100

#define ID_ANI_MARIO_FIRE_SIT_RIGHT 2201
#define ID_ANI_MARIO_FIRE_SIT_LEFT 2200

#define ID_ANI_MARIO_FIRE_BRACE_RIGHT 2301
#define ID_ANI_MARIO_FIRE_BRACE_LEFT 2300

#define ID_ANI_MARIO_FIRE_IDLE_HOLD_RIGHT 3701
#define ID_ANI_MARIO_FIRE_IDLE_HOLD_LEFT 3700

#define ID_ANI_MARIO_FIRE_HOLD_WALK_RIGHT 3801
#define ID_ANI_MARIO_FIRE_HOLD_WALK_LEFT 3800

#define ID_ANI_MARIO_FIRE_KICK_RIGHT 4101
#define ID_ANI_MARIO_FIRE_KICK_LEFT 4100

#define ID_ANI_MARIO_FIRE_FALL_RIGHT 4601
#define ID_ANI_MARIO_FIRE_FALL_LEFT 4600

//RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 2401
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 2400

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 2501
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 2500

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 2601
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 2600

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2701
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2700

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 2801
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 2800

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2901
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2900

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 3001
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 3000

#define ID_ANI_MARIO_RACCOON_IDLE_HOLD_RIGHT 3201
#define ID_ANI_MARIO_RACCOON_IDLE_HOLD_LEFT 3200

#define ID_ANI_MARIO_RACCOON_FLYING_RIGHT 4301
#define ID_ANI_MARIO_RACCOON_FLYING_LEFT 4300

#define ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT 3101
#define ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT 3100

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 4201
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 4200

#define	ID_ANI_MARIO_RACCOON_ATTACK	4400

#define ID_ANI_MARIO_RACCOON_FALL_WALK_RIGHT 4701
#define ID_ANI_MARIO_RACCOON_FALL_WALK_LEFT 4700

#define ID_ANI_MARIO_RACCOON_FALL_RUN_RIGHT 4901
#define ID_ANI_MARIO_RACCOON_FALL_RUN_LEFT 4900

#define ID_ANI_MARIO_RACCOON_FALL_SLOWLY_RIGHT 4801
#define ID_ANI_MARIO_RACCOON_FALL_SLOWLY_LEFT 4800

#pragma endregion

//ANIMATION CHANGE LEVEL
#define ID_ANI_SMALL_TO_BIG_RIGHT		4802
#define ID_ANI_SMALL_TO_BIG_LEFT		4803

#define ID_ANI_SMALL_TO_SMALL_RIGHT		4804
#define ID_ANI_SMALL_TO_SMALL_LEFT		4805

#define ID_ANI_BIG_TO_FIRE_RIGHT		4806
#define ID_ANI_BIG_TO_FIRE_LEFT			4807

#define ID_ANI_BIG_TO_RACCOON_RIGHT		4808
#define ID_ANI_BIG_TO_RACCOON_LEFT		4809

//PROPERTY
#define MARIO_VMAX_X_ADJUST			0.005f
#define MARIO_WALKING_SPEED			0.1f
#define MARIO_RUNNING_SPEED			0.2f
#define	MARIO_DECELERATION_SPEED	0.0055f

#define MARIO_ACCEL_WALK_X			0.0002f
#define MARIO_ACCEL_RUN_X			0.0003f

#define MARIO_JUMP_SPEED_Y			0.25f
#define MARIO_JUMP_RUN_SPEED_Y		0.26f

#define MARIO_GRAVITY				0.00042f
#define MARIO_JUMP_DEFLECT_SPEED	0.15f
#define MARIO_MAX_POWER_UP			7
#define MARIO_SPEED_FALL			0.001f
#define MARIO_SPEED_FLYING			0.2f
#define MARIO_COIN_MAX				99
#define MARIO_HEART_MAX				99
#define MARIO_HOLDKOOPA_X_ADJUST	10
#define MARIO_HOLDKOOPA_Y_ADJUST	2
#define MARIO_TAIL_X_ADJUST			4
#define MARIO_POSITION_OUTMAP		2900
#define MARIO_GHOSTBOX_Y			1
#define MARIO_RACCON_GHOSTBOX_X_ADJUST	4
#define MARIO_RACCON_GHOSTBOX_Y_ADJUST	1
#define MARIO_ON_PLATFORM_Y_ADJUST	4
#define MARIO_SMALL_ON_PLATFORM_Y_ADJUST	6

//STATE
#define MARIO_STATE_DIE					-10

#define MARIO_STATE_IDLE				0

#define MARIO_STATE_WALKING_RIGHT		100
#define MARIO_STATE_WALKING_LEFT		101

#define MARIO_STATE_HOLDING				200	
#define MARIO_STATE_RELEASE_HOLDING		201

#define MARIO_STATE_ATTACK				900
#define MARIO_STATE_KICK				901
#define MARIO_STATE_FALL_SLOWLY			902
#define MARIO_STATE_CHANGE_LEVEL		903

#define MARIO_STATE_FLYING				800
#define MARIO_STATE_RELEASE_FLYING		801

#define MARIO_STATE_JUMP				300
#define MARIO_STATE_RELEASE_JUMP		301

#define MARIO_STATE_RUNNING_RIGHT		400
#define MARIO_STATE_RUNNING_LEFT		401

#define MARIO_STATE_SIT					600
#define MARIO_STATE_SIT_RELEASE			601

#define MARIO_STATE_DECELERATION		700

//LEVEL
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_FIRE	3
#define	MARIO_LEVEL_RACCOON	4

//BBOX
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24

#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_RACCOON_BBOX_WIDTH  22
#define MARIO_RACCOON_SITTING_BBOX_WIDTH  22
#define MARIO_RACCOON_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12
#define MARIO_CHANGE_LEVEL_HEIGHT 6

#define MARIO_DISTANCE_WITH_GHOST_BOX 20


#define MARIO_UNTOUCHABLE_TIME 2500

//TIME
#define	MARIO_FALL_SLOWLY_TIMEOUT 300
#define	MARIO_KICK_TIMEOUT 100
#define	MARIO_ATTACK_TIMEOUT 500
#define TIME_ONE_SECOND 1000
#define MARIO_CHANGE_LEVEL_TIMEOUT 1000
#define MARIO_POWER_TIMEOUT 200
#define MARIO_FLYING_TIMEOUT 5000
#define MARIO_DECREASE_POWER_TIMEOUT 1000
#define MARIO_TIME_DECREASE_WHEN_OUTMAP 7

class CMario : public CGameObject
{
	CKoopa* koopa_holding;
	float maxVx;
	float maxRunVx;
	float minVx;
	float maxVy;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	int level; 
	int untouchable; 

	int time;
	int heart;
	int coin;
	int score;
	int power;
	
	ULONGLONG untouchable_start = 0;
	ULONGLONG count_1_second = 0;
	ULONGLONG time_fly;
	ULONGLONG time_line = 0;
	ULONGLONG time_power;
	ULONGLONG time_running = 0;

	BOOLEAN isOnPlatform;
	BOOLEAN isSitting;
	BOOLEAN isDeceleration;
	BOOLEAN isHolding;
	BOOLEAN isRunning;
	BOOLEAN isFlying;
	BOOLEAN isGhostBox;
	BOOLEAN isAttack;
	BOOLEAN isKick;
	BOOLEAN isSlowFly;
	BOOLEAN isChangeLevel;
	BOOLEAN isDecreasePower;
	BOOLEAN disableKey;
	BOOLEAN canReturnWorldMap;
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBalls(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithFlowerBox(LPCOLLISIONEVENT e);
	void OnCollisionWithButton(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdFire();
	int GetAniIdRaccoon();
	int GetAniIdChangeLevel();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		time_fly = 0;
		time_line = 0;
		time_power = 0;
		
		canReturnWorldMap = false;
		isSlowFly = false;
		isAttack = false;
		isFlying = false;
		isRunning = false;
		isHolding = false;
		isSitting = false;
		isDeceleration = false;
		isGhostBox = false;
		isKick = false;
		isChangeLevel = false;
		isDecreasePower = false;
		koopa_holding = NULL;
		disableKey = false;
		maxVx = 0.0f;
		minVx = 0.0f;
		maxVy = 0.0f;
		maxRunVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		heart = 4;
		time = 300;
		score = 0;
		power = 0;
	}
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; }
	bool GetIsAttack() {return isAttack;  }

	bool GetIsOnPlatform() { return isOnPlatform; }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	void SetIsHolding(bool isHolding) { this->isHolding = isHolding; }
	bool GetIsHolding() { return isHolding; };

	void SetIsFlying(bool isFlying) { this->isFlying = isFlying; }
	bool GetIsFlying() { return isFlying; };

	int GetTime() { return time; }
	int GetCoin() { return coin; }
	int GetHeart() { return heart; }
	int GetScore() { return score; }
	int GetPower() { return power; }

	bool IsMaxPower() { return power == MARIO_MAX_POWER_UP; }
	bool GetIsChangeLevel() { return isChangeLevel; }
	bool GetDisableKey() { return disableKey; }


	void SetIsRunning(bool isRunning) { this->isRunning = isRunning; }
	bool GetIsRunning() {return isRunning; }

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	int GetLevel() { return level; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void CountDown1Second();

	void LowerLevel();
	void SummonFireBalls();
	void SummonTail();
	void MarioHoldKoopaFunction();
	void MarioThrowKoopaFunction();
	bool CountDownTimer(int time);
	void ChangeLevelMario(DWORD dt);
	void AccelerationFunction();
	void CalculatePowerToFly();
	void CalculateHeartAndCoin();
	bool CountDownTimer2(ULONGLONG time_calculate, int time_out);
	bool MarioOutWorld() { return (x > MARIO_POSITION_OUTMAP); }
};