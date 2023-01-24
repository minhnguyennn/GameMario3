#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include"Map.h"

#define DATA_ID_INTRO_SCENE 15

class CIntroScene : public CScene
{
protected:
	LPGAMEOBJECT player;
	vector<LPGAMEOBJECT> objects;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void LoadAssets(LPCWSTR assetFile);
public:
	CIntroScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	/*virtual void CreateObject(LPGAMEOBJECT gameobject)
	{
		objects.insert(objects.begin() + 1, gameobject);
	}*/
	LPGAMEOBJECT GetPlayer() { return player; }
	//vector<LPGAMEOBJECT> GetListObject() { return objects; }
	void Clear();
	void PurgeDeletedObjects();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CIntroScene* LPINTROSCENE;