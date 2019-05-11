// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com
#include "CPUInformation.h"
#include <cstring>
#include <intrin.h>
#include <stdio.h>
char TempName[64] = {0};

CPUInformation::CPUInformation(void) {
  if (CPUIDisAvalible()) {
    _RawCachesInfo = vector<ProcessorCacheInfoRaw>();
    GetVendorName();
    FeelBrandName();
    GetFeatureInformation();
    GetExtendedFeatures();
    EnumerateCaches();
    EnumerateLogicalCores();
    EnumeratePhysicalCores();
  }
}

CPUInformation::~CPUInformation(void) {}

void CPUInformation::GetFeatureInformation(void) {
  __cpuid(_REGS, CPUID_Function_Feature_Information);
  FeelInternalRegs();
  _ProcessorSignature = _EAX;
  _ProcessorFeatureInfo = _EBX;
  _ProcessorFeature = _EDX;
  _ProcessorFeatureExtended = _ECX;
  _ExtendedModel = (_ProcessorSignature >> 16) & 0x7;
  _ExtendeFamily = (_ProcessorSignature >> 20) & 0xFF;
  _ModelNumber = (_ProcessorSignature >> 4) & 0xF;
  _FamilyCode = (_ProcessorSignature >> 8) & 0x7;
  _StepingID = _ProcessorSignature & 0xF;
}

void CPUInformation::GetExtendedFeatures(void) {
  __cpuidex(_REGS, CPUID_Function_ExtendedFeatures, 0);
  FeelInternalRegs();
  _ProcessorFeatureEx = _EBX;
  _ProcessorFeatureExEDX = _EDX;
}

void CPUInformation::GetVendorName(void) {
  char VendorN[13] = {0};
  __cpuid(_REGS, CPUID_Function_Vendor_Name_and_largest_function);
  FeelInternalRegs();
  strncat_s(VendorN, (char *)&_REGS[1], 4);
  strncat_s(VendorN, (char *)&_REGS[3], 4);
  strncat_s(VendorN, (char *)&_REGS[2], 4);
  _Vendorname = string(VendorN);
  if (_Vendorname == "GenuineIntel") {
    _CPUVendor = CPUID_CPUVendor_Intel;
  }
  if (_Vendorname == "AuthenticAMD") {
    _CPUVendor = CPUID_CPUVendor_AMD;
  }
}

void CPUInformation::FeelInternalRegs(void) {
  _EAX = _REGS[0];
  _EBX = _REGS[1];
  _ECX = _REGS[2];
  _EDX = _REGS[3];
}

int CPUInformation::GetLargestExtendedFunctionSupported(void) {
  __cpuid(_REGS, CPUID_SubFunction_LargestExtendedFunctionSupported);
  FeelInternalRegs();
  return _EAX;
}

void CPUInformation::GetExtendedProcessorSignature(void) {
  __cpuid(_REGS, CPUID_SubFunction_ExtendedProcessorSignature);
  FeelInternalRegs();
}

void CPUInformation::GetBrandString1(void) {
  int RegValue = 0;
  char BrandNameC[16] = {0};
  __cpuid((int *)BrandNameC, CPUID_SubFunction_BrandString1);
  strncat_s(TempName, BrandNameC, 16);
}

void CPUInformation::GetBrandString2(void) {
  int RegValue = 0;
  char BrandNameC[16] = {0};
  __cpuid((int *)BrandNameC, CPUID_SubFunction_BrandString2);
  strncat_s(TempName, BrandNameC, 16);
}

void CPUInformation::GetBrandString3(void) {
  int RegValue = 0;
  char BrandNameC[16] = {0};
  __cpuid((int *)BrandNameC, CPUID_SubFunction_BrandString3);
  strncat_s(TempName, BrandNameC, 16);
  _BrandName = TempName;
}

