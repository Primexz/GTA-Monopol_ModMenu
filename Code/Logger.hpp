#pragma once

namespace Big
{
	class Logger
	{
	public:
		explicit Logger();
		~Logger() noexcept;

		Logger(Logger const&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(Logger const&) = delete;
		Logger& operator=(Logger&&) = delete;

		void Info(const char* format, ...);
		void Error(const char* format, ...);
		void Green(const char* format, ...);
		void Red(const char* format, ...);
		void LightBlue(const char* format, ...);
		void Yellow(const char* format, ...);
		void Log(const char* type, const char* format, std::va_list args);

		std::mutex& GetMutex();
		std::pair<std::unique_ptr<char[]>*, std::size_t> GetMessages();
		std::istream& GetInput();
	private:
		std::mutex m_Mutex;
		std::vector<std::unique_ptr<char[]>> m_Messages;

		fs::path m_FilePath;
		std::ofstream m_File;
		std::ofstream m_Console;
		std::ifstream m_Input;
	};

	inline std::unique_ptr<Logger> g_Logger;
}
