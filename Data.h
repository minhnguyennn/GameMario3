#pragma once

class CData
{
	static CData* __instance;
	bool isConvertBrick;
public:
	CData()
	{
		this->isConvertBrick = false;
	};
	void SetIsConvertBrick(bool isConvertBrick) { this->isConvertBrick = isConvertBrick; }
	bool GetIsConvertBrick() { return isConvertBrick; }

	static CData* GetInstance();
	~CData() {};
};