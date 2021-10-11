#ifndef __GENERAL_H__
#define __GENERAL_H__

#ifndef doOnce
#define doOnce(...)			\
    do {					\
        static int once;	\
        if (!once)			\
		{					\
            ++once;			\
            __VA_ARGS__;	\
        }					\
    } while (0)
#endif

namespace Utility
{
	/* String */
	std::wstring str_to_wstr(const std::string& string);
	std::string wstr_to_str(const std::wstring& wstring);

	/* Hash */
	constexpr unsigned char ToLowerLookupTable[256] =
	{
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
		0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
		0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x5B, 0x2F, 0x5D, 0x5E, 0x5F,
		0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
		0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
		0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
		0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
		0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
		0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
		0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
		0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
		0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
		0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
	};

	constexpr std::uint32_t joaatc(const char* string, std::size_t length)
	{
		std::uint32_t hash = 0;

		for (std::size_t i = 0; i < length; ++i)
		{
			hash = static_cast<std::uint64_t>(hash) + ToLowerLookupTable[string[i]];
			hash = static_cast<std::uint64_t>(hash) + (hash << 10);
			hash = static_cast<std::uint64_t>(hash) ^ (hash >> 6);
		}

		hash = static_cast<std::uint64_t>(hash) + (hash << 3);
		hash = static_cast<std::uint64_t>(hash) ^ (hash >> 11);
		hash = static_cast<std::uint64_t>(hash) + (hash << 15);

		return hash;
	}

	std::uint32_t joaat(const char* string);
	std::uint32_t joaat(const std::string& string);

	/* File / Folder */
	bool				DoesFileExist(const char* name);
	const std::string	GetModuleFolder(HMODULE module, bool fullPath = false);
	const std::string	GetNamedModuleFolder(const std::string& name, bool fullPath = false);
	const std::string	GetRunningExecutableFolder();
	const std::string	GetOurModuleFolder();

	/* Module / Process Related */
	void				SetOurModuleHandle(const HMODULE module);
	const HMODULE		GetOurModuleHandle();

	const std::string	GetModuleName(const HMODULE module);
	const std::string	GetModuleNameWithoutExtension(const HMODULE module);

	bool				GetProcess(const std::string& filename, HANDLE& handle);
	DWORD				GetProcessID(const std::string& processName);
	HANDLE				StartProcessPaused(LPCTSTR lpApplicationName, PHANDLE ptr_thread);
	void				StartProcess(LPCTSTR lpApplicationName);
	void				killProcessByName(const char *filename);
	bool				CreateElevatedThread(LPTHREAD_START_ROUTINE thread);
	bool				SetPrivilege(const char * szPrivilege, bool bState = true);
	bool				Is64BitProcess(HANDLE hProc);

	/* General Misc */
	template <typename T>
	inline void SafeRelease(T *&p)
	{
		if (nullptr != p)
		{
			p->Release();
			p = nullptr;
		}
	}

	template <typename Container, typename Element>
	bool DoesVectorContain(const Container& container, const Element& element)
	{
		return std::find(std::begin(container), std::end(container), element) != std::end(container);
	}

	template<class T1, class T2>
	bool GetMapValue(const std::map<T1, T2>& input, T1 key, T2& out)
	{
		auto foundIter = input.find(key);
		if (foundIter != input.end())
		{
			out = foundIter->second;
			return true;
		}
		return false;
	}

	template<class T1, class T2>
	bool GetMapValue(const std::unordered_map<T1, T2>& input, T1 key, T2& out)
	{
		auto foundIter = input.find(key);
		if (foundIter != input.end())
		{
			out = foundIter->second;
			return true;
		}
		return false;
	}

	void playwindowsSound(const char* sound);
}

constexpr std::uint32_t operator""_joaat(const char* string, std::size_t length)
{
	return Utility::joaatc(string, length);
}
#define FMT(fmt, ...) (false ? std::to_string(printf(fmt, ##__VA_ARGS__)) : string_format(fmt, ##__VA_ARGS__ ))
template <typename T> T process_arg(T value) noexcept { return value; }
template <typename T> T const * process_arg(std::basic_string<T> const & value) noexcept { return value.c_str(); }
template <typename ... Args> std::string string_format(const std::string& format, Args const & ... args) {

	const auto fmt = format.c_str();
	const auto size = std::snprintf(nullptr, 0, fmt, process_arg(args) ...) + 1;
	auto buf = std::make_unique<char[]>(size);
	std::snprintf(buf.get(), size, fmt, process_arg(args) ...);
	return std::string(buf.get(), buf.get() + size - 1);
}
#endif // __GENERAL_H__