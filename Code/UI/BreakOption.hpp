#pragma once
#include "BaseOption.hpp"
#include "UIManager.hpp"
namespace Big::UserInterface
{
	class BreakOption : public BaseOption<BreakOption>
	{
	public:
		explicit BreakOption() = default;
		explicit BreakOption(const char* text, const char* description = nullptr, std::function<void()> action = [] {})
		{
			SetLeftText(((std::string)"~italic~[ " + text + " ]").c_str());
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Break)
			{
				return true;
			}

			return false;
		}
		~BreakOption() noexcept = default;
		BreakOption(BreakOption const&) = default;
		BreakOption& operator=(BreakOption const&) = default;
		BreakOption(BreakOption&&) = default;
		BreakOption& operator=(BreakOption&&) = default;
	};
}
