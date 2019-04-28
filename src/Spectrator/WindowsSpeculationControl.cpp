#include "WindowsSpeculationControl.h"


WindowsSpeculationControl::WindowsSpeculationControl(void)
{

	NTSTATUS State;
	hNtDll = GetModuleHandle("ntdll.dll");
	if (hNtDll)
	{	
		NtQuerySystemInformation = (pNtQuerySystemInformation)GetProcAddress(hNtDll, "NtQuerySystemInformation");
		NtSetSystemInformation = (pNtSetSystemInformation)GetProcAddress(hNtDll, "NtSetSystemInformation");
	}


	if (NtQuerySystemInformation)
	{
		ULONG Length = 0;
		NtQuerySystemInformation(SystemSpeculationControlInformation, &SpeculationControlFlags, sizeof(SpeculationControlFlags), &Length);
		NtQuerySystemInformation(SystemKernelVaShadowInformation, &KvaShadowFlags, sizeof(KvaShadowFlags), &Length);

	}


}


WindowsSpeculationControl::~WindowsSpeculationControl(void)
{
}

SYSTEM_KERNEL_VA_SHADOW_INFORMATION WindowsSpeculationControl::GetKvaShadowFlags(void)
{
	return  KvaShadowFlags;
}

SYSTEM_SPECULATION_CONTROL_INFORMATION WindowsSpeculationControl::GetSpeculationControlFlags(void)
{
	return SpeculationControlFlags;
}

void WindowsSpeculationControl::GetKvaShadowFlags(SYSTEM_KERNEL_VA_SHADOW_INFORMATION * Flags)
{
}

void WindowsSpeculationControl::GetSpeculationControlFlags(SYSTEM_SPECULATION_CONTROL_INFORMATION * Flags)
{
}

void WindowsSpeculationControl::SetKvaShadowFlags(SYSTEM_KERNEL_VA_SHADOW_INFORMATION * Flags)
{
}

void WindowsSpeculationControl::SetSpeculationControlFlags(SYSTEM_SPECULATION_CONTROL_INFORMATION * Flags)
{
}