void CPUInformation::FeelBrandName(void) {
  if (GetLargestExtendedFunctionSupported() >= CPUID_SubFunction_BrandString3) {
    GetBrandString1();
    GetBrandString2();
    GetBrandString3();
  }
}

void CPUInformation::EnumerateCaches(void) {
  int NoMoreCaches = 1;
  int LevelCache = 0;
  do {
    if (_CPUVendor == CPUID_CPUVendor_Intel) {
      __cpuidex(_REGS, CPUID_Function_Cache_Parameters, LevelCache);
    }

    if (_CPUVendor == CPUID_CPUVendor_AMD) {
      __cpuidex(_REGS, CPUID_SubFunction_AMD_Cache_Parameters, LevelCache);
    }
    FeelInternalRegs();
    LevelCache++;
  } while (IsLastCacheEnumerated());
}

bool CPUInformation::IsLastCacheEnumerated(void) {
  bool Res = true;
  ProcessorCacheInfoRaw OneUnitInfo;
  OneUnitInfo._EAX = _EAX;
  OneUnitInfo._EBX = _EBX;
  OneUnitInfo._ECX = _ECX;
  OneUnitInfo._EDX = _EDX;
  if (GetCacheTypeEnumerate(OneUnitInfo) == CacheType_NoMoreCaches) {
    Res = false;
  } else {
    _RawCachesInfo.push_back(OneUnitInfo);
  };
  return Res;
}

int CPUInformation::GetLogicalCPUCount(void) { return _LogicalCoresCount; }

int CPUInformation::GetPhysicalCPUCount(void) { return _PhysicalCoresCount; }

void CPUInformation::EnumerateLogicalCores(void) {
  _LogicalCoresCount = 0;
  if (_CPUVendor == CPUID_CPUVendor_Intel) {
    __cpuidex(_REGS, CPUID_Function_Processor_Topology, 1);
    FeelInternalRegs();
    _LogicalCoresCount = _EBX;
  }

  if (_CPUVendor == CPUID_CPUVendor_AMD) {
    __cpuid(_REGS, CPUID_Function_Feature_Information); // EAX: 0x1
    FeelInternalRegs();
    _LogicalCoresCount = (_EBX >> 16) & 0x7f;
  }
}

void CPUInformation::EnumeratePhysicalCores(void) {
  _PhysicalCoresCount = 0;
  if (_CPUVendor == CPUID_CPUVendor_Intel) {
    __cpuidex(_REGS, CPUID_Function_Processor_Topology, 0);
    FeelInternalRegs();
    _PhysicalCoresCount = _LogicalCoresCount / _EBX;
  }

  if (_CPUVendor == CPUID_CPUVendor_AMD) {
    __cpuid(_REGS, CPUID_SubFunction_AMD_DieTopology);
    FeelInternalRegs();
    int ThreadsPerPhysicalCore = ((_EBX >> 8) & 0xFF) + 1;
    _CCXCount = ((_ECX >> 8) & 0x7) + 1;
    _PhysicalCoresCount = _LogicalCoresCount / ThreadsPerPhysicalCore;
  }
}

bool CPUInformation::GetProcessorFeatureFlag(ProcessorFeatureFlags Feature) {
  return (_ProcessorFeature & 1 << Feature) != 0;
}

bool CPUInformation::GetProcessorFeatureFlagsExtended(
    ProcessorFeatureFlagsExtended Feature) {
  return (_ProcessorFeatureExtended & 1 << Feature) != 0;
}

bool CPUInformation::GetProcessorFeatureFlagsExtendedEx(
    ProcessorFeatureFlagsExtendedEx Feature) {
  return (_ProcessorFeatureEx & 1 << Feature) != 0;
}

bool CPUInformation::GetProcessorFeatureFlagsExtendedExEDX(
    ProcessorFeatureFlagsExtendedExEDX Feature) {
  return (_ProcessorFeatureExEDX & 1 << Feature) != 0;
}

