#include "Koopa.h"
#include"debug.h"
#include"Platform.h"
#include"PlayScene.h"
#include"QuestionBrick.h"
#include"VenusFireTrap.h"
#include"Brick.h"
#include"Tail.h"
#include"Mario.h"


void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDie) return;

	if (state == KOOPA_STATE_WALKING || state == KOOPA_STATE_FLY) 
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WAITING / 2;
		top = y - KOOPA_BBOX_WAITING / 2;
		right = left + KOOPA_BBOX_WAITING;
		bottom = top + KOOPA_BBOX_WAITING;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		if (level == KOOPA_LEVEL_BIG) 
		{
			SetState(KOOPA_STATE_FLY);
		}
		else
		{
			if (isTurnOver && !isAttacking)
			{
				vx = 0;
			}
			else
			{
				vy = 0;
			}
		}
	}
	
	if (e->nx != 0 && e->obj->IsBlocking()) 
	{
		vx = -vx;
	}

	if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatForm(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CVenusFireTrap*>(e->obj))
		OnCollisionWithVenusFireTrap(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithDifferentKoopa(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CTail*>(e->obj))
		OnCollisionWitTail(e);
}

void CKoopa::OnCollisionWitTail(LPCOLLISIONEVENT e)
{
	SetState(KOOPA_STATE_TURN_OVER);
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e) 
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (isAttacking)
	{
		goomba->SetState(GOOMBA_STATE_DIE_TURN_OVER);
	}
}

void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e) 
{
	float left, top, right, bottom;
	e->obj->GetBoundingBox(left, top, right, bottom);
	
	if (vx > 0 && x > right || vx < 0 && x < left)
	{
		vx = -vx;
	}
}

void CKoopa::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	float plant_form_y = platform->GetY();
	float plat_form_x_start = platform->GetX() - KOOPA_REMAINDER_OF_DISTANCE;
	float plat_form_x_end = platform->GetX() + (platform->GetLength() * KOOPA_WIDTH_OF_BOX) - KOOPA_REMAINDER_OF_DISTANCE;
	if(!platform->IsBlocking()) isGhostBox = true;
	else isGhostBox = false;
	if (level == KOOPA_LEVEL_SMALL) 
	{
		if (!platform->IsBlocking()) 
		{
			if (e->ny < 0) {
				vy = 0;
				if (!isDefense) {
					//CASE WHEN KOOPA WAIT AND ATTACK AND TURN OVER
					if (isWaiting || isAttacking || isTurnOver) {
						y = plant_form_y - KOOPA_UP_DISTANCE;
					}
					//CASE WHEN KOOPA MOVE
					else {
						y = plant_form_y - KOOPA_UP_DISTANCE_MOVE;
						if (x < plat_form_x_start) {
							vx = -vx;
							x = plat_form_x_start;
						}
						if (x > plat_form_x_end) {
							vx = -vx;
							x = plat_form_x_end;
						}
					}
				}
				//CASE WHEN KOOPA DEFENSE
				else {
					y = plant_form_y - KOOPA_UP_DISTANCE;
				}
			}
		}
	}
}

void CKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	//Question brick will summon leaf or green mushroom follow level mario
	CQuestionBrick* question_brick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->nx != 0) 
	{
		if (question_brick->GetState() == QUESTION_STATE_IDLE && isAttacking)
		{
			question_brick->SummonItemsFromBrickQuestion();
		}
	}
}

void CKoopa::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	//Venus fire trap will deleted
	CVenusFireTrap* vf_trap = dynamic_cast<CVenusFireTrap*>(e->obj);
	if ((e->nx != 0) || (e->nx < 0)) 
	{
		if (isAttacking) 
		{
			vf_trap->SetSummonItems(VFTRAP_TYPE_POINT);
			vf_trap->SetState(VFTRAP_STATE_DIE);
		}
	}
}

