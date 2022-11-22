#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "QuestionBrick.h"
#include "Animations.h"

//ANIMATION
#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_NO 10001
#define ID_ANI_BRICK_NULL 10001
#define ID_ANI_BUTTON_NOT_PRESSED 10002
#define ID_ANI_BUTTON_PRESSED 10003

//BBOX
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

//TYPE
#define BRICK_TYPE_BLOCK 1
#define BRICK_TYPE_NO_BLOCK 2

class CBrick : public CGameObject {
	int type;
public:
	CBrick(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; };
	int IsBlocking() { return 1; }
};