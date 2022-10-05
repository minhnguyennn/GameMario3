#pragma once
#define QUESIONBRICK_BBOX_WIDTH 16
#define QUESIONBRICK_BBOX_HEIGHT 16
#define ID_ANI_QUESTIONBRICK 10100
#include "GameObject.h"
class CQuestionBrick : public CGameObject
{
public:
	CQuestionBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

