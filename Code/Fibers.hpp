#pragma once
#include "Script.hpp"
#include <timeapi.h>

using FiberHandle = std::function<void()>;
	class FiberScript : public Script
	{
	public:
		explicit FiberScript() = default;
		~FiberScript() noexcept = default;
		bool IsInitialized() override;
		ScriptType GetType() override;
		void Initialize() override;
		void Destroy() override;
		void Tick() override;
		void Wait(DWORD ms);

		std::vector<FiberHandle>& getTasks()
		{
			return m_fiberTasks;
		}

		void addTask(FiberHandle handle)
		{
			m_fiberTasks.push_back(handle);
		}

	private:
		std::uint32_t m_wake_at{};
		bool m_Initialized{};
		void* m_script_fiber{};
		void* m_main_fiber{};
		std::vector<FiberHandle> m_fiberTasks;
	};

	inline std::shared_ptr<FiberScript> g_FiberScript;