#pragma once
#include "../Common.hpp"
#include "../Types.hpp"
#include "TextBox.hpp"
#include "AbstractSubmenu.hpp"

namespace Big::UserInterface
{
	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};

	enum class HeaderType : std::int32_t
	{
		YTD = 0,
		YTD2 = 1,
		YTD3 = 2,
		YTD4 = 3,
		YTD5 = 4,
		YTD6 = 5,
	};

	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;

		bool IsInBounds(Vector2 point)
		{
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);

			if (point.x > right || point.x < left)
				return false;
			if (point.y > top || point.y < bottom)
				return false;

			return true;
		}
	};

	class UIManager
	{
	public:
		explicit UIManager() = default;
		~UIManager() noexcept = default;
		UIManager(UIManager const&) = delete;
		UIManager(UIManager&&) = delete;
		UIManager& operator=(UIManager const&) = delete;
		UIManager& operator=(UIManager&&) = delete;

		template <typename SubmenuType, typename ...TArgs>
		void AddSubmenu(TArgs&&... args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}

		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto&& sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}

		void OnTick();
	public:
		std::mutex m_Mutex;

		bool ImGUIMode;
		bool m_Opened = false;
		bool m_MouseLocked = false;
		float m_PosX = 0.18f;
		float m_PosA = 0.21f;
		float m_PosB = 0.21f;
		float m_PosY = 0.02f;
		float m_Width = 0.22f;
		std::size_t m_OptionsPerPage = 14;
		bool m_Sounds = true;

		// Input
		std::int32_t m_OpenDelay = 200;
		std::int32_t m_BackDelay = 300;
		std::int32_t m_EnterDelay = 300;
		std::int32_t m_VerticalDelay = 120;
		std::int32_t m_HorizontalDelay = 120;


		//footheader

		float m_FooterHeaderHeight = 0.06f;
		float m_FooterHeaderSpriteSize = 0.025f;
		Color m_FooterHeaderBackgroundColor{ 30, 30, 30, 200 };
		Color m_FooterHeaderSpriteColor{ 255, 255, 255, 255 };

		// Header
		float m_HeaderHeight = 0.1f;
		bool m_HeaderText = true;
		float m_HeaderTextSize = 1.f;
		Font m_HeaderFont = Font::HouseScript;
		Color m_HeaderBackgroundColor{ 2, 130, 53, 255 };
		Color m_HeaderTextColor{ 255, 255, 255, 255 };
		HeaderType m_HeaderType = HeaderType::YTD;

		bool m_HeaderGradientTransparent = true;
		bool m_HeaderGradientFlip = false;
		float m_HeaderGradientStretch = 0.f;
		float m_HeaderGradientFiller = 0.f;
		Color m_HeaderGradientColorLeft{ 100, 134, 255, 255 };
		Color HeaderAnim = { 255, 255, 255, 255 };
		Color m_HeaderGradientColorRight{ 200, 94, 100, 255 };

		// Submenu bar/home
		float m_SubmenuBarHeight = 0.04f;
		float m_SubmenuBarTextSize = 0.4f;
		Font m_SubmenuBarFont = Font::ChaletLondon;
		float m_SubmenuBarPadding = 2.1f;
		Color m_SubmenuBarBackgroundColor{ 0, 0, 0, 220 };
		Color m_SubmenuBarTextColor{ 255, 255, 255, 255 };

		// Options/scroller
		float m_OptionHeight = 0.04f;
		float m_OptionTextSize = 0.32f;
		Font m_OptionFont = Font::ChaletLondon;
		float m_OptionPadding = 2.1f;
		Color m_OptionSelectedTextColor{ 0, 0, 0, 255 };
		Color m_OptionUnselectedTextColor{ 255, 255, 255, 255 };
		Color m_OptionSelectedBackgroundColor{ 255, 255, 255, 255 };
		Color m_OptionUnselectedBackgroundColor{ 0, 0, 0, 160 };
		Color m_ESPcolor{ 255, 0, 0, 255 };

		// Footer/bottom
		float m_FooterHeight = 0.03f;
		float m_FooterSpriteSize = 0.025f;
		Color m_FooterBackgroundColor{ 10, 10, 10, 200 };
		Color m_FooterSpriteColor{ 255, 255, 255, 255 };

		// Description 
		float m_DescriptionHeightPadding = 0.002f;
		float m_DescriptionHeight = 0.035f;
		float m_DescriptionTextSize = 0.27f;
		Font m_DescriptionFont = Font::ChaletLondon;
		Color m_DescriptionBackgroundColor{ 0, 0, 0, 120 };
		Color m_DescriptionTextColor{ 255, 255, 255, 255 };
		float m_DescriptionSpriteSize = 0.025f;
		float m_DescriptionPadding = 2.1f;
		Color m_DescriptionSpriteColor{ 255, 255, 255, 255 };
		bool m_OpenKeyPressed = false;
		bool m_clickkeypressed = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
		void CheckForInput();
		void HandleInput();
		void ResetInput();
		void DrawInfoTitle(std::string title);
		void DrawTextInfo(std::string text, RGBAF rgbaf, Vector2 position, Vector2 size, bool center, bool right);
		void AddInfoSprite(std::string left_text, const char* sprite);
		void AddInfo(std::string left_text, std::string right_text);
		float m_DrawBaseY{};
		void DrawHeader();
		void DrawSubmenuBar(AbstractSubmenu* sub);
		void DrawOption(AbstractOption* opt, bool selected);
		void DrawFooter();
		void DrawDescription();

		void DrawRect(float x, float y, float width, float height, Color color);
		void DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation);
		void DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		float GetTextHeight(Font font, float size);
		Vector2 GetSpriteScale(float size);

		bool IsMouseLocked();
		Rectangle GetMenuRect();
		Vector2 GetMousePos();

		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> m_SubmenuStack;
	};
}

namespace Big
{
	inline std::unique_ptr<UserInterface::UIManager> g_UiManager;
}
