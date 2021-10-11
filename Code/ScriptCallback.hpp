#pragma once
#include "Script.hpp"
#include "Natives.hpp"

namespace Big
{
	class AbstractCallback
	{
	public:
		virtual ~AbstractCallback() noexcept = default;
		AbstractCallback(AbstractCallback const&) = delete;
		AbstractCallback& operator=(AbstractCallback const&) = delete;
		AbstractCallback(AbstractCallback&&) = delete;
		AbstractCallback& operator=(AbstractCallback&&) = delete;

		virtual bool IsDone() = 0;
		virtual void OnSuccess() = 0;
		virtual void OnFailure() = 0;
	protected:
		AbstractCallback() = default;
	};

	class ModelCallback : public AbstractCallback
	{
	public:
		explicit ModelCallback(std::uint32_t model, std::function<void()> action):
			m_Model(model),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return STREAMING::HAS_MODEL_LOADED(m_Model);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			STREAMING::REQUEST_MODEL(m_Model);
		}
	private:
		std::uint32_t m_Model;
		std::function<void()> m_Action;
	};
	class WeaponModelCallback : public AbstractCallback
	{
	public:
		explicit WeaponModelCallback(std::uint32_t model, std::function<void()> action) :
			m_Model(model),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return WEAPON::HAS_WEAPON_ASSET_LOADED(m_Model);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			WEAPON::REQUEST_WEAPON_ASSET(m_Model, 31, 0);
		}
	private:
		std::uint32_t m_Model;
		std::function<void()> m_Action;
	};
	class DelayCallback : public AbstractCallback
	{
	public:
		explicit DelayCallback(std::uint32_t delay, std::function<void()> action) :
			m_StartTime(GetTickCount()),
			m_Delay(delay),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return (GetTickCount() - m_StartTime) >= m_Delay;
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
		}
	private:
		std::uint32_t m_StartTime;
		std::uint32_t m_Delay;
		std::function<void()> m_Action;
	};
	class KeyboardCallback : public AbstractCallback
	{
	public:
		explicit KeyboardCallback(std::string type, std::function<void()> action):
			m_type(type),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD();
		}

		void OnSuccess() override
		{
			if (m_type == "PLATES")
			{

				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
				{
				}
				char* name = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				Features::PlateEdit(name);
			}
			if (m_type == "NAME")
			{
				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
				{
				}
				char* name = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				Features::SetName(name);

			}
			if (m_type == "OUTFIT")
			{
				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
				{
				}
				char* name = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				Features::SaveOutfit(name);

			}
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
		}
	private:
		std::function<void()> m_Action;
		std::string m_type;
	};
	class CallbackScript : public Script
	{
	public:
		explicit CallbackScript() = default;
		~CallbackScript() noexcept = default;

		bool IsInitialized() override;
		ScriptType GetType() override;
		void Initialize() override;
		void Destroy() override;
		void Tick() override;

		template <typename CallbackType, typename ...TArgs>
		void AddCallback(TArgs&&... args)
		{
			m_Callbacks.push_back(std::make_unique<CallbackType>(std::forward<TArgs>(args)...));
		}
	private:
		bool m_Initialized{};
		std::vector<std::unique_ptr<AbstractCallback>> m_Callbacks;
	};

	class KeyBoardCallBack : public AbstractCallback
	{
	public:
		explicit KeyBoardCallBack(const char* title, int input, std::function<void()> action) :
			Title(Title),
			m_Action(std::move(action)),
			Input(input)
		{
		}

		bool IsDone() override
		{
			return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{

		}
	private:
		const char* Title;
		int Input;
		std::function<void()> m_Action;
	};

	inline std::shared_ptr<CallbackScript> g_CallbackScript;
}

class TextureCallback : public AbstractCallback
{
public:
	explicit TextureCallback(std::string dict, std::function<void()> action) :
		m_Texture(dict),
		m_Action(std::move(action))
	{
	}

	bool IsDone() override
	{
		return GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(m_Texture.c_str());
	}

	void OnSuccess() override
	{
		if (m_Action)
			std::invoke(m_Action);

	}

	void OnFailure() override
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(m_Texture.c_str(), false);
	}
private:
	std::string m_Texture;
	std::function<void()> m_Action;
};