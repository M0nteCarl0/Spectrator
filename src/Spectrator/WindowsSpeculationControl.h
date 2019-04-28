#pragma once
#include <Windows.h>
#include <winternl.h>
#define STATUS_SUCCESS 0x00000000
#define STATUS_UNSUCCESSFUL 0xC0000001
#define SystemSpeculationControlInformation (SYSTEM_INFORMATION_CLASS)201
#define SystemKernelVaShadowInformation     (SYSTEM_INFORMATION_CLASS)196
typedef NTSTATUS(NTAPI *pNtQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength OPTIONAL
	);


typedef NTSTATUS(NTAPI *pNtSetSystemInformation)(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength
	);

typedef struct _SYSTEM_KERNEL_VA_SHADOW_INFORMATION {
	struct {
		ULONG KvaShadowEnabled : 1;
		ULONG KvaShadowUserGlobal : 1;
		ULONG KvaShadowPcid : 1;
		ULONG KvaShadowInvpcid : 1;
		ULONG KvaShadowRequired : 1;
		ULONG KvaShadowRequiredAvailable : 1;
		ULONG InvalidPteBit : 6;
		ULONG L1DataCacheFlushSupported : 1;
		ULONG L1TerminalFaultMitigationPresent : 1;
		ULONG Reserved : 18;
	} KvaShadowFlags;
} SYSTEM_KERNEL_VA_SHADOW_INFORMATION, *PSYSTEM_KERNEL_VA_SHADOW_INFORMATION;


typedef struct _SYSTEM_SPECULATION_CONTROL_INFORMATION {
	struct {
		ULONG BpbEnabled : 1;
		ULONG BpbDisabledSystemPolicy : 1;
		ULONG BpbDisabledNoHardwareSupport : 1;
		ULONG SpecCtrlEnumerated : 1;
		ULONG SpecCmdEnumerated : 1;
		ULONG IbrsPresent : 1;
		ULONG StibpPresent : 1;
		ULONG SmepPresent : 1;
		ULONG SpeculativeStoreBypassDisableAvailable : 1;
		ULONG SpeculativeStoreBypassDisableSupported : 1;
		ULONG SpeculativeStoreBypassDisabledSystemWide : 1;
		ULONG SpeculativeStoreBypassDisabledKernel : 1;
		ULONG SpeculativeStoreBypassDisableRequired : 1;
		ULONG BpbDisabledKernelToUser : 1;
		ULONG Reserved : 18;
	} SpeculationControlFlags;

} SYSTEM_SPECULATION_CONTROL_INFORMATION, *PSYSTEM_SPECULATION_CONTROL_INFORMATION;

class WindowsSpeculationControl
{
public:
	WindowsSpeculationControl(void);
	~WindowsSpeculationControl(void);
	SYSTEM_KERNEL_VA_SHADOW_INFORMATION GetKvaShadowFlags(void);
	SYSTEM_SPECULATION_CONTROL_INFORMATION  GetSpeculationControlFlags(void);
private:
	void GetKvaShadowFlags(SYSTEM_KERNEL_VA_SHADOW_INFORMATION* Flags);
	void GetSpeculationControlFlags(SYSTEM_SPECULATION_CONTROL_INFORMATION* Flags);
	void SetKvaShadowFlags(SYSTEM_KERNEL_VA_SHADOW_INFORMATION* Flags);
	void SetSpeculationControlFlags(SYSTEM_SPECULATION_CONTROL_INFORMATION* Flags);
	HINSTANCE hNtDll;
	pNtQuerySystemInformation NtQuerySystemInformation;
	pNtSetSystemInformation NtSetSystemInformation;
	SYSTEM_KERNEL_VA_SHADOW_INFORMATION KvaShadowFlags;
	SYSTEM_SPECULATION_CONTROL_INFORMATION  SpeculationControlFlags;

};