void CKoopa::OnCollisionWithDifferentKoopa(LPCOLLISIONEVENT e)
{
	//Different Koopa will turned over and died.
	CKoopa* df_koopa = dynamic_cast<CKoopa*>(e->obj);
	if (isAttacking) 
	{
		df_koopa->SetState(KOOPA_STATE_DIE_TURN_OVER);
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	vy += ay * dt;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario->GetIsChangeLevel()) return;

	if ( isDefense && CountDownTimer(KOOPA_CLOSE_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_WAITING);
	}

	if (isWaiting && CountDownTimer(KOOPA_CLOSE_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_WALKING);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = 0;
	if (type == KOOPA_TYPE_TROOPA)
	{
		if (level == KOOPA_LEVEL_SMALL)
		{
			if (vx > 0)
				aniId = ID_ANI_KOOPA_RED_SMALL_WALKING_RIGHT;
			else if (vx < 0)
				aniId = ID_ANI_KOOPA_RED_SMALL_WALKING_LEFT;
		}
		else if (level == KOOPA_LEVEL_BIG)
		{
			if (vx > 0)
				aniId = ID_ANI_KOOPA_RED_BIG_WALKING_RIGHT;
			else if (vx < 0)
				aniId = ID_ANI_KOOPA_RED_BIG_WALKING_LEFT;
		}

		if (state == KOOPA_STATE_WAITING)
			aniId = ID_ANI_KOOPA_RED_WAITING;
		else if (state == KOOPA_STATE_CLOSE_SHELL)
			aniId = ID_ANI_KOOPA_RED_CLOSE_SHELL;
		else if (state == KOOPA_STATE_ATTACKING)
		{
			if (isTurnOver)
				aniId = ID_ANI_KOOPA_RED_TURN_OVER_ATTACKING;
			else
				aniId = ID_ANI_KOOPA_RED_ATTACKING;
		}
		else if (state == KOOPA_STATE_TURN_OVER)
			aniId = ID_ANI_KOOPA_RED_TURN_OVER;
	}
	else if (type == KOOPA_TYPE_PARATROOPA)
	{
		if (level == KOOPA_LEVEL_SMALL) 
		{
			if (vx > 0)
				aniId = ID_ANI_KOOPA_GREEN_SMALL_WALKING_RIGHT;
			else if (vx < 0)
				aniId = ID_ANI_KOOPA_GREEN_SMALL_WALKING_LEFT;
		}
		else if (level == KOOPA_LEVEL_BIG) 
		{
			if (vx > 0)
				aniId = ID_ANI_KOOPA_GREEN_BIG_WALKING_RIGHT;
			else if (vx < 0)
				aniId = ID_ANI_KOOPA_GREEN_BIG_WALKING_LEFT;
		}

		if (state == KOOPA_STATE_WAITING)
			aniId = ID_ANI_KOOPA_GREEN_WAITING;
		else if (state == KOOPA_STATE_CLOSE_SHELL)
			aniId = ID_ANI_KOOPA_GREEN_CLOSE_SHELL;
		else if (state == KOOPA_STATE_ATTACKING)
			aniId = ID_ANI_KOOPA_GREEN_ATTACKING;
		else if (state == KOOPA_STATE_TURN_OVER)
			aniId = ID_ANI_KOOPA_GREEN_TURN_OVER;
	}
	if(isGhostBox)
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	else
		CAnimations::GetInstance()->Get(aniId)->Render(x, y + KOOPA_Y_ADJUST);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	switch (state)
	{
	case KOOPA_STATE_FLY: 
	{
		vy = -KOOPA_FLY_SPEED;
		break;
	}
	case KOOPA_STATE_DIE_TURN_OVER:
	{
		isTurnOver = true;
		isDie = true;
		vx = -KOOPA_TURN_UP_JUMP_VX;
		vy = -KOOPA_TURN_UP_JUMP_VY;
		break;
	}
	case KOOPA_STATE_TURN_OVER:
	{
		isTurnOver = true;
		isDie = false;
		isAttacking = false;
		time_line = GetTickCount64();
		vx = KOOPA_TURN_UP_JUMP_VX * isLeftWithMario();
		vy = -KOOPA_TURN_UP_JUMP_VY;
		break;
	}
	case KOOPA_STATE_DIE:
	{
		vx = 0;
		die_start = GetTickCount64();
		isDie = true;
		break;
	}
	case KOOPA_STATE_ATTACKING:
	{
		ay = KOOPA_GRAVITY;
		vx = KOOPA_WALKING_ATTACKING_SPEED * isLeftWithMario();
		isAttacking = true;
		isWaiting = false;
		isDefense = false;
		break;
	}
	case KOOPA_STATE_WAITING:
	{
		vx = 0;
		isWaiting = true;
		isDefense = false;
		time_line = GetTickCount64();
		break;
	}
	case KOOPA_STATE_CLOSE_SHELL:
	{
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_WAITING) / 2;
		vx = 0;
		time_line = GetTickCount64();
		isDefense = true;
		isAttacking = false;
		break;
	}
	case KOOPA_STATE_WALKING:
	{
		if (isWaiting)
		{
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_WAITING) / 2;
		}
		ay = KOOPA_GRAVITY;
		vx = KOOPA_WALKING_SPEED;
		isWaiting = false;
		break;
	}
	default:
		break; 
	}
	CGameObject::SetState(state);
}

int CKoopa::isLeftWithMario()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (x < mario->GetX()) return -1;
	else return 1;
}

void CKoopa::LowerLevel()
{
	if (level == KOOPA_LEVEL_BIG)
	{
		level = MARIO_LEVEL_SMALL;
	}
	else
	{
		DebugOut(L">>> Koopa DIE >>> \n");
		SetState(KOOPA_STATE_DIE_TURN_OVER);
	}
}

bool CKoopa::CountDownTimer(int time)
{
	if (GetTickCount64() - time_line > time)
	{
		return true;
	}
	return false;
}