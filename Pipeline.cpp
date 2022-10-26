#include "Pipeline.h"
#include "debug.h"
#include "PlayScene.h"
#include "VenusFireTrap.h"

void CPipeline::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_PIPELINE)->Render(x, y);
	//RenderBoundingBox();
}

void CPipeline::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIPELINE_BBOX_WIDTH / 2;
	t = y - PIPELINE_BBOX_HEIGHT / 2;
	r = l + PIPELINE_BBOX_WIDTH;
	b = t + PIPELINE_BBOX_HEIGHT;
}

void CPipeline::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPipeline::SetState(int state) {
	
	CGameObject::SetState(state);
}

void CPipeline::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	float mario_x = mario->GetX();
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPipeline::SummonVenusFireTrap() {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CVenusFireTrap* vftrap = new CVenusFireTrap(x, y-6);
	scene->CreateObject(vftrap);
}



