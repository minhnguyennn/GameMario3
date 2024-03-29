#include <algorithm>
#include "debug.h"
#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "MushRoom.h"
#include "Leaf.h"
#include "QuestionBrick.h"
#include "Point.h"
#include "Koopa.h"
#include "FireBalls.h"
#include "Platform.h"
#include "Collision.h"
#include "PlayScene.h"
#include "FireBallOfMario.h"
#include "Goomba.h"
#include "Tail.h"
#include "VenusFireTrap.h"
#include "CardBox.h"
#include "Button.h"
#include "GameObject.h"
#include "Data.h"
#include "Effect.h"
#include "Pipeline.h"
#include "WorldScene.h"
#include "IntroKoopa.h"
#include "IntroGoomba.h"
#include "IntroLeaf.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	ChangeLevelMario(dt);
	AccelerationFunction();
	CalculatePowerToFly();
	CountDown1Second();
	CountDownKoopaTouch();
	CoinMax();
	HeartMax();
	GoDownPipeline();
	MarioMoveAutomationWhenGameTimeout();
	MarioNotAttackWhenTimeout();
	MarioNotFlySlowlyWhenTimeout();
	MarioNotKickWhenTimeout();
	MarioUntouchableTimeout();
	MarioDie();

	//HANDLE AUTOMATION
	SummonGreenMario();
	HandleAutomation();


	isOnPlatform = false;
	isCollisionPipeline = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	MarioHoldKoopaFunction();

	if (isSummonTail)
	{
		isSummonTail = false;
		SummonTail();
	}
}

//ONCOLLISION
void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;

		if (e->ny < 0)
		{
			isOnPlatform = true;
			isGhostBox = false;
		}
		else
		{
			if (!isDecreasePower) time_power = GetTickCount64();
			isDecreasePower = true;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
		if (!isDecreasePower) time_power = GetTickCount64();
		isDecreasePower = true;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMushRoom*>(e->obj))
		OnCollisionWithMushRoom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CFireBalls*>(e->obj))
		OnCollisionWithFireBalls(e);
	else if (dynamic_cast<CVenusFireTrap*>(e->obj))
		OnCollisionWithVenusFireTrap(e);
	else if (dynamic_cast<CCardBox*>(e->obj))
		OnCollisionWithCardBox(e);
	else if (dynamic_cast<CButton*>(e->obj))
		OnCollisionWithButton(e);
	else if (dynamic_cast<CPipeline*>(e->obj))
		OnCollisionWithPipeline(e);
	else if (dynamic_cast<CMario*>(e->obj))
		OnCollisionWithDifferentMario(e);
	else if (dynamic_cast<CIntroKoopa*>(e->obj))
		OnCollisionWithIntroKoopa(e);
	else if (dynamic_cast<CIntroGoomba*>(e->obj))
		OnCollisionWithIntroGoomba(e);
	else if (dynamic_cast<CIntroLeaf*>(e->obj))
		OnCollisionWithIntroLeaf(e);
}

void CMario::OnCollisionWithIntroLeaf(LPCOLLISIONEVENT e)
{
	CIntroLeaf* intro_leaf = dynamic_cast<CIntroLeaf*>(e->obj);
	SetLevel(MARIO_LEVEL_RACCOON);
	intro_leaf->Delete();
}

void CMario::OnCollisionWithIntroGoomba(LPCOLLISIONEVENT e)
{
	CIntroGoomba* intro_goomba = dynamic_cast<CIntroGoomba*>(e->obj);
	if (e->ny < 0 && intro_goomba->GetState() == GOOMBA_STATE_WALKING)
	{
		intro_goomba->SetState(GOOMBA_STATE_DIE);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
}

void CMario::OnCollisionWithIntroKoopa(LPCOLLISIONEVENT e)
{
	CIntroKoopa* intro_koopa = dynamic_cast<CIntroKoopa*>(e->obj);
	if (e->ny > 0)
	{
		intro_koopa->SetState(KOOPA_STATE_TURN_OVER);
		intro_koopa->SetIsAutoAttack(true);
		SetState(MARIO_STATE_AUTO_RAISED_HEAD);
	}
}

void CMario::OnCollisionWithDifferentMario(LPCOLLISIONEVENT e)
{
	/*isDifferentMario = true;
	time_collision_mario = GetTickCount64();
	SetState(MARIO_STATE_AUTO_HEIGHT_JUMP);*/
}

void CMario::OnCollisionWithPipeline(LPCOLLISIONEVENT e)
{
	CPipeline* pipeline = dynamic_cast<CPipeline*>(e->obj);
	if (e->ny < 0 && pipeline->GetType() == PIPELINE_TYPE_BIG_HIDDEN) isCollisionPipeline = true;
	else if (e->ny > 0 && pipeline->GetType() == PIPELINE_TYPE_BLACK_GO_UP) isCollisionPipeline = true;
}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	CButton* button = dynamic_cast<CButton*>(e->obj);
	if (e->ny < 0)
	{
		if (!button->GetIsPressed())
		{
			time_collision_button = GetTickCount64();
			CData::GetInstance()->SetIsConvertBrick(true);
		}
		button->SetIsPressed(true);
	}
}

