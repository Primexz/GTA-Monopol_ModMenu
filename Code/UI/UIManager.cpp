#include "UIManager.hpp"
#include "../Timer.hpp"
#include "../Natives.hpp"
#include "BoolOption.hpp"
#include "../Functions.h"
#include "../LogScript.hpp"

namespace Big::UserInterface
{


	double opt_start = 0;
	double opt_end = 0;
	float scrollCurrent = 0;
	float scrollTarget = 0;
	double scroll_speed = 0.0625f;
	int currentOpacity;
	int targetOpacity;
	int currentSelected, fullAmount;

	double lerp(double start, double end, double amount) {
		return start * (1 - amount) + end * amount;
	}


	void UIManager::OnTick()
	{
		Big::UpdateNativeShit();
		Features::UpdatePerTick();
		Features::TimePD1 = timeGetTime();
		std::lock_guard lock(m_Mutex);


		if (scrollCurrent != scrollTarget) scrollCurrent = lerp(scrollCurrent, scrollTarget, scroll_speed);
		if ((scrollCurrent > scrollTarget - 0.0005) && (scrollCurrent < scrollTarget + 0.0005))
		{
			scrollCurrent = scrollTarget;
		}

		if (g_Settings.m_LockMouse)
		{
			if (!Features::EnableControlBypass)
			{
				CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
			}
			ShowCursor(true);
		}

		if (IsMouseLocked())
		{

			//CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
			ShowCursor(true);
			SetCursor(LoadCursorA(NULL, IDC_ARROW));
			if (GetMenuRect().IsInBounds(GetMousePos()))
			{
				//g_Logger->Info("");
			}
		}


		CheckForInput();
		HandleInput();

		if (m_Opened)
		{
			CONTROLS::DISABLE_CONTROL_ACTION(0, 27, true); // Disable phone
			m_DrawBaseY = m_PosY;
			DrawHeader();
			if (!m_SubmenuStack.empty())
			{
				auto sub = m_SubmenuStack.top();
				sub->Reset();
				sub->Execute();
				DrawSubmenuBar(sub);
				if (sub->GetNumOptions() != 0)
				{
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->GetNumOptions() > m_OptionsPerPage ? m_OptionsPerPage : sub->GetNumOptions();
					if (sub->GetNumOptions() > m_OptionsPerPage && sub->GetSelectedOption() >= m_OptionsPerPage)
					{
						startPoint = sub->GetSelectedOption() - m_OptionsPerPage + 1;
						endPoint = sub->GetSelectedOption() + 1;
					}
					float tmp_base = m_DrawBaseY;


					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						DrawOption(sub->GetOption(i), i == sub->GetSelectedOption());
					}
				}
			}
			DrawFooter();
			DrawDescription();
		}
	}
	std::pair<UINT16, UINT16> menubindsGamepad = { INPUT_FRONTEND_RB, INPUT_FRONTEND_LEFT };

	void UIManager::CheckForInput()
	{
		if (loggedin)
		{
			ResetInput();
			//if(m_Controller)
			//{
			//	UINT8 index1 = menubindsGamepad.first < 50 ? 0 : 2;
			//	UINT8 index2 = menubindsGamepad.second < 50 ? 0 : 2;
			//	m_OpenKeyPressed = IsKeyPressed(m_OpenKey) || IsKeyPressed(VK_MENU) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(index1, menubindsGamepad.first) && CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(index2, menubindsGamepad.second);
			//	m_BackKeyPressed = IsKeyPressed(m_BackKey) || IsKeyPressed(VK_BACK) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RRIGHT);
			//	m_EnterKeyPressed = IsKeyPressed(m_EnterKey) || IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_ACCEPT);
			//	m_UpKeyPressed = IsKeyPressed(m_UpKey) || IsKeyPressed(VK_UP) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_UP);
			//	m_DownKeyPressed = IsKeyPressed(m_DownKey) || IsKeyPressed(VK_DOWN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_DOWN);
			//	m_LeftKeyPressed = IsKeyPressed(m_LeftKey) || IsKeyPressed(VK_LEFT) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_LEFT);
			//	m_RightKeyPressed = IsKeyPressed(m_RightKey) || IsKeyPressed(VK_RIGHT) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RIGHT);
			//}
			//else
			//{
				//m_OpenKeyPressed = IsKeyPressed(m_OpenKey) || IsKeyPressed(VK_F12);


				m_clickkeypressed = IsKeyPressed(m_OpenKey) || IsKeyPressed(VK_F8) || IsKeyPressed(VK_MENU);


				//m_BackKeyPressed = IsKeyPressed(m_BackKey) || IsKeyPressed(VK_BACK);
				//m_EnterKeyPressed = IsKeyPressed(m_EnterKey) || IsKeyPressed(VK_RETURN);
				//m_UpKeyPressed = IsKeyPressed(m_UpKey) || IsKeyPressed(VK_UP);
				//m_DownKeyPressed = IsKeyPressed(m_DownKey) || IsKeyPressed(VK_DOWN);
				//m_LeftKeyPressed = IsKeyPressed(m_LeftKey) || IsKeyPressed(VK_LEFT);
				//m_RightKeyPressed = IsKeyPressed(m_RightKey) || IsKeyPressed(VK_RIGHT);
			//}
		}
	}
	void UIManager::HandleInput()
	{
		static auto openTicker = GetTickCount();
		if (m_OpenKeyPressed && GetTickCount() - openTicker >= static_cast<std::uint32_t>(m_OpenDelay))
		{
			openTicker = GetTickCount();
			m_Opened ^= true;

			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		}

		if (m_clickkeypressed && GetTickCount() - openTicker >= static_cast<std::uint32_t>(m_OpenDelay))
		{
			openTicker = GetTickCount();
			ImGUIMode ^= true;

			g_Settings.m_LockMouse ^= true;


			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

		}

		static Timer backTimer(0ms);
		backTimer.SetDelay(std::chrono::milliseconds(m_BackDelay));
		if (m_Opened && m_BackKeyPressed && backTimer.Update())
		{
			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

			if (m_SubmenuStack.size() <= 1)
			{
				m_Opened = false;
			}
			else
			{
				m_SubmenuStack.pop();
			}
		}

		if (m_Opened && !m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();

			static Timer enterTimer(0ms);
			enterTimer.SetDelay(std::chrono::milliseconds(m_EnterDelay));
			if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::EnterPress);
				}
			}

			static Timer upTimer(0ms);
			upTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollBackward();
			}

			static Timer downTimer(0ms);
			downTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollForward();
			}

			static Timer leftTimer(0ms);
			leftTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::LeftPress);
				}
			}

			static Timer rightTimer(0ms);
			rightTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::RightPress);
				}
			}
		}
	}

	void UIManager::ResetInput()
	{
		m_OpenKeyPressed = false;
		m_BackKeyPressed = false;
		m_EnterKeyPressed = false;
		m_UpKeyPressed = false;
		m_DownKeyPressed = false;
		m_LeftKeyPressed = false;
		m_RightKeyPressed = false;
	}
	Color color{ 255, 255, 255, 255 };

	bool FileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}


	void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
		}
	}


	int frameID;
	bool loaded = 0;
	bool m_Scrollbar = true;
	float m_scrollbarWidthIndex = 0.05f;
	int id = 1;
	int customtimer;
	std::string pic_id;
	int numofframes = 271;
	void UIManager::DrawHeader()
	{
		switch (m_HeaderType)
		{
		case HeaderType::YTD:

				//DrawSprite(
				//	"Main",
				//	Features::HeaderImage ? "HEADER1" : "HEADER1",
				//	m_PosX - (m_HeaderGradientStretch / 2.f),
				//	m_DrawBaseY + (m_HeaderHeight / 2.f),
				//	m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
				//	m_HeaderHeight,
				//	color,
				//	0);
				if ((timeGetTime() - customtimer) > 20) //20 is the delay between frames in ms
				{
					if (id < numofframes) id++;
					else id = 0; // if we're at the last frame we jump to the start

					if (id < 10) {
						pic_id = "116548-min-" + std::to_string(id);
					}
					else if (id < 100) {
						pic_id = "116548-min-" + std::to_string(id);
					}
					else {
						pic_id = "116548-min-" + std::to_string(id);
					}

					customtimer = timeGetTime(); //reset the timer for next frame we display
				}

				if (id <= 111)
				{
					Spriter("Header1", pic_id, m_PosX - (m_HeaderGradientStretch / 2.f), m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller, m_HeaderHeight, 0, HeaderAnim.r, HeaderAnim.g, HeaderAnim.g, HeaderAnim.a);
				}
				else if (id > 111 && id <= 209)
				{
					Spriter("Header2", pic_id, m_PosX - (m_HeaderGradientStretch / 2.f), m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller, m_HeaderHeight, 0, HeaderAnim.r, HeaderAnim.g, HeaderAnim.g, HeaderAnim.a);
				}
				else
				{
					Spriter("Header3", pic_id, m_PosX - (m_HeaderGradientStretch / 2.f), m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller, m_HeaderHeight, 0, HeaderAnim.r, HeaderAnim.g, HeaderAnim.g, HeaderAnim.a);
				}

	
			break;
		case HeaderType::YTD2:

				DrawSprite(
					"Main",
					Features::HeaderImage ? "HEADER2" : "HEADER2",
					m_PosX - (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					color,
					0);

			break;
		case HeaderType::YTD3:
	
				DrawSprite(
					"Main",
					Features::HeaderImage ? "HEADER3" : "HEADER3",
					m_PosX - (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					color,
					0);
	
			break;
		case HeaderType::YTD4:
	
				DrawSprite(
					"Main",
					Features::HeaderImage ? "HEADER4" : "HEADER4",
					m_PosX - (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					color,
					0);

			break;
		case HeaderType::YTD5:

				DrawSprite(
					"Main",
					Features::HeaderImage ? "HEADER5" : "HEADER5",
					m_PosX - (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					color,
					0);

			break;
		case HeaderType::YTD6:

				DrawSprite(
					"Main",
					Features::HeaderImage ? "HEADER6" : "HEADER6",
					m_PosX - (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					color,
					0);

			break;

			break;
			if (m_HeaderText)
			{
				//DrawCenteredText(
				//	GX_NAME,
				//	m_PosX,
				//	m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
				//	m_HeaderTextSize,
				//	m_HeaderFont,
				//	m_HeaderTextColor,
				//	false, true);
			}

		}

		m_DrawBaseY += m_HeaderHeight;
	}

	void UIManager::DrawSubmenuBar(AbstractSubmenu* sub)
	{
		char leftText[64] = {};
		std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
		//std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>(toupper(c)); });

		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());
		//scrollbar arrow
		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f),
			m_Width, m_SubmenuBarHeight,
			m_SubmenuBarBackgroundColor);
		DrawLeftText(
			&leftText[0],
			m_PosX - (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);
		DrawRightText(
			&rightText[0],
			m_PosX + (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);

		m_DrawBaseY += m_SubmenuBarHeight;
	}

	void UIManager::DrawOption(AbstractOption* opt, bool selected)
	{
		auto sub = m_SubmenuStack.top();
		int Test420 = sub->GetSelectedOption();
		int Test69 = sub->GetNumOptions();






		if (m_Scrollbar)
		{
			m_scrollbarWidthIndex = (m_Width / 2) + 0.01f;
			if (!selected) { DrawRect(m_PosX - m_scrollbarWidthIndex, m_DrawBaseY + (m_OptionHeight / 2.f), 0.008f, m_OptionHeight, m_OptionUnselectedBackgroundColor); }
			if (sub->GetNumOptions() < 17)
			{
				if (selected) { DrawRect(m_PosX - m_scrollbarWidthIndex, m_DrawBaseY + (m_OptionHeight / 2.f), 0.008f, m_OptionHeight, m_OptionSelectedBackgroundColor); }
			}
			else
			{
				if (selected) { DrawRect(m_PosX - m_scrollbarWidthIndex, m_DrawBaseY + (m_OptionHeight / 2.f), 0.008f, m_OptionHeight, m_OptionUnselectedBackgroundColor); }
				GRAPHICS::DRAW_RECT(m_PosX - m_scrollbarWidthIndex, ((((sub->GetSelectedOption() * (m_OptionsPerPage * m_OptionHeight - 0.012f)) / sub->GetNumOptions()))) + m_PosY + 0.138f, 0.008f, 0.035f, m_OptionSelectedBackgroundColor.r, m_OptionSelectedBackgroundColor.g, m_OptionSelectedBackgroundColor.b, 255);  //The blue ting
			}
		}


		if (selected == true)
		{
			DrawRect(
				m_PosX,
				m_DrawBaseY + (m_OptionHeight / 2.f),
				m_Width,
				m_OptionHeight,
				m_OptionUnselectedBackgroundColor);
			DrawSprite(
				"Main",
				"scroll",
				m_PosX,
				m_DrawBaseY + (m_OptionHeight / 2.f),
				m_Width,
				m_OptionHeight,
				m_OptionSelectedBackgroundColor,
				0);
			//DrawRect(
				//m_PosX - m_scrollbarWidthIndex,
				//m_DrawBaseY + (m_OptionHeight / 2.f),
				//0.01f,
				//m_OptionHeight,
				//m_OptionSelectedBackgroundColor
			//);

		}
		else if (selected == false)
		{
			DrawRect(
				m_PosX,
				m_DrawBaseY + (m_OptionHeight / 2.f),
				m_Width,
				m_OptionHeight,
				m_OptionUnselectedBackgroundColor);
			//DrawRect(
				//m_PosX - m_scrollbarWidthIndex,
				//m_DrawBaseY + (m_OptionHeight / 2.f),
				//0.01f,
				//m_OptionHeight,
				//m_OptionUnselectedBackgroundColor
			//);
		}
		DrawLeftText(
			opt->GetLeftText(),
			m_PosX - (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);
		if (opt->GetFlag(OptionFlag::BoolOption))
		{
			auto res = GetSpriteScale(0.045f);
			if (Features::ToggledOn)
			{
				GRAPHICS::DRAW_SPRITE("Main", "on",
					g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.01f)
					, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
						, g_UiManager->m_OptionTextSize) / 1.9f) + 0.010f
					, res.x, 0.045, 0.0, 255, 255, 255, 255);
			}
			else if (!Features::ToggledOn)
			{
				GRAPHICS::DRAW_SPRITE("Main", "off",
					g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.01f)
					, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
						, g_UiManager->m_OptionTextSize) / 1.9f) + 0.010f
					, res.x, 0.045, 0.0, 255, 255, 255, 255);
			}
		}
		DrawRightText(
			opt->GetRightText(),
			m_PosX + (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);
		if (opt->GetFlag(OptionFlag::Enterable))
		{
			DrawRightText(
				">",
				m_PosX + (m_Width / m_OptionPadding - 0.006),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f),
				m_OptionTextSize,
				Font::Monospace,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false);
		}

		m_DrawBaseY += m_OptionHeight;
	}

	void UIManager::DrawFooter()
	{

		auto spriteSize = GetSpriteScale(m_DescriptionSpriteSize);


		/*		DrawLeftText(
					"Rekt",
					m_PosX - (m_Width / m_DescriptionPadding) + (spriteSize.x * 15.4f),
					m_DrawBaseY + (m_DescriptionHeight / 2.f) - (GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f),
					m_DescriptionTextSize,
					m_DescriptionFont,
					m_DescriptionTextColor,
					false, false);*/


		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_FooterHeight / 2.f),
			m_Width,
			m_FooterHeight,
			m_FooterBackgroundColor);

		float size = m_FooterSpriteSize;
		float rotation = 0.f;
		const char* texture = "shop_arrows_upanddown";

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetSelectedOption() == 0)
			{
				rotation = 90.f;
				texture = "arrowright";
				size *= 0.8f;
			}
			else if (sub->GetSelectedOption() + 1 == sub->GetNumOptions())
			{
				rotation = 270.f;
				texture = "arrowright";
				size *= 0.8f;
			}
		}

		auto sizee = GetSpriteScale(size);

		DrawSprite(
			"commonmenu",
			texture,
			m_PosX,
			m_DrawBaseY + (m_FooterHeight / 2.f),
			sizee.x,
			sizee.y,
			m_FooterSpriteColor,
			rotation);

		m_DrawBaseY += m_FooterHeight;

	}

	void UIManager::DrawDescription()
	{
		const char* description{};

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetNumOptions())
			{
				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					description = opt->GetDescription();
				}
			}
		}

		if (!description || !*description)
			return;

		m_DrawBaseY += m_DescriptionHeightPadding;

		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_DescriptionHeight / 2.f),
			m_Width,
			m_DescriptionHeight,
			m_DescriptionBackgroundColor);

		auto spriteSize = GetSpriteScale(m_DescriptionSpriteSize);
		DrawSprite(
			"shared", "info_icon_32",
			m_PosX - (m_Width / m_DescriptionPadding) + (spriteSize.x / 2.f),
			m_DrawBaseY + (m_DescriptionHeight / 2.f),
			spriteSize.x,
			spriteSize.y,
			m_DescriptionSpriteColor,
			0.f
		);

		DrawLeftText(
			description,
			m_PosX - (m_Width / m_DescriptionPadding) + (spriteSize.x * 1.15f),
			m_DrawBaseY + (m_DescriptionHeight / 2.f) - (GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f),
			m_DescriptionTextSize,
			m_DescriptionFont,
			m_DescriptionTextColor,
			false, false
		);

		m_DrawBaseY += m_DescriptionHeight;
	}

	void UIManager::DrawRect(float x, float y, float width, float height, Color color)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a);
	}

	void UIManager::DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
		{
			GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a);
		}
		else
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
		}
	}

	void UIManager::DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		UI::SET_TEXT_SCALE(size, size);
		UI::SET_TEXT_FONT(static_cast<int>(font));
		UI::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			UI::SET_TEXT_OUTLINE();
		if (shadow)
			UI::SET_TEXT_DROP_SHADOW();

		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
	}

	void UIManager::DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		UI::SET_TEXT_CENTRE(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void UIManager::DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		UI::SET_TEXT_WRAP(0.f, x);
		UI::SET_TEXT_RIGHT_JUSTIFY(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	float UIManager::GetTextHeight(Font font, float size)
	{
		return UI::_GET_TEXT_SCALE_HEIGHT(size, static_cast<int>(font));
	}

	Vector2 UIManager::GetSpriteScale(float size)
	{
		int x;
		int y;
		GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}

	bool UIManager::IsMouseLocked()
	{
		return m_Opened && m_MouseLocked;
	}

	Rectangle UIManager::GetMenuRect()
	{
		float height = m_HeaderHeight;
		height += m_SubmenuBarHeight;

		if (!m_SubmenuStack.empty())
		{
			height += m_OptionHeight * std::min(m_SubmenuStack.top()->GetNumOptions(), m_OptionsPerPage);
		}

		height += m_FooterHeight;

		return
		{
			{ m_PosX + (m_Width / 2.f), m_PosY + (height / 2.f) },
			{ m_Width, height }
		};
	}

	Vector2 UIManager::GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);

		return Vector2{ static_cast<float>(point.x), static_cast<float>(point.y) };
	}
	void UIManager::DrawTextInfo(std::string text, RGBAF rgbaf, Vector2 position, Vector2 size, bool center, bool right)
	{



		UI::SET_TEXT_RIGHT_JUSTIFY(right);
		UI::SET_TEXT_CENTRE(center);
		UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		UI::SET_TEXT_FONT(rgbaf.f);
		UI::SET_TEXT_SCALE(size.x, size.y);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);



	}
	float x_pos{};
	float current_y_pos{};

	void UIManager::DrawInfoTitle(std::string title)
	{
		if (m_PosX > 0.482f)
			x_pos = m_PosX - m_PosB;
		else
			x_pos = m_PosX + m_PosA;

		DrawSprite("commonmenu", "interaction_bgd", x_pos, m_PosY + 0.05f, 0.17f, 0.1f, { 0, 0, 0, 150 }, 0.f);
		DrawTextInfo(title, { 255, 255, 255, 255, 1 }, { x_pos, m_PosY + 0.025f }, GetSpriteScale(0.70f), true, false);

		current_y_pos = m_PosY + 0.0492f;
	}
	void UIManager::AddInfoSprite(std::string left_text, const char* sprite)
	{
		DrawRect(x_pos, current_y_pos + 0.068f, 0.17f, 0.035f, { 0, 0, 0, 100 });

		DrawTextInfo(left_text + ":", { 255,255,255,255 }, { x_pos - 0.08f, current_y_pos + 0.0605f }, GetSpriteScale(0.25f), 0, 0);

		UI::SET_TEXT_WRAP(0.f, x_pos + 0.08f);

		DrawSprite(sprite, sprite, x_pos + 0.07f, current_y_pos + 0.070f, 0.018f, 0.025f, { 255, 255, 255, 255 }, 0.f);

		current_y_pos += 0.028f;
	}
	void UIManager::AddInfo(std::string left_text, std::string right_text)
	{
		DrawRect(x_pos, current_y_pos + 0.072f, 0.17f, 0.030f, { 0, 0, 0, 100 });

		DrawTextInfo(left_text + ":", { 255,255,255,255 }, { x_pos - 0.08f, current_y_pos + 0.06f }, GetSpriteScale(0.25f), 0, 0);

		UI::SET_TEXT_WRAP(0.f, x_pos + 0.08f);

		DrawTextInfo(right_text, { 255,255,255,255 }, { x_pos + 0.08f, current_y_pos + 0.06f }, GetSpriteScale(0.25f), false, true);

		current_y_pos += 0.030f;
	}
}