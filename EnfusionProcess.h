/*
	by unitx 12.22.2018
*/

#pragma once

#include "Engine.h"

enum Analysis
{
	Easy,
	Normal,
	Deep
};

typedef BOOL(WINAPI* tReadProcessMemory)(
	HANDLE  hProcess,
	LPCVOID lpBaseAddress,
	LPVOID  lpBuffer,
	SIZE_T  nSize,
	SIZE_T  *lpNumberOfBytesRead);

typedef BOOL(WINAPI* tWriteProcessMemory)(
	HANDLE  hProcess,
	LPVOID  lpBaseAddress,
	LPCVOID lpBuffer,
	SIZE_T  nSize,
	SIZE_T  *lpNumberOfBytesWritten);

class EnfusionProcess
{
public:
	static VOID AutoGameSelection(Analysis methods);
	static HANDLE GetProcessHandleByName(const CHAR *ProcessName);
	static uint64_t GetModuleBase();
	static uint64_t ModuleBase;
	static const char* GameName;

	template <typename T>
	static T ReadData(uint64_t address)
	{
		if (!address)
			return T();

		T buffer;
		return ZwCopyMemory(address, &buffer, sizeof(T), false) ? buffer : T();
	};

	template <typename T>
	static void WriteData(uint64_t address, T data)
	{
		if (!address)
			return;

		ZwCopyMemory(address, &data, sizeof(T), true);
	};

	static std::string ReadString(uint64_t address, size_t size)
	{
		if (!address || size > 1024)
			return "";

		char string[1024] = "";
		return ZwCopyMemory(address, string, size, false) ? std::string(string) : "";
	};

	static bool WriteString(uint64_t address, char* string, size_t size)
	{
		if (!address)
			return false;

		return ZwCopyMemory(address, string, size, true) ? true : false;
	};

private:
	static HANDLE m_hProcess;
	static tReadProcessMemory m_fReadMemory;
	static tWriteProcessMemory m_fWriteMemory;

	static __forceinline bool ZwCopyMemory(uint64_t address, PVOID buffer, uint64_t size, BOOL write = false)
	{
		if (m_hProcess == NULL)
			return false;

		SIZE_T bytes = 0;

		if (!write)
		{
			if (!m_fReadMemory(m_hProcess, (LPVOID)address, buffer, size, (SIZE_T*)&bytes))
				return false;

			if (bytes != size)
				return false;
		}
		else
		{
			if (!m_fWriteMemory(m_hProcess, (LPVOID)address, buffer, size, (SIZE_T*)&bytes))
				return false;

			if (bytes != size)
				return false;
		}

		return true;
	};
};

const CHAR* EnfusionProcess::GameName = "DayZ_x64.exe";
HANDLE EnfusionProcess::m_hProcess = NULL;
uint64_t EnfusionProcess::ModuleBase = NULL;
tReadProcessMemory EnfusionProcess::m_fReadMemory = NULL;
tWriteProcessMemory EnfusionProcess::m_fWriteMemory = NULL;

uint64_t EnfusionProcess::GetModuleBase()
{
	uint64_t baseAddress = 0;
	HANDLE hHandle = EnfusionProcess::GetProcessHandleByName(
		EnfusionProcess::GameName);
	HMODULE *moduleArray;
	LPBYTE moduleArrayBytes;
	DWORD bytesRequired;

	if (hHandle) {
		if (EnumProcessModules(hHandle, NULL, 0, &bytesRequired)) {
			if (bytesRequired) {
				moduleArrayBytes = (LPBYTE)LocalAlloc(LPTR, bytesRequired);
				if (moduleArrayBytes) {
					unsigned int moduleCount;
					moduleCount = bytesRequired / sizeof(HMODULE);
					moduleArray = (HMODULE *)moduleArrayBytes;
					if (EnumProcessModules(hHandle, moduleArray, bytesRequired, &bytesRequired)) {
						baseAddress = (DWORD_PTR)moduleArray[0];
					}
					LocalFree(moduleArrayBytes);
				}
			}
		}
		CloseHandle(hHandle);
	}
	return baseAddress;
}

HANDLE EnfusionProcess::GetProcessHandleByName(const CHAR *ProcessName)
{
	HANDLE hProcess = NULL;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes) {
		if (strcmp(pEntry.szExeFile, ProcessName) == 0) {
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, (uint32_t)pEntry.th32ProcessID);
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
	return hProcess;
}

VOID EnfusionProcess::AutoGameSelection(Analysis methods)
{
	if (methods == Analysis::Easy) {
		m_hProcess = EnfusionProcess::GetProcessHandleByName(EnfusionProcess::GameName);
	}

	if (methods == Analysis::Normal) {
		m_hProcess = EnfusionProcess::GetProcessHandleByName(EnfusionProcess::GameName);
	}

	if (methods == Analysis::Deep) {
		m_hProcess = GetProcessHandleByName(EnfusionProcess::GameName);

		if (m_hProcess == NULL) {

			HWND DayZTitleWindow = FindWindow(NULL, "DayZ");
			HWND DayZClassName = FindWindow("DayZ", NULL);

			DWORD DayZPid = NULL;

			if (DayZTitleWindow != NULL) {
				GetWindowThreadProcessId(DayZTitleWindow, &DayZPid);
				m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DayZPid);
			}
			else if (DayZClassName != NULL) {
				GetWindowThreadProcessId(DayZClassName, &DayZPid);
				m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DayZPid);
			}
		}

		ModuleBase = EnfusionProcess::GetModuleBase();
		m_fReadMemory = (tReadProcessMemory)GetProcAddress(GetModuleHandle("kernel32.dll"), "ReadProcessMemory");
		m_fWriteMemory = (tWriteProcessMemory)GetProcAddress(GetModuleHandle("kernel32.dll"), "WriteProcessMemory");
	}
}