void CMario::OnCollisionWithCardBox(LPCOLLISIONEVENT e)
{
	CCardBox* card_box = dynamic_cast<CCardBox*>(e->obj);
	CData* data_game = CData::GetInstance();
	CData::GetInstance()->CaculationScoreTimeout(time);
	int type_card = card_box->SetupRandomCardBox();
	if (data_game->GetNumberTouchCard() == MARIO_TOUCH_ZERO_NUMBER) data_game->SetCardStore1(type_card);
	else if (data_game->GetNumberTouchCard() == MARIO_TOUCH_ONE_NUMBER) data_game->SetCardStore2(type_card);
	else if (data_game->GetNumberTouchCard() == MARIO_TOUCH_TOW_NUMBER)
	{
		SummonScore();
		data_game->SetCardStore3(type_card);
		data_game->SumCardBox();
	}
	if (data_game->GetNumberTouchCard() < MARIO_TOUCH_CARD_BOX_MAX) data_game->IncreaseNumberTouchCard();
	position_x_out_map = x;
	disableKey = true;
	isCollisionCardBox = true;
	time_collision_card_box = GetTickCount64();
	SetState(MARIO_STATE_IDLE);
	CData::GetInstance()->SetCardBox(type_card);
	card_box->SetState(CARD_BOX_STATE_UP);
}

void CMario::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	this->LowerLevel();
}

