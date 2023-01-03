#include "Data.h"
#include "debug.h"

CData* CData::__instance = NULL;

CData* CData::GetInstance()
{
	if (__instance == NULL) __instance = new CData();
	return __instance;
}