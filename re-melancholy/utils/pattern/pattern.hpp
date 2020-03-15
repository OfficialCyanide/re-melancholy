#pragma once
#include <Windows.h>
#include <Psapi.h>

namespace pattern
{
	#define in_range(x,a,b) (x >= a && x <= b) 
	#define get_bits(x) (in_range((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xA) : (in_range(x,'0','9') ? x - '0' : 0))
	#define get_bytes(x) (get_bits(x[0]) << 4 | get_bits(x[1]))

	inline HMODULE get_module_handle(const char *module)
	{
		HMODULE hmModuleHandle = nullptr;

		do {
			hmModuleHandle = GetModuleHandleA(module);
			Sleep(1); //thonk
		} while (hmModuleHandle == nullptr);

		return hmModuleHandle;
	}

	inline DWORD find_in_module(DWORD address, DWORD length, const char *pattern)
	{
		const char *pat = pattern;
		DWORD firstMatch = 0x0;

		for (DWORD pCur = address; pCur < length; pCur++)
		{
			if (!*pat) return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == get_bytes(pat)) {
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else pat += 2;
			}

			else {
				pat = pattern;
				firstMatch = 0;
			}
		}

		return 0x0;
	}

	inline DWORD find_in_module(const char *module, const char *pattern)
	{
		const char* pat = pattern;
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(module);
		MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;

		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == get_bytes(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2;
			}

			else {
				pat = pattern;
				firstMatch = 0;
			}
		}

		return 0x0;
	}

	inline DWORD find_in_client(const char *pattern)
	{
		static HMODULE hmModule = get_module_handle("client.dll");
		static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
		static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
		return find_in_module(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, pattern);
	}

	inline DWORD find_in_engine(const char *pattern)
	{
		static HMODULE hmModule = get_module_handle("engine.dll");
		static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
		static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
		return find_in_module(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, pattern);
	}
}