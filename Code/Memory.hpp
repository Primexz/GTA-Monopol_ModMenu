#pragma once
#include "core.h"
namespace Big
{
	class MemoryHandle
	{
	public:
		 MemoryHandle(void* p = nullptr) :
			m_Ptr(p)
		{}

		 explicit MemoryHandle(std::uintptr_t p) :
			m_Ptr(reinterpret_cast<void*>(p))
		{}

		template <typename T>
		 std::enable_if_t<std::is_pointer_v<T>, T> As()
		{
			return static_cast<T>(m_Ptr);
		}

		template <typename T>
		 std::enable_if_t<std::is_lvalue_reference_v<T>, T> As()
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_Ptr);
		}

		template <typename T>
		 std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> As()
		{
			return reinterpret_cast<T>(m_Ptr);
		}

		template <typename T>
		 MemoryHandle Add(T offset)
		{
			return MemoryHandle(As<std::uintptr_t>() + offset);
		}

		template <typename T>
		 MemoryHandle Sub(T offset)
		{
			return MemoryHandle(As<std::uintptr_t>() - offset);
		}

		 MemoryHandle Rip()
		{
			if (!m_Ptr)
				return nullptr;
			return Add(As<std::int32_t&>()).Add(4U);
		}

		 explicit operator bool() noexcept
		{
			return m_Ptr;
		}
	protected:
		void* m_Ptr;
	};

	class MemoryRegion
	{
	public:
		 explicit MemoryRegion(MemoryHandle base, std::size_t size):
			m_Base(base),
			m_Size(size)
		{}

		 MemoryHandle Base()
		{
			return m_Base;
		}

		 MemoryHandle End()
		{
			return m_Base.Add(m_Size);
		}

		 std::size_t Size()
		{
			return m_Size;
		}

		 bool Contains(MemoryHandle p)
		{
			if (p.As<std::uintptr_t>() < m_Base.As<std::uintptr_t>())
				return false;
			if (p.As<std::uintptr_t>() > m_Base.Add(m_Size).As<std::uintptr_t>())
				return false;

			return true;
		}
	protected:
		MemoryHandle m_Base;
		std::size_t m_Size;
	};

	class Module : public MemoryRegion
	{
	public:
		explicit Module(std::nullptr_t):
			Module(static_cast<char*>(nullptr))
		{}
		
		explicit Module(const char* name):
			Module(GetModuleHandleA(name))
		{
		}

		Module(HMODULE hmod):
			MemoryRegion(hmod, 0)
		{
			auto dosHeader = m_Base.As<IMAGE_DOS_HEADER*>();
			auto ntHeader = m_Base.Add(dosHeader->e_lfanew).As<IMAGE_NT_HEADERS64*>();
			m_Size = ntHeader->OptionalHeader.SizeOfImage;
		}

		template <typename TReturn, typename TOffset>
		TReturn GetRVA(TOffset rva)
		{
			return m_Base.Add(rva).As<TReturn>();
		}

		IMAGE_DOS_HEADER* GetDosHeaders()
		{
			return m_Base.As<IMAGE_DOS_HEADER*>();
		}

		IMAGE_NT_HEADERS64* GetNtHeaders()
		{
			return m_Base.Add(m_Base.As<IMAGE_DOS_HEADER*>()->e_lfanew).As<IMAGE_NT_HEADERS64*>();
		}
	};

	class Signature
	{
	public:
		struct Element
		{
			std::uint8_t m_Data{};
			bool m_Wildcard{};
		};

		explicit Signature(const char* pattern, const char* Name)
		{
			g_Logger->Green(fmt::format("Found {0}", Name).c_str());
			auto toUpper = [](char c) -> char
			{
				return c >= 'a' && c <= 'z' ? static_cast<char>(c + ('A' - 'a')) : static_cast<char>(c);
			};

			auto isHex = [&](char c) -> bool
			{
				switch (toUpper(c))
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
					return true;
				default:
					return false;
				}
			};

			do
			{
				if (*pattern == ' ')
					continue;
				if (*pattern == '?')
				{
					m_Elements.push_back(Element{ {}, true });
					continue;
				}

				if (*(pattern + 1) && isHex(*pattern) && isHex(*(pattern + 1)))
				{
					char str[3] = { *pattern, *(pattern + 1), '\0' };
					auto data = std::strtol(str, nullptr, 16);

					m_Elements.push_back(Element{ static_cast<std::uint8_t>(data), false });
				}
			} while (*(pattern++));
		}

		MemoryHandle Scan(MemoryRegion region = Module(nullptr))
		{
			auto compareMemory = [](std::uint8_t* data, Element* elem, std::size_t num) -> bool
			{
				for (std::size_t i = 0; i < num; ++i)
				{
					if (!elem[i].m_Wildcard)
						if (data[i] != elem[i].m_Data)
							return false;
				}

				return true;
			};

			for (std::uintptr_t i = region.Base().As<std::uintptr_t>(), end = region.End().As<std::uintptr_t>(); i != end; ++i)
			{
				if (compareMemory(reinterpret_cast<std::uint8_t*>(i),  m_Elements.data(), m_Elements.size()))
				{
					return MemoryHandle(i);
				}
			}

			return {};
		}
	private:
		std::vector<Element> m_Elements;
	};
}
