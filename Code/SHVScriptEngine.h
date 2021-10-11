#ifndef __SCRIPT_ENGINE_H__
#define __SCRIPT_ENGINE_H__


class ScriptEngine
{
public:

	static bool Initialize();


	static PUINT64 getGlobal(int globalId);

	static uint32_t* GetGameState();

	static int RegisterFile(const std::string& fullPath, const std::string& fileName);
};

#endif // __SCRIPT_ENGINE_H__