void CMario::OnCollisionWithFireBalls(LPCOLLISIONEVENT e)
{
	this->LowerLevel();
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (CData::GetInstance()->GetIsCoin())
	{
		brick->SetState(BRICK_STATE_DELETE);
		CData::GetInstance()->IncreaseCoin();
		CData::GetInstance()->IncreaseScore();
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (e->ny < 0)
	{
		goomba->LowerLevel();
		SetupTouchTime();
		SummonScore();
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else
	{
		LowerLevel();
	}
}

void CMario::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	float plant_form_y = platform->GetY();
	if (!platform->IsBlocking())
	{
		if (e->ny < 0)
		{
			vy = 0;
			isOnPlatform = true;
			isGhostBox = true;
			if (level != MARIO_LEVEL_SMALL)
			{
				if (!isSitting)
				{
					y = (plant_form_y - MARIO_DISTANCE_WITH_GHOST_BOX);
				}
				else
				{
					y = (plant_form_y - (MARIO_DISTANCE_WITH_GHOST_BOX - MARIO_ON_PLATFORM_Y_ADJUST));
				}
			}
			else
			{
				y = (plant_form_y - (MARIO_DISTANCE_WITH_GHOST_BOX - MARIO_SMALL_ON_PLATFORM_Y_ADJUST));
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (e->ny < 0)
	{
		SetupTouchTime();
		SummonScore();
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		if (koopa->GetLevel() == KOOPA_LEVEL_BIG) koopa->SetLevel(KOOPA_LEVEL_SMALL);
		else
		{
			if (koopa->GetIsAttacking() || koopa->GetState() == KOOPA_STATE_WALKING)
			{
				koopa->SetY(koopa->GetY() - KOOPA_DISTANCE_WHEN_ATTACKING);
				koopa->SetState(KOOPA_STATE_CLOSE_SHELL);
			}
			else if ((koopa->GetIsDefense() || koopa->GetIsWaiting()) && !koopa->GetIsCollisionTail())
			{
				koopa->SetState(KOOPA_STATE_ATTACKING);
			}
		}
	}
	else if (e->nx != 0)
	{
		if (koopa->GetLevel() == KOOPA_LEVEL_SMALL)
		{
			if ((koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetIsAttacking()))
			{
				LowerLevel();
			}
			else if (isRunning)
			{
				koopa_holding = koopa;
				SetState(MARIO_STATE_HOLDING);
			}
			else if ((koopa->GetIsDefense() || koopa->GetIsWaiting() || koopa->GetIsTurnOver()) && !koopa->GetIsCollisionTail())
			{
				SetState(MARIO_STATE_KICK);
				koopa->SetState(KOOPA_STATE_ATTACKING);
			}
		}
		else
		{
			LowerLevel();
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CData::GetInstance()->IncreaseCoin();
	CData::GetInstance()->IncreaseScore();
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	//CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());

}

void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	CMushRoom* mush_room = (CMushRoom*)e->obj;
	mush_room->SummonScore();
	mush_room->Delete();
	if (level == MARIO_LEVEL_SMALL) SetLevel(MARIO_LEVEL_BIG);
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = (CLeaf*)e->obj;
	leaf->SummonScore();
	leaf->Delete();
	if (level == MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	else if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_FIRE)
	{
		SetLevel(MARIO_LEVEL_RACCOON);
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* quest_brick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (quest_brick->GetState() == QUESTION_STATE_IDLE && e->ny > 0)
		quest_brick->SetState(QUESTION_STATE_MOVE_UP);
}

//GET ANIMATION
void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (isDrawAnimation)
	{
		if (state == MARIO_STATE_DIE) aniId = ID_ANI_MARIO_DIE;
		else if (isChangLevel) aniId = GetAniIdChangeLevel();
		else if (level == MARIO_LEVEL_BIG) aniId = GetAniIdBig();
		else if (level == MARIO_LEVEL_SMALL) aniId = GetAniIdSmall();
		else if (level == MARIO_LEVEL_FIRE || isMarioGreen) aniId = GetAniIdFire();
		else if (level == MARIO_LEVEL_RACCOON) aniId = GetAniIdRaccoon();

		if (level != MARIO_LEVEL_RACCOON)
		{
			if (isGhostBox)
				animations->Get(aniId)->Render(x, y - MARIO_GHOSTBOX_Y);
			else
				animations->Get(aniId)->Render(x, y);
		}
		else
		{
			if (nx > 0)
			{
				if (isGhostBox)
					animations->Get(aniId)->Render(x - MARIO_RACCON_GHOSTBOX_X_ADJUST, y - MARIO_RACCON_GHOSTBOX_Y_ADJUST);
				else
					animations->Get(aniId)->Render(x - MARIO_RACCON_GHOSTBOX_X_ADJUST, y);
			}
			else
			{
				if (isGhostBox)
					animations->Get(aniId)->Render(x + MARIO_RACCON_GHOSTBOX_X_ADJUST, y - MARIO_RACCON_GHOSTBOX_Y_ADJUST);
				else
					animations->Get(aniId)->Render(x + MARIO_RACCON_GHOSTBOX_X_ADJUST, y);
			}
		}
	}
	else
	{
		aniId = ID_ANI_MARIO_INVISIBLE;
		animations->Get(aniId)->Render(x, y);
	}
	//RenderBoundingBox();
}

int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx == 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT;
			else  aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT;
		}
	}
	else if (isKick)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
		else  aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (IsMaxPower())
		{
			if (nx >= 0) aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
		}
		else if (isDeceleration)
		{
			if (nx > 0)	aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			else  aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (IsMaxPower()) aniId = ID_ANI_MARIO_SMALL_RUNNING_HAND_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else
			{
				if (ax > 0) aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (IsMaxPower()) aniId = ID_ANI_MARIO_SMALL_RUNNING_HAND_LEFT;
					else aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
	return aniId;
}

int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx == 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_IDLE_HOLD_RIGHT;
			else  aniId = ID_ANI_MARIO_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
		}
	}
	else if (isKick)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_KICK_RIGHT;
		else  aniId = ID_ANI_MARIO_KICK_LEFT;
	}
	else if (isAutoRaisedHead)
	{
		aniId = ID_ANI_MARIO_AUTO_RAISED_HEAD;
	}
	else if (isAutoRaisedHead2)
	{
		aniId = ID_ANI_MARIO_AUTO_RAISED_HEAD_2;
	}
	else if (!isOnPlatform)
	{
		if (vy < 0)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0) aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx > 0) aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FALL_RIGHT;
			else  aniId = ID_ANI_MARIO_FALL_LEFT;
		}
	}
	else
	{
		if (isSitting || isAutoSit)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isDeceleration)
		{
			if (nx > 0)	aniId = ID_ANI_MARIO_WALKING_RIGHT;
			else  aniId = ID_ANI_MARIO_WALKING_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (IsMaxPower()) aniId = ID_ANI_MARIO_RUNNING_HAND_RIGHT;
					else aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else
			{
				if (ax > 0) aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (IsMaxPower()) aniId = ID_ANI_MARIO_RUNNING_HAND_LEFT;
					else aniId = ID_ANI_MARIO_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdFire()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx == 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FIRE_IDLE_HOLD_RIGHT;
			else  aniId = ID_ANI_MARIO_FIRE_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_LEFT;
		}
	}
	else if (isKick)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_FIRE_KICK_RIGHT;
		else  aniId = ID_ANI_MARIO_FIRE_KICK_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (vy < 0)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0) aniId = ID_ANI_MARIO_FIRE_JUMP_RUN_RIGHT;
				else aniId = ID_ANI_MARIO_FIRE_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx > 0) aniId = ID_ANI_MARIO_FIRE_JUMP_WALK_RIGHT;
				else aniId = ID_ANI_MARIO_FIRE_JUMP_WALK_LEFT;
			}
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FIRE_FALL_RIGHT;
			else  aniId = ID_ANI_MARIO_FIRE_FALL_LEFT;
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_FIRE_SIT_RIGHT;
			else aniId = ID_ANI_MARIO_FIRE_SIT_LEFT;
		}
		else if (isDeceleration)
		{
			if (nx > 0)	aniId = ID_ANI_MARIO_FIRE_WALKING_RIGHT;
			else  aniId = ID_ANI_MARIO_FIRE_WALKING_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_FIRE_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_FIRE_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = ID_ANI_MARIO_FIRE_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (IsMaxPower()) aniId = ID_ANI_MARIO_FIRE_RUNNING_HAND_RIGHT;
					else aniId = ID_ANI_MARIO_FIRE_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_FIRE_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0) aniId = ID_ANI_MARIO_FIRE_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (IsMaxPower()) aniId = ID_ANI_MARIO_FIRE_RUNNING_HAND_LEFT;
					else aniId = ID_ANI_MARIO_FIRE_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_FIRE_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_FIRE_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx == 0)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_HOLD_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT;
		}
	}
	else if (isGoDown || isGoUp || isGoOutUp)
	{
		aniId = ID_ANI_MARIO_RACCOON_GO_DOWN;
	}
	else if (isAttack)
	{
		aniId = ID_ANI_MARIO_RACCOON_ATTACK;
	}
	else if (isKick)
	{
		if (nx > 0)	aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
		else  aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (vy < 0)
		{
			if (isFlying)
			{
				if (nx > 0)  aniId = ID_ANI_MARIO_RACCOON_FLYING_RIGHT;
				else  aniId = ID_ANI_MARIO_RACCOON_FLYING_LEFT;
			}
			else
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
		}
		else
		{
			if (isSlowFly)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_FALL_SLOWLY_RIGHT;
				else  aniId = ID_ANI_MARIO_RACCOON_FALL_SLOWLY_LEFT;
			}
			else if (isFlying)
			{
				if (nx > 0)  aniId = ID_ANI_MARIO_RACCOON_FALL_RUN_RIGHT;
				else  aniId = ID_ANI_MARIO_RACCOON_FALL_RUN_LEFT;
			}
			else
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_FALL_WALK_RIGHT;
				else  aniId = ID_ANI_MARIO_RACCOON_FALL_WALK_LEFT;
			}
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else if (isDeceleration)
		{
			if (nx > 0)	aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			else  aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (IsMaxPower()) aniId = ID_ANI_MARIO_RACCOON_RUNNING_HAND_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else
			{
				if (ax > 0) aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (IsMaxPower()) aniId = ID_ANI_MARIO_RACCOON_RUNNING_HAND_LEFT;
					else aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X) aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}
		}
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
	return aniId;
}

