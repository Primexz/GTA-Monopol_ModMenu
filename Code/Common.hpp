#pragma once
#undef _HAS_STD_BYTE
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#include <winsdkver.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <sdkddkver.h>
#include <windows.h>
#include <winternl.h>
#include <d3d11.h>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Encryptor.h"
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <Psapi.h>
#include <timeapi.h>
#include <time.h>
#include <xstring>
#include <functional>
#include <cassert>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>
#pragma comment(lib, "ws2_32.lib")

// Windows Header Files:
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <Psapi.h>
#include <intrin.h>
#include <timeapi.h>
#include <time.h>
#include <xstring>
#include <functional>
//#include <experimental/filesystem>
//#pragma comment(lib, "discord-rpc.lib")

#define GX_WIDE_IMPL(str) L ## str
#define GX_WIDE(str) GX_WIDE_IMPL(str)
#define ConsoleTitle "Grand Theft Auto V"
#define GX_STRINGIZE_IMPL(x) #x
#define GX_STRINGIZE(x) GX_STRINGIZE_IMPL(x)


namespace Big
{
	using namespace std::chrono_literals;
	namespace fs = std::filesystem;

	inline HMODULE g_Module{};
	inline std::atomic_bool g_Running = true;

	inline std::uint32_t g_SelectedPlayer{};
}

#include "Settings.hpp"
#include "Logger.hpp"
#include "Util.hpp"
#include "NativeMemory.h"
#include "Memory.hpp"
#include "Game.hpp"
#include "ScriptGlobal.hpp"
#include "Features.h"
#include "Functions.h"
#include "enums.h"
using namespace std;
class Ini
{
private:
	std::string inifile;
public:
	Ini(std::string file)
	{
		this->inifile = file;
	}

	void WriteString(std::string string, std::string app, std::string key)
	{
		WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), this->inifile.c_str());
	}
	std::string GetString(std::string app, std::string key)
	{
		char buf[100];
		GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, this->inifile.c_str());
		return (std::string)buf;
	}

	void WriteInt(int value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	int GetInt(std::string app, std::string key)
	{
		int iResult = GetPrivateProfileInt(app.c_str(), key.c_str(), 90210, this->inifile.c_str());
		return iResult;
	}

	void WriteFloat(float value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	float GetFloat(std::string app, std::string key)
	{
		return std::stof(GetString(app, key));
	}
};
class globalHandle
{
private:
	void* _handle;

public:
	globalHandle(int index)
		//: _handle(&Big::g_GameVariables->m_globalPtr[index >> 18 & 0x3F][index & 0x3FFFF])
		: _handle(&Big::g_GameVariables->m_globalPtr[index >> 0x12 & 0x3F][index & 0x3FFFF])
	{ }

	globalHandle(void* p)
		: _handle(p)
	{ }

	globalHandle(const globalHandle& copy)
		: _handle(copy._handle)
	{ }

	globalHandle At(int index)
	{
		return globalHandle(reinterpret_cast<void**>(this->_handle) + (index));
	}

	globalHandle At(int index, int size)
	{
		// Position 0 = Array Size
		return this->At(1 + (index * size));
	}

	template <typename T>
	T* Get()
	{
		return reinterpret_cast<T*>(this->_handle);
	}

	template <typename T>
	T& As()
	{
		return *this->Get<T>();
	}
};
