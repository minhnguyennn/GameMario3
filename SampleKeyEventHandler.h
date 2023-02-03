#pragma once

#include "Scene.h"

#define	POSITION_BEGIN_MAP_X		16
#define	POSITION_BEGIN_MAP_Y		380

#define	POSITION_MIDDLE_MAP_X		1503
#define	POSITION_MIDDLE_MAP_Y		144

#define	POSITION_END_MAP_X			2600
#define	POSITION_END_MAP_Y			380

#define	POSITION_HIDDEN_MAP_X		3336
#define	POSITION_HIDDEN_MAP_Y		0

class CSampleKeyHandler: public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
