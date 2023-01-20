#pragma once
#include"GameObject.h"

//BBOX
#define DOOR_BBOX_WIDTH 5
#define DOOR_BBOX_HEIGHT 5

//ANIMATION
#define ID_ANI_DOOR_SPECIAL	15009
#define ID_ANI_DOOR_START	15010
#define ID_ANI_DOOR_1		15002
#define ID_ANI_DOOR_2		15003
#define ID_ANI_DOOR_3		15004
#define ID_ANI_DOOR_4		15005
#define ID_ANI_DOOR_5		15006
#define ID_ANI_DOOR_6		15007
#define ID_ANI_YELLOW_NODE	15011

//TYPE
#define DOOR_TYPE_SPECIAL	10
#define DOOR_TYPE_START		0
#define DOOR_TYPE_1			1
#define DOOR_TYPE_2			2
#define DOOR_TYPE_3			3
#define DOOR_TYPE_4			4
#define DOOR_TYPE_5			5
#define DOOR_TYPE_6			6
#define DOOR_TYPE_YELLOW_1	7
#define DOOR_TYPE_YELLOW_2	8
#define DOOR_TYPE_YELLOW_3				9
#define DOOR_TYPE_YELLOW_MUSHROOM_1		11
#define DOOR_TYPE_YELLOW_4				12

#define DOOR_TYPE_YELLOW_CASTLE			14
#define DOOR_TYPE_YELLOW_5				15
#define DOOR_TYPE_YELLOW_6				16
#define DOOR_TYPE_YELLOW_7				17
#define DOOR_TYPE_YELLOW_8				18
#define DOOR_TYPE_YELLOW_MUSHROOM_2		19
#define DOOR_TYPE_YELLOW_9				20
#define DOOR_TYPE_BIG_CASTLE			21

//TIME
#define MARIO_WORLD_IDLE_TIMEOUT	50

class CDoor : public CGameObject
{
	int type;
	ULONGLONG time_mario_idle;
	bool isMarioIdle;
public:
	CDoor(float x, float y, int type) : CGameObject(x, y) 
	{
		this->type = type;
		time_mario_idle = 0;
		isMarioIdle = false;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable(){ return 1; }
	int IsBlocking() { return 0; }
	void SetType(int type) { this->type = type; }
	int GetType() { return type; }
	void SetIsMarioIdle(bool isMarioIdle) 
	{ 
		this->isMarioIdle = isMarioIdle; 
		time_mario_idle = GetTickCount64(); 
	}
	bool GetIsMarioIdle() { return isMarioIdle; }
};