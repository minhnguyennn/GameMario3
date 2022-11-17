#include "Pipeline.h"
#include "debug.h"
#include "PlayScene.h"
#include "VenusFireTrap.h"

void CPipeline::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_PIPELINE)->Render(x, y);
	RenderBoundingBox();
}

void CPipeline::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIPELINE_BBOX_WIDTH / 2;
	t = y - PIPELINE_BBOX_HEIGHT / 2;
	r = l + PIPELINE_BBOX_WIDTH;
	b = t + PIPELINE_BBOX_HEIGHT;
}


void CPipeline::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPipeline::SummonVenusFireTrap() {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	
	if (type == 1) {
		CVenusFireTrap* vft_green = new CVenusFireTrap(x, y - PIPELINE_DISTANCE_GREEN, VFTRAP_TYPE_GREEN);
		scene->CreateObject(vft_green);
	}
	else if (type == 2) {
		CVenusFireTrap* vft_red = new CVenusFireTrap(x, y - PIPELINE_DISTANCE_RED, VFTRAP_TYPE_RED);
		scene->CreateObject(vft_red);
	}
	
}



