#pragma once

#include "GameObject.h"

//animation
#define ID_ANI_FLOWER_BOX 11200
#define ID_ANI_FLOWER_BOX_UP 11201
//bbox
#define FLOWER_BOX_BBOX_WIDTH 16
#define FLOWER_BOX_BBOX_HEIGHT 16
//state
#define FLOWER_BOX_STATE_UP	1
//property
#define	FLOWER_BOX_SPEED_Y	0.1f

class CFlowerBox : public CGameObject 
{
	bool isUp;
public:
	CFlowerBox(float x, float y) : CGameObject(x, y) 
	{
		isUp = false;
	}
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; };
};