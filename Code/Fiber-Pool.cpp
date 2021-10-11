#include "Fibers.hpp"
#include "Script.hpp"
#include <timeapi.h>
#include <Windows.h>
void FiberScript::Initialize()
{
	m_Initialized = true;
}
bool FiberScript::IsInitialized()
{
	return m_Initialized;
}
void FiberScript::Destroy()
{
	return;
}
ScriptType FiberScript::GetType()
{
	return ScriptType::Game;
}
void FiberScript::Tick()
{
	if (!m_main_fiber) //Main Script Fiber
		m_main_fiber = ConvertThreadToFiber(nullptr);

	if (!m_main_fiber) // Second Fiber Check -> Prevent Crash
		m_main_fiber = GetCurrentFiber();

	if (GetTickCount() < m_wake_at)
		return;

	if (!m_script_fiber)
	{
		m_script_fiber = CreateFiber(0, [](PVOID param)
		{
			try
			{
				while (1)
				{
					for (auto it = g_FiberScript->getTasks().begin(); it != g_FiberScript->getTasks().end();)
					{
						auto&& task = *it;

						std::invoke(task);
						it = g_FiberScript->getTasks().erase(it);
					}
					g_FiberScript->Wait(0);
				}
			}
			catch (...)
			{
				g_Logger->Info("Unable to start Fiber Script.");
			}

		}, nullptr);
	}
	SwitchToFiber(m_script_fiber);
}

void FiberScript::Wait(DWORD ms)
{

	m_wake_at = GetTickCount() + ms;
	SwitchToFiber(m_main_fiber);
}