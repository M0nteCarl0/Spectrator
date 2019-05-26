#include <Windows.h>
#ifndef _SPEC_CONTROL_CPU_
#define _SPEC_CONTROL_CPU_
enum IA32_SPEC_CTRL_MSR_FLAG {
  IA32_SPEC_CTRL_MSR_FLAG_IBRS = (1 << 0),
  IA32_SPEC_CTRL_MSR_FLAG_STIBP = (1 << 1),
  IA32_SPEC_CTRL_MSR_FLAG_SSBD = (1 << 2)
};

enum IA32_ARCH_CAPABILITIES_MSR_FLAG {
  IA32_ARCH_CAPABILITIES_MSR_FLAG_RDCL_NO = (1 << 0),
  IA32_ARCH_CAPABILITIES_MSR_FLAG_IBRS_ALL = (1 << 1),
  IA32_ARCH_CAPABILITIES_MSR_FLAG_RSBA = (1 << 2),
  IA32_ARCH_CAPABILITIES_MSR_FLAG_SKIP_L1DFL_VMENTRY = (1 << 3),
  IA32_ARCH_CAPABILITIES_MSR_FLAG_SSB_NO = (1 << 4),
  IA32_ARCH_CAPABILITIES_MSR_FLAG_MDS_NO = (1 << 5),
};

enum IA32_PRED_CMD_MSR_FLAG {
  IA32_PRED_CMD_MSR_FLAG_IBPB = (0 << 1),
};

enum IA32_FLUSH_CMD_MSR_FLAG {
  IA32_FLUSH_CMD_MSR_FLAG_IA32_FLUSH_CMD = (0 << 0),
};

enum SPECULATION_CONTROL_MSR {
  SPECULATION_CONTROL_MSR_IA32_SPEC_CTRL = 0x48,
  SPECULATION_CONTROL_MSR_IA32_PRED_CMD = 0x49,
  SPECULATION_CONTROL_MSR_IA32_FLUSH_CMD = 0x10B,

};

class SpeculationControl {
public:
  SpeculationControl(void);
  ~SpeculationControl(void);
  int GetMicrocodeVersion(void);
  void SetNumProcessors(size_t NumProcessors);
  void ApplyPerPackageSpeculationControl(void);
  void GetSpeculationCapabylities(void);
  bool
  GetSpeculationCapabylitiesAvallibility(IA32_ARCH_CAPABILITIES_MSR_FLAG Flag);
  void GetSpeculationControlSettings(void);
  bool GetSpeculationControlSettingsActivity(IA32_SPEC_CTRL_MSR_FLAG Flag);
  void SetSpeculationControlFlagState(IA32_SPEC_CTRL_MSR_FLAG Flag, bool State);
  void SetStatePredictionControl(IA32_PRED_CMD_MSR_FLAG Flag, bool State);
  void ApplyPerPackagePredictionControl(void);
  void SetStateFlushCaches(IA32_FLUSH_CMD_MSR_FLAG Flag, bool State);
  void ApplyPerPackageFlushCachesControl(void);
  bool CheckWritedSpeculationControlSettings(void);
  DWORD GetIA32_SPEC_CTRL(void) { return IA32_SPEC_CTRL; };
  DWORD GetIA32_SPEC_CTRLW(void) { return IA32_SPEC_CTRLW; };

private:
  size_t ProcessorMask;
  size_t LogicalProcessorCount;
  DWORD IA32_SPEC_CTRL;
  DWORD IA32_SPEC_CTRLW;
  DWORD IA32_ARCH_CAPABILITIES;
  DWORD IA32_PRED_CMD;
  DWORD IA32_FLUSH_CMD;
  unsigned long long CR4;
  HANDLE Thread;
};
#endif
