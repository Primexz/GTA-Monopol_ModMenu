#include "Logger.hpp"
#include <core.h>
namespace Big
{

	std::string mono() {
		char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
		std::string x = "";
		int input[] = { 46, 67, 14, 67, 16, 67, 12 };
		for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
			if (input[i] == 0) x += 0x20;
			else x += charlist[input[i] - 1];
		}
		return x;
	}

	Logger::Logger()
	{
		try
		{
			m_FilePath.append(std::getenv("appdata"));
			m_FilePath.append(mono());
			if (!fs::exists(m_FilePath))
				fs::create_directory(m_FilePath);

			m_FilePath.append(fmt::format("{0}.log", mono().c_str()));
			if (fs::exists(m_FilePath))
			{
				fs::remove(m_FilePath);
			}
		}
		catch (fs::filesystem_error const&)
		{
		}
		if (!AttachConsole(GetCurrentProcessId()))
		{
			AllocConsole(); 
		}
		SetConsoleTitleW(GX_WIDE(ConsoleTitle));
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE + FOREGROUND_GREEN + FOREGROUND_RED);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
		m_Console.open("CONOUT$");
		m_Input.open("CONIN$");
		m_File.open(m_FilePath, std::ios_base::out | std::ios_base::app);
	}
	Logger::~Logger() noexcept
	{
		FreeConsole();
	}

	void Logger::Info(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_INTENSITY);
		std::va_list args{};
		va_start(args, format);
		Log("Info", format, args);
		va_end(args);
	}
	void Logger::Green(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		std::va_list args{};
		va_start(args, format);
		Log("SUCCESS", format, args);
		va_end(args);
	}

	void Logger::Red(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::va_list args{};
		va_start(args, format);
		Log("Info", format, args);
		va_end(args);
	}

	void Logger::LightBlue(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE + FOREGROUND_GREEN);
		std::va_list args{};
		va_start(args, format);
		Log("Info", format, args);
		va_end(args);
	}

	void Logger::Yellow(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED + FOREGROUND_GREEN + FOREGROUND_INTENSITY);
		std::va_list args{};
		va_start(args, format);
		Log("Info", format, args);
		va_end(args);
	}


	void Logger::Error(const char* format, ...)
	{
		std::va_list args{};
		va_start(args, format);
		Log("Error", format, args);
		va_end(args);
	}

	void Logger::Log(const char* type, const char* format, std::va_list args)
	{
		std::lock_guard lock(m_Mutex);

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		char prefix[64] = {};
		std::snprintf(prefix, sizeof(prefix) - 1, "[%02d:%02d:%02d] [%s] ", tm->tm_hour, tm->tm_min, tm->tm_sec, type);

		std::size_t messageLength = std::vsnprintf(nullptr, 0, format, args) + 1;
		auto messageBuffer = std::make_unique<char[]>(messageLength);

		std::uninitialized_fill_n(messageBuffer.get(), messageLength, '\0');
		std::vsnprintf(messageBuffer.get(), messageLength, format, args);

		m_File << prefix << messageBuffer.get() << std::endl;
		m_Console << prefix << messageBuffer.get() << std::endl;

		m_Messages.push_back(std::move(messageBuffer));
	}

	std::mutex& Logger::GetMutex()
	{
		return m_Mutex;
	}

	std::pair<std::unique_ptr<char[]>*, std::size_t> Logger::GetMessages()
	{
		return std::make_pair(m_Messages.data(), m_Messages.size());
	}

	std::istream& Logger::GetInput()
	{
		return m_Input;
	}
}
