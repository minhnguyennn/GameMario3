#pragma once
#include"GameObject.h"

//ANIMATION
#define ID_ANI_DOOR_SPECIAL	15009
#define ID_ANI_DOOR_START	15008
#define ID_ANI_DOOR_1		15002
#define ID_ANI_DOOR_2		15003
#define ID_ANI_DOOR_3		15004
#define ID_ANI_DOOR_4		15005
#define ID_ANI_DOOR_5		15006
#define ID_ANI_DOOR_6		15007

//TYPE
#define DOOR_TYPE_SPECIAL	10
#define DOOR_TYPE_START		0
#define DOOR_TYPE_1			1
#define DOOR_TYPE_2			2
#define DOOR_TYPE_3			3
#define DOOR_TYPE_4			4
#define DOOR_TYPE_5			5
#define DOOR_TYPE_6			6


class CDoor : public CGameObject
{
	int type;
public:
	CDoor(float x, float y, int type) : CGameObject(x, y) 
	{
		this->type = type;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};