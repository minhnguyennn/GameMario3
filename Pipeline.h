#pragma once

#define PIPELINE_BBOX_WIDTH 29
#define PIPELINE_BBOX_HEIGHT 47

#define ID_ANI_PIPELINE 6000

#include "GameObject.h"
class CPipeline : public CGameObject
{
public:
	CPipeline(float x, float y) : CGameObject(x, y) {}
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SummonVenusFireTrap();
};

