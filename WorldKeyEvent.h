#pragma once

#include "Scene.h"

class CWorldKeyEvent : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CWorldKeyEvent(LPSCENE s) :CSceneKeyHandler(s) {};
};
