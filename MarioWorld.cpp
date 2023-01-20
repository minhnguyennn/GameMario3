#include "MarioWorld.h"
#include "Door.h"

CMarioWorld::CMarioWorld(float x, float y) :CGameObject(x, y)
{
	isGoTop = false;
	isGoLeft = false;
	isGoBottom = false;
	isGoRight = true;
}

void CMarioWorld::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	//DebugOut(L"state : %d\n", state);
	//DebugOut(L"vx : %f\n", vx);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioWorld::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SMALL_MARIO_WORLD)->Render(x, y);
	RenderBoundingBox();
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
	case MARIO_WORLD_STATE_UP:
		vy = -MARIO_WORLD_SPEED;
		vx = 0;
		break;
	case MARIO_WORLD_STATE_DOWN:
		vy = MARIO_WORLD_SPEED;
		vx = 0;
		break;
	case MARIO_WORLD_STATE_RIGHT:
		vy = 0;
		vx = MARIO_WORLD_SPEED;
		break;
	case MARIO_WORLD_STATE_LEFT:
		vy = 0;
		vx = -MARIO_WORLD_SPEED;
		break;
	case MARIO_WORLD_STATE_IDLE:
		vy = 0;
		vx = 0;
		break;
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
		isGoTop = true;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = false;
		break;
	}
	case DOOR_TYPE_YELLOW_CASTLE:
	{
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
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = false;
		break;
	}
	case DOOR_TYPE_1:
	{
		isGoTop = false;
		isGoLeft = false;
		isGoBottom = true;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_2:
	{
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = true;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_3:
	{
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_4:
	{
		isGoTop = false;
		isGoLeft = true;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_5:
	{
		isGoTop = true;
		isGoLeft = false;
		isGoBottom = false;
		isGoRight = true;
		break;
	}
	case DOOR_TYPE_6:
	{
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