bool CPUInformation::GetProcessorFeatureFlagsECX(
    ProcessorFeatureFlagsECX Feature) {
  return (_ProcessorFeatureExtended & 1 << Feature) != 0;
}

bool CPUInformation::CPUIDisAvalible(void) {
  bool Flag = false;
  unsigned long long FlagsW = __readeflags();
  FlagsW |= 0x200000;
  unsigned long long FlagsR = 0;
  __writeeflags(FlagsW);
  FlagsR = __readeflags();
  if (FlagsR & 0x200000) {
    Flag = true;
  }
  return Flag;
}

string CPUInformation::GetVendorname(void) { return _Vendorname; }

string CPUInformation::GetBrandName(void) { return _BrandName; }

int CPUInformation::GetStepingID(void) { return _StepingID; }

int CPUInformation::GetModelNumber(void) { return _ModelNumber; }

int CPUInformation::GetFamilyCode(void) { return _FamilyCode; }

int CPUInformation::GetType(void) { return _Type; }

int CPUInformation::GetExtendedModel(void) { return _ExtendedModel; }

int CPUInformation::GetExtendeFamily(void) { return _ExtendeFamily; }

int CPUInformation::GetModel(void) {
  return (_ExtendedModel << 4) + _ModelNumber;
}

int CPUInformation::GetFamily(void) { return _ExtendeFamily + _FamilyCode; }

int CPUInformation::GetCacheWaysAssociativity(int Level) {
  return ((_RawCachesInfo[Level]._EBX >> 22) & 0x1FF) + 1;
}

int CPUInformation::GetCacheNumberofSets(int Level) {
  return _RawCachesInfo[Level]._ECX + 1;
}

int CPUInformation::GetCacheCoherencyLineSize(int Level) {
  return (_RawCachesInfo[Level]._EBX & 0xFFF) + 1;
}

int CPUInformation::GetCachePhysicalLineSizePartitions(int Level) {
  return ((_RawCachesInfo[Level]._EBX >> 12) & 0x1FF) + 1;
}

int CPUInformation::GetCacheNumberAPIC(int Level) {
  int Value = 0;
  if (_CPUVendor == CPUID_CPUVendor_Intel) {
    Value = ((_RawCachesInfo[Level]._EAX >> 26) & 0x1F) + 1;
  }

  if (_CPUVendor == CPUID_CPUVendor_AMD) {
    Value = 1;
  }
  return Value;
}

int CPUInformation::GetCacheNumberThredsPerCache(int Level) {
  return ((_RawCachesInfo[Level]._EAX >> 14) & 0x7FF) + 1;
}

int CPUInformation::GetMaximumCacheLevel(void) { return _RawCachesInfo.size(); }

int CPUInformation::GetCacheSize(int Level) {
  return GetCacheWaysAssociativity(Level) *
         GetCachePhysicalLineSizePartitions(Level) *
         GetCacheCoherencyLineSize(Level) * GetCacheNumberofSets(Level);
}

CacheType CPUInformation::GetCacheTypeEnumerate(ProcessorCacheInfoRaw RawInfo) {
  return (CacheType)(RawInfo._EAX & 0x1F);
}

CacheType CPUInformation::GetCacheType(int Level) {
  return GetCacheTypeEnumerate(_RawCachesInfo[Level]);
}

int CPUInformation::GetCacheHWLevel(int Level) {
  return _RawCachesInfo[Level]._EAX >> 5 & 0x7;
}

int CPUInformation::GetSignature(void) { return _ProcessorSignature; }

int CPUInformation::GetCacheAccesCapabylity(int Level,
                                            CacheAccesCapabylity Capabylity) {
  return _RawCachesInfo[Level]._EDX & Capabylity;
}

CPUID_CPUVendor CPUInformation::GetCPUVendor(void) { return _CPUVendor; }

int CPUInformation::GetCCXCount(void) { return _CCXCount; }
