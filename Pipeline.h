#pragma once

//BBOX
#define PIPELINE_BBOX_WIDTH 31
#define PIPELINE_BBOX_HEIGHT 47

//DISTANCE
#define PIPELINE_DISTANCE_GREEN 4
#define PIPELINE_DISTANCE_RED 6

//ANIMATION
#define ID_ANI_PIPELINE 6000

//TYPE
#define PIPELINE_TYPE_SUMMON_GREEN_VFT_PLANT 1
#define PIPELINE_TYPE_SUMMON_RED_VFT_PLANT	2
#define PIPELINE_TYPE_SUMMON_PIRANHA_PLANT	3

#include "GameObject.h"
class CPipeline : public CGameObject
{
	int type;
public:
	CPipeline(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
		SummonVenusFireTrap();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SummonVenusFireTrap();
};

