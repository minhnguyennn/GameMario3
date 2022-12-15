#include "Automation.h"

void CAutomation::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CAutomation::Render()
{
	if (!checkObjectInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COURSE_CLEAR)->Render(x, y);
	animations->Get(ID_ANI_YOU_GOT_A_CARD)->Render(x, y + 26);
}

void CAutomation::SetState(int state)
{
	/*switch (state)
	{
	case COIN_STATE_MOVE_DOWN:
		vy = MAX_VY;
		break;
	case COIN_STATE_DELETE:
	{
		Delete();
		break;
	}
	case COIN_STATE_MOVE_UP:
		vy = -MAX_VY;
		break;
	case COIN_STATE_IDLE:
		vy = 0;
		break;
	default:
		break;
	}*/
	CGameObject::SetState(state);
}