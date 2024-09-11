#include"pch.h"

struct Memory {
	//Internal

	static void Nop(BYTE* dst, size_t Size);
	static void Patch(BYTE* dst, BYTE*Replacement, size_t Size);
	static uintptr_t GetPointerAddress(uintptr_t address, std::vector<DWORD>& offsets);                   // FIXED  

	//statical

	static DWORD GetProcessId(const wchar_t* ProcessName);
	static uintptr_t GetModuleBaseAddress(DWORD processId, const wchar_t* moduleName);
	static uintptr_t GetPointerAddressEx(HANDLE& hwnd, uintptr_t& gameBaseAddr, uintptr_t& address, std::vector<DWORD>& offsets);

	template<typename T>
	static T ReadMemory(HANDLE HandleToProcess, LPVOID Address);

	template<typename W>
	static void WriteMemory(HANDLE HandleToProcess, LPVOID Address, W Value);

	static void NopEx(HANDLE HandleToProcess, BYTE* dst, size_t Size);
	static void PatchEx(HANDLE HandleToProcess, BYTE* dst, BYTE*Replacement, size_t Size);

};