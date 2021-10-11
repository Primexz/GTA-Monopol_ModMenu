#include "SHVScriptEngine.h"
#include "SHVScriptManager.h"
#include "SHVUtility.h"
#include "SHVASILoader.h"
#include "enums.h"
#include "Functions.h"
struct GlobalTable
{
	PINT64* GlobalBasePtr;
	PINT64 AddressOf(int index) const { return &GlobalBasePtr[index >> 18 & 0x3F][index & 0x3FFFF]; }
	bool IsInitialised()const { return *GlobalBasePtr; }
};

GlobalTable		globalTable;
eGameState* gameState;
eHookState		g_HookState;
int				g_GameVersion;
bool			g_IsRetail;

bool ScriptEngine::Initialize()
{
	g_HookState = HookStateRunning;
	return true;
}

uint32_t* ScriptEngine::GetGameState()
{
	return g_GameVariables->m_GameState;
}

PUINT64 ScriptEngine::getGlobal(int globalId)
{
	return reinterpret_cast<PUINT64>(globalTable.AddressOf(globalId));
}
