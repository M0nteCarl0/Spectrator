#include "CPUInformation_definitions.h"
#include <string>
#include <vector>
using namespace std;
#ifndef _CPU_INFO_
#define _CPU_INFO_
class CPUInformation {
public:
  CPUInformation(void);
  ~CPUInformation(void);
  bool GetProcessorFeatureFlag(ProcessorFeatureFlags Feature);
  bool GetProcessorFeatureFlagsExtended(ProcessorFeatureFlagsExtended Feature);
  bool
  GetProcessorFeatureFlagsExtendedEx(ProcessorFeatureFlagsExtendedEx Feature);
  bool GetProcessorFeatureFlagsExtendedExEDX(
      ProcessorFeatureFlagsExtendedExEDX Feature);
  bool GetProcessorFeatureFlagsECX(ProcessorFeatureFlagsECX Feature);
  bool CPUIDisAvalible(void);
  int GetLogicalCPUCount(void);
  int GetPhysicalCPUCount(void);
  int GetCCXCount(void);
  int GetStepingID(void);
  int GetModelNumber(void);
  int GetModel(void);
  int GetFamily(void);
  int GetFamilyCode(void);
  int GetType(void);
  int GetExtendedModel(void);
  int GetExtendeFamily(void);
  int GetMaximumCacheLevel(void);
  int GetCacheWaysAssociativity(int Level);
  int GetCacheNumberofSets(int Level);
  int GetCacheCoherencyLineSize(int Level);
  int GetCachePhysicalLineSizePartitions(int Level);
  int GetCacheNumberAPIC(int Level);
  int GetCacheNumberThredsPerCache(int Level);
  int GetCacheSize(int Level);
  int GetCacheHWLevel(int Level);
  int GetSignature(void);
  CacheType GetCacheType(int Level);
  int GetCacheAccesCapabylity(int Level, CacheAccesCapabylity Capabylity);
  CPUID_CPUVendor GetCPUVendor(void);
  string GetVendorname(void);
  string GetBrandName(void);

private:
  CacheType GetCacheTypeEnumerate(ProcessorCacheInfoRaw RawInfo);
  void GetFeatureInformation(void);
  void FeelInternalRegs(void);
  void GetVendorName(void);
  void FeelBrandName(void);
  void GetBrandString1(void);
  void GetBrandString2(void);
  void GetBrandString3(void);
  void GetExtendedFeatures(void);
  int GetLargestExtendedFunctionSupported(void);
  void GetExtendedProcessorSignature(void);
  void EnumerateCaches(void);
  void EnumerateLogicalCores(void);
  void EnumeratePhysicalCores(void);
  bool IsLastCacheEnumerated(void);
  int _EAX;
  int _EBX;
  int _ECX;
  int _EDX;
  int _REGS[4];
  int _LogicalCoresCount;
  int _PhysicalCoresCount;
  int _CCXCount;
  string _Vendorname;
  string _BrandName;
  string _ArchName;
  int _ProcessorFeature;
  int _ProcessorFeatureEx;
  int _ProcessorFeatureExEDX;
  int _ProcessorFeatureExtended;
  int _ProcessorFeatureInfo;
  int _StepingID;
  int _ModelNumber;
  int _FamilyCode;
  int _Type;
  int _ExtendedModel;
  int _ExtendeFamily;
  int _ProcessorSignature;
  vector<ProcessorCacheInfoRaw> _RawCachesInfo;
  CPUID_CPUVendor _CPUVendor;
};
#endif
