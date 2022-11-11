#include "KoopaParatroopas.h"
#include"debug.h"
#include"Platform.h"
#include"PlayScene.h"
#include"QuestionBrick.h"
#include"VenusFireTrap.h"
#include"Koopa.h"


void CKoopaParatroopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if ((isDie)) return;
	if (isDefense || isWaiting || isAttacking || isTurnOver)
	{
		left = x - KOOPA_PARATROOPAS_BBOX_WAITING / 2;
		top = y - KOOPA_PARATROOPAS_BBOX_WAITING / 2;
		right = left + KOOPA_PARATROOPAS_BBOX_WAITING;
		bottom = top + KOOPA_PARATROOPAS_BBOX_WAITING;
	}
	else
	{
		left = x - KOOPA_PARATROOPAS_BBOX_WIDTH / 2;
		top = y - KOOPA_PARATROOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPA_PARATROOPAS_BBOX_WIDTH;
		bottom = top + KOOPA_PARATROOPAS_BBOX_HEIGHT;
	}
}

void CKoopaParatroopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopaParatroopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (dynamic_cast<CKoopa*>(e->obj)) return;
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = -KOOPA_PARATROOPAS_FLY_SPEED;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
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

}

void CKoopaParatroopas::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	float plant_form_y = platform->GetY();
	float plat_form_x_start = platform->GetX() - KOOPA_PARATROOPAS_REMAINDER_OF_DISTANCE;
	float plat_form_x_end = platform->GetX() + (platform->GetLength() * KOOPA_PARATROOPAS_BBOX_WIDTH) - KOOPA_PARATROOPAS_REMAINDER_OF_DISTANCE;
	if (!platform->IsBlocking()) {
		if (e->ny < 0) {
			vy = -KOOPA_PARATROOPAS_FLY_SPEED;
			if (!isDefense) {
				//CASE WHEN KOOPA PARATROOPAS WAIT, ATTACK AND TURN OVER
				if (isWaiting || isAttacking || isTurnOver) {
					y = plant_form_y - KOOPA_PARATROOPAS_UP_DISTANCE;
				}
				//CASE WHEN KOOPA PARATROOPAS MOVE
				else {
					y = plant_form_y - KOOPA_PARATROOPAS_UP_DISTANCE_MOVE;
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
			//CASE WHEN KOOPA PARATROOPAS DEFENSE
			else {
				y = plant_form_y - KOOPA_PARATROOPAS_UP_DISTANCE;
			}
		}
	}
}

void CKoopaParatroopas::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	//Question brick will summon leaf or green mushroom follow level mario
	CQuestionBrick* question_brick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->nx != 0) {
		if (isAttacking) {
			question_brick->SummonItemsFromBrickQuestion();
		}
	}
}

void CKoopaParatroopas::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	//Venus fire trap will deleted
	CVenusFireTrap* vf_trap = dynamic_cast<CVenusFireTrap*>(e->obj);
	if ((e->nx != 0) || (e->nx < 0)) {
		if (isAttacking) {
			vf_trap->SetSummonItems(VFTRAP_TYPE_POINT);
			vf_trap->Delete();
		}
	}
}

void CKoopaParatroopas::OnCollisionWithDifferentKoopa(LPCOLLISIONEVENT e)
{
	//Different Koopa will turned over and died.
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	//DebugOut(L"e->nx %f", e->nx);
	if ((isAttacking) || (isHeld)) {
		koopa->SetState(KOOPA_STATE_DIE_TURN_OVER);
		//df_koopa->SetState(KOOPA_STATE_DIE);
	}

}

void CKoopaParatroopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	//DebugOut(L"x y %f %f \n", x,y);

	//DebugOut(L"isHeld %d \n", isHeld);
	//DebugOut(L"AY VY %f %f \n", ay, vy);
	//DebugOut(L"[OKE] x: %f\n", start_x);
	//DebugOut(L"[OKE] isDefense  %d  \n", isDefense);
	//DebugOut(L"isDie %d", isDie);

	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (isHeld)
	{
		ChangePositionFollowMario();
	}

	if (isSummon) {
		y = mario->GetY();
		//DebugOut(L"[oke] right: %d\n", mario->GetState());
		if ((mario->GetState() == MARIO_STATE_WALKING_RIGHT) || (mario->GetState() == MARIO_STATE_IDLE) || (mario->GetState() == MARIO_STATE_SUMMON_KOOPA)) {
			x = mario->GetX() + 14;
		}
		else {
			x = mario->GetX() - 14;
		}
	}

	if (isDefense && (GetTickCount64() - close_start > KOOPA_PARATROOPAS_CLOSE_SHELL_TIMEOUT))
	{
		SetState(KOOPA_PARATROOPAS_STATE_WAITING);
		//DebugOut(L"[OKE] isDefense isWaiting waiting_start %d %d %f \n", isDefense, isWaiting, waiting_start);
	}

	if (isWaiting && (GetTickCount64() - waiting_start > KOOPA_PARATROOPAS_CLOSE_SHELL_TIMEOUT))
	{
		//DebugOut(L"[OKE]\n");
		SetState(KOOPA_PARATROOPAS_STATE_WALKING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopaParatroopas::Render()
{
	//Type of animation
	int aniId = ID_ANI_KOOPA_PARATROOPAS_WALKING_LEFT;
	if (isWaiting)
	{
		aniId = ID_ANI_KOOPA_PARATROOPAS_WAITING;
	}
	else if (isDefense)
	{
		aniId = ID_ANI_KOOPA_PARATROOPAS_CLOSE_SHELL;
	}
	else if (isAttacking) {
		aniId = ID_ANI_KOOPA_PARATROOPAS_ATTACKING;
	}
	else if (isTurnOver) {
		aniId = ID_ANI_KOOPA_PARATROOPAS_TURN_OVER;
	}
	else if (vx > 0)
	{
		aniId = ID_ANI_KOOPA_PARATROOPAS_WALKING_RIGHT;
	}
	//DebugOut(L"[OKE] aniId: %d\n", aniId);
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopaParatroopas::SetState(int state)
{

	switch (state)
	{
	case KOOPA_PARATROOPAS_STATE_DIE_TURN_OVER:
	{
		if (isSummon == true) {
			ay = 0;
		}
		isTurnOver = true;
		isDie = true;
		isWaiting = false;
		isAttacking = false;
		isDefense = false;
		vx = -0.05f;
		vy = -0.05f;
		break;
	}
	case KOOPA_PARATROOPAS_STATE_TURN_OVER:
	{
		if (isSummon == true) {
			ay = 0;
		}
		isTurnOver = true;
		isDie = false;
		isWaiting = false;
		isAttacking = false;
		isDefense = false;
		vx = -0.05f;
		vy = -0.05f;
		break;
	}
	case KOOPA_PARATROOPAS_STATE_DIE:
	{
		die_start = GetTickCount64();
		isDie = true;
		isWaiting = false;
		isAttacking = false;
		isDefense = false;
		isTurnOver = false;
		vx = 0;
		break;
	}
	case KOOPA_PARATROOPAS_STATE_ATTACKING:
	{
		ay = KOOPA_PARATROOPAS_GRAVITY;
		vx = KOOPA_PARATROOPAS_ATTACKING_SPEED * isLeftWithMario();
		isWaiting = false;
		isAttacking = true;
		isDefense = false;
		isTurnOver = false;
		isHeld = false;
		break;
	}
	case KOOPA_PARATROOPAS_STATE_WAITING:
	{
		vx = 0;
		vy = 0;
		isWaiting = true;
		isDefense = false;
		isAttacking = false;
		isHeld = false;
		isTurnOver = false;
		waiting_start = GetTickCount64();
		break;
	}
	case KOOPA_PARATROOPAS_STATE_CLOSE_SHELL:
	{
		y += (KOOPA_PARATROOPAS_BBOX_HEIGHT - KOOPA_PARATROOPAS_BBOX_WAITING) / 2;
		vx = 0;
		close_start = GetTickCount64();
		isDefense = true;
		isTurnOver = false;
		isHeld = false;
		isAttacking = false;
		isWaiting = false;
		break;
	}
	case KOOPA_PARATROOPAS_STATE_WALKING:
	{
		ay = KOOPA_PARATROOPAS_GRAVITY;
		vx = -KOOPA_PARATROOPAS_WALKING_SPEED * (-isLeftWithMario());
		if (isWaiting) y -= (KOOPA_PARATROOPAS_BBOX_HEIGHT - KOOPA_PARATROOPAS_BBOX_WAITING) / 2;
		isWaiting = false;
		isDefense = false;
		isAttacking = false;
		isHeld = false;
		isTurnOver = false;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

int CKoopaParatroopas::isLeftWithMario()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (x < mario->GetX()) return -1;
	else return 1;
}

void CKoopaParatroopas::ChangePositionFollowMario()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario->GetNx() < 0) {
		x = mario->GetX() - 19 + 1;
	}
	else {
		x = mario->GetX() + 19 - 1;

	}
	y = mario->GetY() - 2;
	//vx = mario->GetVX()-0.05f;
	vy = mario->GetVY();
}

