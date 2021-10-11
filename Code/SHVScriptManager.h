#ifndef __SCRIPT_MANAGER_H__
#define __SCRIPT_MANAGER_H__

class SHVScript
{
public:

	inline SHVScript(void(*function)())
	{
		scriptFiber = nullptr;
		callbackFunction = function;
		wakeAt = timeGetTime();
	}

	inline ~SHVScript()
	{
		if (scriptFiber)
		{
			DeleteFiber(scriptFiber);
		}
	}

	void Tick();

	void Wait(uint32_t time);

	inline void(*GetCallbackFunction())()
	{
		return callbackFunction;
	}

private:

	HANDLE			scriptFiber;
	uint32_t		wakeAt;

	void			Run();
	void(*callbackFunction)();
};

typedef std::map<HMODULE, std::shared_ptr<SHVScript>> scriptMap;

class SHVScriptThread
{
private:

	scriptMap				m_scripts;

public:

	virtual void			DoRun();
	void					AddScript(HMODULE module, void(*fn)());
	void					RemoveScript(void(*fn)());
	void					RemoveScript(HMODULE module);
	void					RemoveAllScripts();
	size_t					ScriptCount();
};

typedef						void(*KeyboardHandler)(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);
typedef						void(*TWndProcFn)(UINT uMsg, WPARAM wParam, LPARAM lParam);
static						std::set<KeyboardHandler> g_keyboardFunctions;
static						std::set<TWndProcFn> g_WndProcCb;

namespace SHVScriptManager
{
	void					WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void					MainFiber();
	void					UnloadHook();
	void					Notification(const std::string& str);
}

extern SHVScriptThread	g_ScriptThread;
extern SHVScriptThread	g_AdditionalThread;

#endif // __SCRIPT_MANAGER_H__