int CMario::GetAniIdChangeLevel()
{
	int aniId = -1;
	if (level == MARIO_LEVEL_BIG)
	{
		if (nx > 0) aniId = ID_ANI_SMALL_TO_BIG_RIGHT;
		else aniId = ID_ANI_SMALL_TO_BIG_LEFT;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (nx > 0) aniId = ID_ANI_SMALL_TO_SMALL_RIGHT;
		else aniId = ID_ANI_SMALL_TO_SMALL_LEFT;
	}
	else if (level == MARIO_LEVEL_FIRE)
	{
		if (nx > 0) aniId = ID_ANI_BIG_TO_FIRE_RIGHT;
		else aniId = ID_ANI_BIG_TO_FIRE_LEFT;
	}
	else
	{
		aniId = ID_ANI_MARIO_EFFECTS_SMOKE;
	}
	return aniId;
}


//FUNCTION
void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_AUTO_FALL:
	{
		if (level != MARIO_LEVEL_RACCOON) break;
		isSlowFly = true;
		vx = -MARIO_AUTO_VX;
		nx = 1;
		break;
	}
	case MARIO_STATE_AUTO_RAISED_HEAD:
	{
		time_auto_raised_head = GetTickCount64();
		isAutoRaisedHead = true;
		break;
	}
	case MARIO_STATE_AUTO_IDLE:
	{
		isAutoSit = false;
		isAutoWalkLeft = false;
		vx = 0.0f;
		ax = 0.0f;
		y -= MARIO_SIT_HEIGHT_ADJUST;
		break;
	}
	case MARIO_STATE_AUTO_HEIGHT_JUMP:
	{
		vy = -MARIO_AUTO_HEIGHT_JUMP;
		break;
	}
	case MARIO_STATE_AUTO_WALK_LEFT:
	{
		if (!isAutoWalkLeft)
		{
			SetState(MARIO_STATE_WALKING_LEFT);
		}
		isAutoWalkLeft = true;
		isAutoSit = false;
		time_auto_walk_left = GetTickCount64();

		break;
	}
	case MARIO_STATE_AUTO_SIT:
	{
		if (!isAutoSit)
		{
			time_auto_sit = GetTickCount64();
		}
		isAutoSit = true;
		vx = 0;
		break;
	}
	case MARIO_STATE_AUTO_JUMP:
	{
		isAutoJump = true;
		time_auto_jump = GetTickCount64();
		break;
	}
	case MARIO_STATE_RELEASE_UP_PIPELINE:
	{
		isGoUp = false;
		isGoOutUp = true;
		time_go_out_pipeline = GetTickCount64();
		break;
	}
	case MARIO_STATE_RELEASE_GO_PIPELINE:
	{
		CData::GetInstance()->SetIsMarioGoPipeline(false);
		time_go_pipeline = 0;
		isGoDown = false;
		isGoOutUp = false;
		vy = 0;
		ay = MARIO_GRAVITY;
		break;
	}
	case MARIO_STATE_GO_UP:
	{
		CData::GetInstance()->SetIsMarioGoPipeline(true);
		isGoUp = true;
		time_go_pipeline = GetTickCount64();
		ay = -0.0001f;
		break;
	}
	case MARIO_STATE_GO_DOWN:
	{
		CData::GetInstance()->SetIsMarioGoPipeline(true);
		isGoDown = true;
		time_go_pipeline = GetTickCount64();
		vy = MARIO_GO_DOWN_Y;
		ay = 0;
		break;
	}
	case MARIO_STATE_KICK:
	{
		if (isSitting) break;
		time_line = GetTickCount64();
		isKick = true;
		break;
	}
	case MARIO_STATE_HOLDING:
	{
		if (isSitting) break;
		isHolding = true;
		koopa_holding->SetIsHeld(true);
		break;
	}
	case MARIO_STATE_RELEASE_HOLDING:
	{
		isHolding = false;
		isRunning = false;
		break;
	}
	case MARIO_STATE_ATTACK:
	{
		if (isSitting || isChangLevel) break;
		isAttack = true;
		isSummonTail = true;
		time_line = GetTickCount64();
		break;
	}
	case MARIO_STATE_FALL_SLOWLY:
	{
		if (level != MARIO_LEVEL_RACCOON) break;
		time_line = GetTickCount64();
		isSlowFly = true;
		vy = -MARIO_SPEED_FALL;
		break;
	}
	case MARIO_STATE_FLYING:
	{
		if (isSitting) break;
		if (!isFlying) time_fly = GetTickCount64();
		isOnPlatform = false;
		isFlying = true;
		vy = -MARIO_SPEED_FLYING;
		break;
	}
	case MARIO_STATE_RELEASE_FLYING:
	{
		if (vy < 0)
		{
			vy += MARIO_SPEED_FLYING / 2;
		}
		break;
	}
	case MARIO_STATE_DECELERATION:
	{
		isDeceleration = true;
		minVx = MARIO_DECELERATION_SPEED;
		if (vx < 0)
		{
			if (isRunning)
			{
				ax = MARIO_ACCEL_RUN_X;
			}
			else
			{
				ax = MARIO_ACCEL_WALK_X;
			}
		}
		else if (vx > 0)
		{
			if (isRunning)
			{
				ax = -MARIO_ACCEL_RUN_X;
			}
			else
			{
				ax = -MARIO_ACCEL_WALK_X;
			}
		}
		break;
	}
	case MARIO_STATE_RUNNING_RIGHT:
	{
		if (isSitting) break;
		isRunning = true;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	}
	case MARIO_STATE_RUNNING_LEFT:
	{
		if (isSitting) break;
		isRunning = true;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	}
	case MARIO_STATE_WALKING_RIGHT:
	{
		if (isSitting)  break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	}
	case MARIO_STATE_WALKING_LEFT:
	{
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	}
	case MARIO_STATE_JUMP:
	{
		if (isSitting) break;
		if (isOnPlatform || isMarioGreen)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	}
	case MARIO_STATE_RELEASE_JUMP:
	{
		if (vy < 0)
		{
			vy += MARIO_JUMP_SPEED_Y / 2;
		}
		break;
	}
	case MARIO_STATE_SIT:
	{
		if (isAttack) break;
		if (isOnPlatform && level != MARIO_LEVEL_SMALL && vx == 0)
		{
			isSitting = true;
			vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	}
	case MARIO_STATE_SIT_RELEASE:
	{
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	}
	case MARIO_STATE_IDLE:
	{
		vx = 0.0f;
		ax = 0.0f;
		isRunning = false;
		break;
	}
	case MARIO_STATE_DIE:
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		time_die = GetTickCount64();
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if ((level == MARIO_LEVEL_BIG) || (level == MARIO_LEVEL_FIRE) || (level == MARIO_LEVEL_RACCOON))
	{
		if (isSitting || isAutoSit)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::LowerLevel()
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_RACCOON)
		{
			SetLevel(MARIO_LEVEL_BIG);
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			SetLevel(MARIO_LEVEL_SMALL);
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::SetLevel(int l)
{
	if (isSitting) return;
	if (level == MARIO_LEVEL_SMALL) y -= MARIO_SMALL_SET_LEVEL_Y_ADJUST;
	else y -= MARIO_BIG_SET_LEVEL_Y_ADJUST;
	isChangLevel = true;
	time_summon_smoke = GetTickCount64();
	level = l;
}

void CMario::SetupFlicker()
{
	if ((rand() % MARIO_RANDOM_NUMBER_ADJUST) % MARIO_RANDOM_NUMBER_ADJUST == 0) isDrawAnimation = true;
	else isDrawAnimation = false;
}

void CMario::ChangeLevelMario(DWORD dt)
{
	if (isChangLevel)
	{
		vx = 0;
		vy = 0;
	}
	else
	{
		vy += ay * dt;
		vx += ax * dt;
	}

	if (isUnTouchable) SetupFlicker();
	if (isChangLevel && CountDownTimer2(time_summon_smoke, MARIO_EFFECT_SMOKE_TIMEOUT))
	{
		time_summon_smoke = 0;
		time_change_level = GetTickCount64();
		isUnTouchable = true;
		isChangLevel = false;
	}
	else if (isUnTouchable && CountDownTimer2(time_change_level, MARIO_CHANGE_LEVEL_TIMEOUT))
	{
		time_change_level = 0;
		isUnTouchable = false;
		isDrawAnimation = true;
	}
}

void CMario::CountDown1Second() {
	if (time > 0)
	{
		if (MarioOutWorld())
		{
			if (CountDownTimer2(count_1_second, 0))
			{
				time -= MARIO_TIME_DECREASE_WHEN_OUTMAP;
				count_1_second = GetTickCount64();
			}
		}
		else
		{
			if (CountDownTimer2(count_1_second, TIME_ONE_SECOND))
			{
				time--;
				count_1_second = GetTickCount64();
			}
		}
	}
	else
	{
		time = 0;
		CGame::GetInstance()->InitiateSwitchScene(DATA_ID_WORLD_SCENE);
	}
}

void CMario::CountDownKoopaTouch()
{
	if (time_touch > 0)
	{
		if (GetTickCount64() - time_coutdown_touch > TIME_ONE_SECOND)
		{
			time_touch--;
			time_coutdown_touch = GetTickCount64();
		}
	}
	else
	{
		time_touch = 0;
		number_touch_koopa = 0;
	}
}

void CMario::SummonFireBalls() {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CFireBallOfMario* frBalls = new CFireBallOfMario(x, y);
	scene->CreateObject(frBalls);
	if (this->nx > 0) {
		frBalls->SetState(FIREBALLS_STATE_RIGHT);
	}
	else {
		frBalls->SetState(FIREBALLS_STATE_LEFT);
	}
}

void CMario::SummonTail()
{
	if (isChangLevel || isSitting) return;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CTail* tail_right = new CTail(x - MARIO_TAIL_X_ADJUST, y + MARIO_TAIL_Y_ADJUST);
	tail_right->SetState(TAIL_STATE_RIGHT);
	scene->CreateObject(tail_right);
	CTail* tail_left = new CTail(x + MARIO_TAIL_X_ADJUST, y + MARIO_TAIL_Y_ADJUST);
	tail_left->SetState(TAIL_STATE_LEFT);
	scene->CreateObject(tail_left);
}

void CMario::MarioHoldKoopaFunction()
{
	if (isHolding)
	{
		if (koopa_holding->GetIsWalking())
		{
			isHolding = false;
			return;
		}
		if (state == MARIO_STATE_RUNNING_LEFT) koopa_holding->SetX(x - MARIO_HOLDKOOPA_X_ADJUST);
		else if (state == MARIO_STATE_RUNNING_RIGHT) koopa_holding->SetX(x + MARIO_HOLDKOOPA_X_ADJUST);
		koopa_holding->SetY(y - MARIO_HOLDKOOPA_Y_ADJUST);
		koopa_holding->SetAy(0);
		koopa_holding->SetVX(vx);
	}
}

void CMario::MarioThrowKoopaFunction()
{
	if (!isHolding && koopa_holding != NULL)
	{
		koopa_holding->SetState(KOOPA_STATE_ATTACKING);
		koopa_holding = NULL;
	}
}

bool CMario::CountDownTimer(int time)
{
	if (GetTickCount64() - time_line > time)
	{
		return true;
	}
	return false;
}

bool CMario::CountDownTimer2(ULONGLONG time_calculate, int time_out)
{
	if (GetTickCount64() - time_calculate > time_out)
	{
		return true;
	}
	return false;
}

void CMario::AccelerationFunction()
{
	if (abs(vx) > abs(maxVx))
	{
		vx = maxVx;
	}
	else if (abs(vx) < abs(minVx))
	{
		SetState(MARIO_STATE_IDLE);
		isDeceleration = false;
	}
}

void CMario::CalculatePowerToFly()
{
	if (CountDownTimer2(time_power, MARIO_DECREASE_POWER_TIMEOUT))
	{
		isDecreasePower = false;
		time_power = 0;
	}

	if (isFlying && IsMaxPower())
	{
		if (CountDownTimer2(time_fly, MARIO_FLYING_TIMEOUT))
		{
			power = 0;
			isFlying = false;
			time_fly = 0;
		}
	}
	else
	{
		if (isRunning && isOnPlatform && !isDecreasePower && !IsChangeDirection())
		{
			if (CountDownTimer2(time_running, MARIO_POWER_TIMEOUT))
			{
				if (power < MARIO_MAX_POWER_UP)
				{
					power++;
				}
				time_running = GetTickCount64();
			}
		}
		else
		{
			if (CountDownTimer2(time_running, MARIO_POWER_TIMEOUT))
			{
				if (power > 0)
				{
					power--;
				}
				time_running = GetTickCount64();
			}
		}
	}
}

void CMario::CoinMax()
{
	CData* data_game = CData::GetInstance();
	if (data_game->GetMarioCoin() > DATA_MARIO_COIN_MAX)
	{
		data_game->IncreaseHeart();
		data_game->SetMarioCoin(0);
	}
}

void CMario::HeartMax()
{
	CData* data_game = CData::GetInstance();
	if (data_game->GetMarioHeart() > DATA_MARIO_HEART_MAX)
	{
		data_game->SetMarioHeart(DATA_MARIO_HEART_MAX);
	}

	if (!CData::GetInstance()->GetIsResetGame())  CData::GetInstance()->SetMarioLevel(level);
}

void CMario::SetupTouchTime()
{
	time_touch = MARIO_TIME_TOUCH_MAX;
	if (number_touch_koopa < MARIO_NUMBER_TOUCH_MAX) number_touch_koopa++;
	else number_touch_koopa = MARIO_NUMBER_START_TOUCH;
}

void CMario::SummonScore()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (number_touch_koopa == MARIO_TOUCH_ONE_NUMBER)
	{
		CPoint* point_100 = new CPoint(x, y, POINT_TYPE_100);
		scene->CreateObject(point_100);
		point_100->SetState(POINT_STATE_MOVE_UP);
	}
	else if (number_touch_koopa == MARIO_TOUCH_TOW_NUMBER)
	{
		CPoint* point_200 = new CPoint(x, y, POINT_TYPE_200);
		scene->CreateObject(point_200);
		point_200->SetState(POINT_STATE_MOVE_UP);
	}
	else
	{
		CPoint* point_big_up = new CPoint(x, y, POINT_TYPE_BIG_UP);
		scene->CreateObject(point_big_up);
		point_big_up->SetState(POINT_STATE_MOVE_UP);
	}
}

void CMario::GoDownPipeline()
{
	if (isGoDown && CountDownTimer2(time_go_pipeline, MARIO_TIME_GO_DOWN_TIMEOUT))
	{
		SetPosition(MARIO_HIDDEN_MAP_POSITION_X, MARIO_HIDDEN_MAP_POSITION_Y);
		SetState(MARIO_STATE_RELEASE_GO_PIPELINE);
	}
	else if (isGoUp && CountDownTimer2(time_go_pipeline, MARIO_GO_UP_HIDDEN_TIMEOUT))
	{
		SetPosition(MARIO_RELEASE_HIDDEN_MAP_POSITION_X, MARIO_RELEASE_HIDDEN_MAP_POSITION_Y);
		SetState(MARIO_STATE_RELEASE_UP_PIPELINE);
	}
	else if (isGoOutUp && CountDownTimer2(time_go_out_pipeline, MARIO_GO_UP_TIMEOUT))
	{
		SetState(MARIO_STATE_RELEASE_GO_PIPELINE);
	}
}

void CMario::MarioMoveAutomationWhenGameTimeout()
{
	if (disableKey && isOnPlatform)
	{
		SetState(MARIO_STATE_WALKING_RIGHT);
	}
}

void CMario::MarioNotAttackWhenTimeout()
{
	if (isAttack && CountDownTimer(MARIO_ATTACK_TIMEOUT))
	{
		isAttack = false;
	}
}

void CMario::MarioNotFlySlowlyWhenTimeout()
{
	if (isSlowFly && CountDownTimer(MARIO_FALL_SLOWLY_TIMEOUT))
	{
		isSlowFly = false;
	}
}

void CMario::MarioNotKickWhenTimeout()
{
	if (isKick && CountDownTimer(MARIO_KICK_TIMEOUT))
	{
		isKick = false;
	}
}

void CMario::MarioUntouchableTimeout()
{
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
}

void CMario::SummonGreenMario()
{
	if (isDifferentMario && CountDownTimer2(time_collision_mario, MARIO_TIME_COLLISION_DIF_MARIO))
	{
		vx = 0.0f;
	}

	if (isAutoJump && CountDownTimer2(time_auto_jump, MARIO_AUTO_JUMP_TIMEOUT))
	{
		SetState(MARIO_STATE_JUMP);
		isAutoJump = false;
		isAutoHeightJump = true;
		time_auto_jump = GetTickCount64();
	}

	if (isAutoHeightJump && CountDownTimer2(time_auto_jump, 1150))
	{
		isAutoHeightJump = false;
		isStopGreen = true;
		vy = -0.3f;
		time_auto_jump = GetTickCount64();
	}

	if (isStopGreen && CountDownTimer2(time_auto_jump, 2000))
	{
		vx = 0.0f;
	}

	if (isAutoWalkLeft && CountDownTimer2(time_auto_walk_left, MARIO_AUTO_WALK_LEFT_TIMEOUT))
	{
		SetState(MARIO_STATE_AUTO_SIT);
	}

	if (isAutoSit && CountDownTimer2(time_auto_sit, MARIO_AUTO_SIT_TIMEOUT))
	{
		SetState(MARIO_STATE_AUTO_IDLE);
	}
}

void CMario::MarioDie()
{
	if (y > MARIO_POSITION_DIE_Y && !CData::GetInstance()->GetIsResetGame())
	{
		SetState(MARIO_STATE_DIE);
	}

	if ((state == MARIO_STATE_DIE) && CountDownTimer2(time_die, MARIO_TIME_DIE))
	{
		CGame::GetInstance()->InitiateSwitchScene(DATA_ID_WORLD_SCENE);
		CData::GetInstance()->DecreaseHeart();
	}
}

void CMario::HandleAutomation()
{
	if (isCollisionCardBox && CountDownTimer2(time_collision_card_box, 1000))
	{
		isCollisionCardBox = false;
	}


	if (isAutoRaisedHead && CountDownTimer2(time_auto_raised_head, MARIO_AUTO_RAISED_HEAD_TIMEOUT))
	{
		isAutoRaisedHead = false;
		isAutoRaisedHead2 = true;
		time_auto_raised_head = GetTickCount64();
	}

	if (isAutoRaisedHead2 && CountDownTimer2(time_auto_raised_head, MARIO_AUTO_JUMP_EAT_LEAF_TIMEOUT))
	{
		isAutoRaisedHead2 = false;
		isAutoFail = true;
		SetState(MARIO_STATE_JUMP);
		time_auto_raised_head = GetTickCount64();
	}

	if (isAutoFail && CountDownTimer2(time_auto_raised_head, MARIO_AUTO_FAIL_SLOWLY_TIMEOUT))
	{
		isAutoFail = false;
		vx = 0.0f;
		time_auto_raised_head = GetTickCount64();
		isAutoWalkRight = true;
	}

	if (isAutoFail)
	{
		SetState(MARIO_STATE_AUTO_FALL);
	}

	if (isAutoWalkRight && CountDownTimer2(time_auto_raised_head, MARIO_AUTO_WALK_RIGHT_TIMEOUT))
	{
		SetState(MARIO_STATE_WALKING_RIGHT);
		isAutoStop = true;
		if (!isAutoStop)
		{
			time_auto_raised_head = GetTickCount64();
		}
	}

	if (isAutoStop && CountDownTimer2(time_auto_raised_head, 2000))
	{
		SetState(MARIO_STATE_WALKING_LEFT);
		isAutoWalkRight = false;
		isJumpKoopa = true;
		time_auto_raised_head = GetTickCount64();
		isAutoStop = false;
	}

	if (isJumpKoopa && CountDownTimer2(time_auto_raised_head, 1500))
	{
		SetState(MARIO_STATE_JUMP);
		isStopJumpKoopa = true;
		time_stop_jump = GetTickCount64();
		isJumpKoopa = false;
	}

	if (isStopJumpKoopa && CountDownTimer2(time_stop_jump, 200))
	{	
		SetState(MARIO_STATE_RELEASE_JUMP);
		vx = 0.0f;
	}

}