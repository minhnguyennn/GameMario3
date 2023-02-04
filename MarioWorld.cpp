#include "MarioWorld.h"
#include "Door.h"
#include "IntroScene.h"
#include "Data.h"

CMarioWorld::CMarioWorld(float x, float y) :CGameObject(x, y)
{
	isGoTop = false;
	isGoLeft = false;
	isGoBottom = false;
	isGoRight = true;
	isCollisionDoor = false;
	isDelay = false;
	isRedArrow = false;
	time_delay = GetTickCount64();
	time_change_map = 0;
}

void CMarioWorld::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (GetTickCount64() - time_delay > MARIO_WORLD_TIME_DELAY)
	{
		isDelay = true;
	}
	if ((state == MARIO_WORLD_STATE_GO_INTRO_SCENE) && (GetTickCount64() - time_change_map > MARIO_WORLD_TIME_CHANGE_MAP))
	{
		CGame::GetInstance()->InitiateSwitchScene(DATA_ID_INTRO_SCENE);
	}
	if ((state == MARIO_WORLD_STATE_GO_PLAYSCENE) && (GetTickCount64() - time_change_map > MARIO_WORLD_TIME_CHANGE_MAP))
	{
		CGame::GetInstance()->InitiateSwitchScene(MARIO_WORLD_ID_PLAY_SCENE);
	}
	if ((state == MARIO_WORLD_STATE_GO_PLAYSCENE_RESET) && (GetTickCount64() - time_change_map > MARIO_WORLD_TIME_CHANGE_MAP))
	{
		CGame::GetInstance()->InitiateSwitchScene(MARIO_WORLD_ID_PLAY_SCENE);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioWorld::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int data = CData::GetInstance()->GetMarioLevel();
	if (isDelay)
	{
		if (data == DATA_MARIO_LEVEL_SMALL) 
			animations->Get(ID_ANI_SMALL_MARIO_WORLD)->Render(x, y);
		else if (data == DATA_MARIO_LEVEL_BIG)
			animations->Get(ID_ANI_BIG_MARIO_WORLD)->Render(x, y);
		else if (data == DATA_MARIO_LEVEL_FIRE)
			animations->Get(ID_ANI_FIRE_MARIO_WORLD)->Render(x, y);
		else if (data == DATA_MARIO_LEVEL_RACCOON)
			animations->Get(ID_ANI_RACCON_MARIO_WORLD)->Render(x, y);
		else
			animations->Get(ID_ANI_SMALL_MARIO_WORLD)->Render(x, y);

	}
	//RenderBoundingBox();
}

void CMarioWorld::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MARIO_WORLD_SMALL_BBOX_WIDTH / 2;
	t = y - MARIO_WORLD_SMALL_BBOX_HEIGHT / 2;
	r = l + MARIO_WORLD_SMALL_BBOX_WIDTH;
	b = t + MARIO_WORLD_SMALL_BBOX_HEIGHT;
}

void CMarioWorld::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CMarioWorld::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->nx != 0 && e->obj->IsBlocking()) 
	{
		vx = 0;
	}
	if (dynamic_cast<CDoor*>(e->obj))
		OnCollisionWithDoor(e);
}

void CMarioWorld::OnCollisionWithDoor(LPCOLLISIONEVENT e)
{
	CDoor* door = dynamic_cast<CDoor*>(e->obj);
	door->SetIsMarioIdle(true);
	CheckTypeDoor(door->GetType());
}

void CMarioWorld::SetState(int state)
{
	switch (state)
	{
	case MARIO_WORLD_STATE_GO_PLAYSCENE_RESET:
	{
		CData::GetInstance()->ResetGame();
		time_change_map = GetTickCount64();
		break;
	}
	case MARIO_WORLD_STATE_GO_INTRO_SCENE:
	{
		CData::GetInstance()->ResetGame();
		time_change_map = GetTickCount64();
		break;
	}
	case MARIO_WORLD_STATE_GO_PLAYSCENE:
	{
		time_change_map = GetTickCount64();
		isCollisionDoor = false;
		break;
	}
	case MARIO_WORLD_STATE_UP:
		vy = -MARIO_WORLD_SPEED;
		vx = 0;
		break;
	case MARIO_WORLD_STATE_DOWN:
	{
		vy = MARIO_WORLD_SPEED;
		vx = 0;
		break;
	}
	case MARIO_WORLD_STATE_RIGHT:
	{
		vy = 0;
		vx = MARIO_WORLD_SPEED;
		break;
	}
	case MARIO_WORLD_STATE_LEFT:
	{
		vy = 0;
		vx = -MARIO_WORLD_SPEED;
		break;
	}
	case MARIO_WORLD_STATE_IDLE:
	{
		vy = 0;
		vx = 0;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CMarioWorld::CheckTypeDoor(int type_door)
{
	switch (type_door)
	{
	case DOOR_TYPE_START:
	{
		isCollisionDoor = true;
		isGoTop = false;
		isGoLeft = false;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_YELLOW_1:
	{
		isGoTop = true;
		isGoLeft = true;
		isGoBottom = true;
		isGoRight = false;
		break;
	}
	case DOOR_TYPE_YELLOW_2:
	{
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_YELLOW_3:
	{
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = true;
		isGoRight = false;
		break;
	}
	case DOOR_TYPE_YELLOW_MUSHROOM_1:
	{
		isCollisionDoor = true;
		isGoTop = true;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = false;
		break;
	}
	case DOOR_TYPE_YELLOW_4:
	{
		isGoTop = true;
		isGoLeft = false;
		isGoBottom = true;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_SPECIAL:
	{
		isCollisionDoor = true;
		isGoTop = true;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = false;
		break;
	}
	case DOOR_TYPE_YELLOW_CASTLE:
	{
		isCollisionDoor = true;
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_YELLOW_5:
	{
		isGoTop = true;
		isGoLeft = false;
		isGoBottom = true;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_YELLOW_6:
	{
		isGoTop = true;
		isGoLeft = false;
		isGoBottom = true;
		isGoRight = false;
		break;
	}
	case DOOR_TYPE_YELLOW_7:
	{
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_YELLOW_8:
	{
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = true;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_YELLOW_MUSHROOM_2:
	{
		isCollisionDoor = true;
		isGoTop = false;
		isGoLeft = false;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_YELLOW_9:
	{
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_BIG_CASTLE:
	{
		isCollisionDoor = true;
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = false;
		break;
	}
	case DOOR_TYPE_1:
	{
		isCollisionDoor = true;
		isGoTop = false;
		isGoLeft = false;
		isGoBottom = true;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_2:
	{
		isCollisionDoor = true;
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = true;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_3:
	{
		isCollisionDoor = true;
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_4:
	{
		isCollisionDoor = true;
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_5:
	{
		isCollisionDoor = true;
		isGoTop = true;
		isGoLeft = false;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_6:
	{
		isCollisionDoor = true;
		isGoTop = true;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = false;
		break;
	}
	default:
		break;
	}
}