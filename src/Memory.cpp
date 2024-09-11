#include"pch.h"
#include<TlHelp32.h>
#include"Memory.h"
//Internal Functions

uintptr_t Memory::GetPointerAddress(uintptr_t address, std::vector<DWORD>& offsets) {                   //TODO: FIX?

    uintptr_t Address = address;

    for (int i = 0; i < offsets.size(); i++) // we dont want to change the last offset value so we do -1
    {
        Address = *(uintptr_t*)Address;
        Address += (uintptr_t)offsets[i];
    }
    std::cout << "\n\nAddress : " << Address << '\n';
    return Address;
}

void Memory::Nop(BYTE* dst, size_t size) {
	DWORD Old = NULL;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &Old);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, Old, &Old);
};
void Memory::Patch(BYTE* dst, BYTE* Replacement, size_t size) {
	DWORD Old = NULL;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &Old);
	memcpy(dst, Replacement, size);
	VirtualProtect(dst, size, Old, &Old);
};

//statical Functions (Not Tested)

template<typename R>
R Memory::ReadMemory(HANDLE HandleToProcess,LPVOID Address) {
	R Buffer;
	ReadProcessMemory(HandleToProcess, Address, Buffer, sizeof(Buffer), NULL);
}

template<typename W>
void Memory::WriteMemory(HANDLE HandleToProcess, LPVOID Address, W Value) {
	
	ReadProcessMemory(HandleToProcess, Address, Value, sizeof(Value), NULL);
}

void Memory::NopEx(HANDLE HandleToProcess,BYTE* dst, size_t Size) {
	DWORD Old = NULL ;
	VirtualProtectEx(HandleToProcess, dst, Size, PAGE_EXECUTE_READWRITE, &Old);
	WriteMemory(HandleToProcess, (LPVOID)dst, (LPVOID)0x90);
	VirtualProtectEx(HandleToProcess, dst, Size, Old, &Old);
};

void Memory::PatchEx(HANDLE HandleToProcess, BYTE* dst, BYTE* Replacement, size_t Size) {
	DWORD Old = NULL;
	VirtualProtectEx(HandleToProcess, dst, Size, PAGE_EXECUTE_READWRITE, &Old);
	WriteMemory(HandleToProcess, (LPVOID)dst, (LPVOID)Replacement);
	VirtualProtectEx(HandleToProcess, dst, Size, Old, &Old);
};

DWORD Memory::GetProcessId(const wchar_t* ProcessName) {
    DWORD pid = 0;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W entry;
        entry.dwSize = sizeof(entry);
        if (Process32FirstW(snap, &entry)) {
            do {
                if (wcscmp(entry.szExeFile, ProcessName) == 0) {
                    pid = entry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snap, &entry));
        }
        CloseHandle(snap);
    }
    return pid;
}
uintptr_t Memory::GetModuleBaseAddress(DWORD processId, const wchar_t* moduleName) {
    uintptr_t baseAddress = 0;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (snap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32W entry;
        entry.dwSize = sizeof(entry);
        if (Module32FirstW(snap, &entry)) {
            do {
                if (wcscmp(entry.szModule, moduleName) == 0) {
                    baseAddress = (uintptr_t)entry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(snap, &entry));
        }
        CloseHandle(snap);
    }
    return baseAddress;
}
uintptr_t Memory::GetPointerAddressEx(HANDLE& hwnd, uintptr_t& gameBaseAddr, uintptr_t& address, std::vector<DWORD>& offsets) {
    DWORD offset_null = NULL;
    ReadProcessMemory(hwnd, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
    DWORD pointeraddress = offset_null; // the address we need
    for (int i = 0; i < offsets.size() - 1; i++) // we dont want to change the last offset value so we do -1
    {
        ReadProcessMemory(hwnd, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
    }
    return pointeraddress += offsets.at(offsets.size() - 1); // adding the last offset
}
 