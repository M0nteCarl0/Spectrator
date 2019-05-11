// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com

#include "WindowsSpeculationControl.h"

WindowsSpeculationControl::WindowsSpeculationControl(void) {

  hNtDll = GetModuleHandle("ntdll.dll");
  NtQuerySystemInformation = nullptr;
  NtSetSystemInformation = nullptr;
  if (hNtDll) {
    NtQuerySystemInformation = (pNtQuerySystemInformation)GetProcAddress(
        hNtDll, "NtQuerySystemInformation");
    NtSetSystemInformation = (pNtSetSystemInformation)GetProcAddress(
        hNtDll, "NtSetSystemInformation");
  }

  if (NtQuerySystemInformation) {
    ULONG Length = 0;
    NtQuerySystemInformation(SystemSpeculationControlInformation,
                             &SpeculationControlFlags,
                             sizeof(SpeculationControlFlags), &Length);
    NtQuerySystemInformation(SystemKernelVaShadowInformation, &KvaShadowFlags,
                             sizeof(KvaShadowFlags), &Length);
  }
}

WindowsSpeculationControl::~WindowsSpeculationControl(void) {}

SYSTEM_KERNEL_VA_SHADOW_INFORMATION
WindowsSpeculationControl::GetKvaShadowFlags(void) { return KvaShadowFlags; }

SYSTEM_SPECULATION_CONTROL_INFORMATION
WindowsSpeculationControl::GetSpeculationControlFlags(void) {
  return SpeculationControlFlags;
}
