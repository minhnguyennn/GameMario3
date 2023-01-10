#pragma once

class CData
{
	static CData* __instance;
	bool isConvertBrick;
	int card_box;
public:
	CData()
	{
		this->isConvertBrick = false;
		this->card_box = 0;
	};
	void SetIsConvertBrick(bool isConvertBrick) { this->isConvertBrick = isConvertBrick; }
	bool GetIsConvertBrick() { return isConvertBrick; }
	void SetCardBox(int card_box) { this->card_box = card_box; }
	int GetCardBox() { return card_box; }
	static CData* GetInstance();
	~CData() {};
};