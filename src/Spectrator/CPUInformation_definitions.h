#include <stdint.h>
#ifndef _CPU_DEFINES_
#define _CPU_DEFINES_
enum ProcessorFeatureFlags {

  ProcessorFeatureFlags_FPU = 0x0,
  ProcessorFeatureFlags_VME,
  ProcessorFeatureFlags_DE,
  ProcessorFeatureFlags_PSE,
  ProcessorFeatureFlags_TSC,
  ProcessorFeatureFlags_MSC,
  ProcessorFeatureFlags_PAE,
  ProcessorFeatureFlags_MCE,
  ProcessorFeatureFlags_CX8,
  ProcessorFeatureFlags_APIC,
  ProcessorFeatureFlags_SEP = 0xA,
  ProcessorFeatureFlags_MTRR,
  ProcessorFeatureFlags_PGE,
  ProcessorFeatureFlags_MCA,
  ProcessorFeatureFlags_CMOV,
  ProcessorFeatureFlags_PAT,
  ProcessorFeatureFlags_PSE36,
  ProcessorFeatureFlags_PSN,
  ProcessorFeatureFlags_CLFSH,
  ProcessorFeatureFlags_DS = 0x15,
  ProcessorFeatureFlags_ACPI,
  ProcessorFeatureFlags_MMX,
  ProcessorFeatureFlags_FXSR,
  ProcessorFeatureFlags_SSE,
  ProcessorFeatureFlags_SSE2,
  ProcessorFeatureFlags_SS,
  ProcessorFeatureFlags_HTT,
  ProcessorFeatureFlags_TM,
  ProcessorFeatureFlags_PBE = 0x1F,
};

enum ProcessorFeatureFlagsECX {
  ProcessorFeatureFlagsECX_PCID = 0x11,
};

enum ProcessorFeatureFlagsExtended {
  ProcessorFeatureFlagsExtended_SSE3 = 0x0,
  ProcessorFeatureFlagsExtended_PCLMULDQ,
  ProcessorFeatureFlagsExtended_DTES64,
  ProcessorFeatureFlagsExtended_MONITOR,
  ProcessorFeatureFlagsExtended_DS_CPL,
  ProcessorFeatureFlagsExtended_VMX,
  ProcessorFeatureFlagsExtended_SMX,
  ProcessorFeatureFlagsExtended_EST,
  ProcessorFeatureFlagsExtended_TM2,
  ProcessorFeatureFlagsExtended_SSSE3,
  ProcessorFeatureFlagsExtended_CNX_ID,
  ProcessorFeatureFlagsExtended_FMA = 0xC,
  ProcessorFeatureFlagsExtended_CX16 = 0xD,
  ProcessorFeatureFlagsExtended_xTPR,
  ProcessorFeatureFlagsExtended_PDCM,
  ProcessorFeatureFlagsExtended_DCA = 0x12,
  ProcessorFeatureFlagsExtended_SSE41,
  ProcessorFeatureFlagsExtended_SSE42,
  ProcessorFeatureFlagsExtended_x2APIC,
  ProcessorFeatureFlagsExtended_MOVBE,
  ProcessorFeatureFlagsExtended_POPCNT,
  ProcessorFeatureFlagsExtended_AES = 0x19,
  ProcessorFeatureFlagsExtended_XSAVE,
  ProcessorFeatureFlagsExtended_OSXSAVE,
  ProcessorFeatureFlagsExtended_AVX,
  ProcessorFeatureFlagsExtended_F16C,
};

enum ProcessorFeatureFlagsExtendedEx {
  ProcessorFeatureFlagsExtendedEx_HLE = 0x4,
  ProcessorFeatureFlagsExtendedEx_AVX2 = 0x5,
  ProcessorFeatureFlagsExtendedEx_SMEP = 0x7,
  ProcessorFeatureFlagsExtendedEx_INVPCID = 0x9,
  ProcessorFeatureFlagsExtendedEx_RTM = 0xA,
  ProcessorFeatureFlagsExtendedEx_MPX = 0xE,
  ProcessorFeatureFlagsExtendedEx_AVX512F = 0x10,
  ProcessorFeatureFlagsExtendedEx_AVX512DQ = 0x11,
  ProcessorFeatureFlagsExtendedEx_SMAP = 0x14,
  ProcessorFeatureFlagsExtendedEx_AVX512PF = 0x1A,
  ProcessorFeatureFlagsExtendedEx_AVX512ER = 0x1B,
  ProcessorFeatureFlagsExtendedEx_AVX512CD = 0x1C,
  ProcessorFeatureFlagsExtendedEx_AVX512BW = 0x1E,
};

enum ProcessorFeatureFlagsExtendedExEDX {
  ProcessorFeatureFlagsExtendedExEDX_IBRS_IBPB = 26,
  ProcessorFeatureFlagsExtendedExEDX_STIBP = 27,
  ProcessorFeatureFlagsExtendedExEDX_L1D_FLUSH = 28,
  ProcessorFeatureFlagsExtendedExEDX_IA32_ARCH_CAPABILITIES = 29,
  ProcessorFeatureFlagsExtendedExEDX_SSBD = 31,
};

typedef struct ProcessorCacheInfoRaw {
  int _EAX;
  int _EBX;
  int _ECX;
  int _EDX;
} ProcessorCacheInfoRaw;

typedef enum CacheType {
  CacheType_NoMoreCaches = 0x0,
  CacheType_Data_Cache = 0x1,
  CacheType_Instruction_Cache = 0x2,
  CacheType_Unifided_Cache = 0x3,
} CacheType;

enum CacheAccesCapabylity {
  CacheAccesCapabylity_Inclusive = 0x0,
  CacheAccesCapabylity_SharedBeetwenThreads = 0x1,
};

enum CPUID_Function {
  CPUID_Function_Vendor_Name_and_largest_function = 0x0,
  CPUID_Function_Feature_Information = 0x1,
  CPUID_Function_Cache_Descriptors = 0x2,
  CPUID_Function_Processor_Serial_Number = 0x3,
  CPUID_Function_Cache_Parameters = 0x4,
  CPUID_Function_MONITOR__MWAIT_Parameters = 0x5,
  CPUID_Function_Digital_Thermal_Sensor_and_Power_Managment_Parameters = 0x6,
  CPUID_Function_ExtendedFeatures = 0x7,
  CPUID_Function_Direct_Cache_Information = 0x9,
  CPUID_Function_Architectual_Performance_Monitor = 0xA,
  CPUID_Function_Processor_Topology = 0xB,
  CPUID_Function_XSAVE_Features = 0xD,
};

enum CPUID_SubFunction {
  CPUID_SubFunction_LargestExtendedFunctionSupported = 0x80000000,
  CPUID_SubFunction_ExtendedProcessorSignature = 0x80000001,
  CPUID_SubFunction_BrandString1 = 0x80000002,
  CPUID_SubFunction_BrandString2 = 0x80000003,
  CPUID_SubFunction_BrandString3 = 0x80000004,
  CPUID_SubFunction_AMD_L1IDs = 0x80000005,
  CPUID_SubFunction_AMD_L2_L3_L2TLB_IDs = 0x80000006,
  CPUID_SubFunction_AMD_PhysicalCoreCount = 0x80000008, // threads for legacy
  CPUID_SubFunction_AMD_Cache_Parameters = 0x8000001D,
  CPUID_SubFunction_AMD_DieTopology = 0x8000001E,
};

typedef enum CPUID_CPUVendor {
  CPUID_CPUVendor_Intel = 0x1,
  CPUID_CPUVendor_AMD
} CPUID_CPUVendor;
#endif
