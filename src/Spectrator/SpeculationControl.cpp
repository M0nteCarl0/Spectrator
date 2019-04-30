#include "SpeculationControl.h"
#include <OlsApi.h>
#include <intrin.h>
SpeculationControl::SpeculationControl(void) {
  bool Flag = InitializeOls();
  IA32_SPEC_CTRL = 0;
  IA32_PRED_CMD = 0;
  IA32_ARCH_CAPABILITIES = 0;
  IA32_FLUSH_CMD = 0;
  // CR4 = __readcr4();
  GetSpeculationControlSettings();
  Thread = GetCurrentThread();
}

SpeculationControl::~SpeculationControl(void) {}

int SpeculationControl::GetMicrocodeVersion(void) {
  DWORD L = 0;
  DWORD H = 0;
  DWORD uCodeVersion = 0;
  if (RdmsrPx(0x8B, &L, &H, 0x1)) {
    uCodeVersion = L | H << 32;
  }
  return uCodeVersion;
}

void SpeculationControl::SetNumProcessors(size_t NumProcessors) {
  LogicalProcessorCount = NumProcessors;
}

void SpeculationControl::SetProcessorMask(size_t ProcesorMask) {}

void SpeculationControl::ApplyPerPackageSpeculationControl(void) {
  DWORD H = 0;
  DWORD AffinityMask = 0;
  IA32_SPEC_CTRLW = IA32_SPEC_CTRL;
  for (size_t i = 0; i < LogicalProcessorCount; i++) {
    AffinityMask = (1 << i);
    SetThreadAffinityMask(Thread, AffinityMask);
    _mm_lfence();
    Wrmsr(0x48, IA32_SPEC_CTRL, H);
    _mm_lfence();
  }
}

void SpeculationControl::GetSpeculationCapabylities(void) {
  DWORD H;
  _mm_lfence();
  Rdmsr(0x10A, &IA32_ARCH_CAPABILITIES, &H);
  _mm_lfence();
}

bool SpeculationControl::GetSpeculationCapabylitiesAvallibility(
    IA32_ARCH_CAPABILITIES_MSR_FLAG Flag) {
  return ((IA32_ARCH_CAPABILITIES & Flag) != 0);
}

void SpeculationControl::GetSpeculationControlSettings(void) {
  _mm_mfence();
  DWORD H = 0;
  DWORD AffinityMask = 1;
  SetThreadAffinityMask(Thread, AffinityMask);
  _mm_lfence();
  Rdmsr(0x48, &IA32_SPEC_CTRL, &H);
  _mm_mfence();
}

bool SpeculationControl::GetSpeculationControlSettingsActivity(
    IA32_SPEC_CTRL_MSR_FLAG Flag) {
  return ((IA32_SPEC_CTRL & Flag) != 0);
}

void SpeculationControl::SetSpeculationControlFlagState(
    IA32_SPEC_CTRL_MSR_FLAG Flag, bool State) {
  if (State) {
    IA32_SPEC_CTRL |= Flag;
  } else {
    IA32_SPEC_CTRL &= ~Flag;
  }
}

void SpeculationControl::SetStatePredictionControl(IA32_PRED_CMD_MSR_FLAG Flag,
                                                   bool State) {
  if (State) {
    IA32_PRED_CMD |= Flag;
  } else {
    IA32_PRED_CMD &= ~Flag;
  }
}

void SpeculationControl::ApplyPerPackagePredictionControl(void) {
  DWORD H = 0;
  DWORD AffinityMask = 0;
  for (size_t i = 0; i < LogicalProcessorCount; i++) {
    AffinityMask = (1 << i);
    SetThreadAffinityMask(Thread, AffinityMask);
    Wrmsr(0x49, IA32_PRED_CMD, H);
    _mm_mfence();
  }
}

void SpeculationControl::SetStateFlushCaches(IA32_FLUSH_CMD_MSR_FLAG Flag,
                                             bool State) {
  if (State) {
    IA32_FLUSH_CMD |= Flag;
  } else {
    IA32_FLUSH_CMD &= ~Flag;
  }
}

void SpeculationControl::ApplyPerPackageFlushCachesControl(void) {
  DWORD H = 0;
  DWORD AffinityMask = 0;
  for (size_t i = 0; i < LogicalProcessorCount; i++) {
    AffinityMask = (1 << i);
    SetThreadAffinityMask(Thread, AffinityMask);
    Wrmsr(0x10B, IA32_FLUSH_CMD, H);
    _mm_mfence();
  }
}

bool SpeculationControl::CheckWritedSpeculationControlSettings(void) {
  bool Flag = false;
  if (IA32_SPEC_CTRL == IA32_SPEC_CTRLW) {
    Flag = true;
  }
  return Flag;
}

void SpeculationControl::ApplyPerLogicalProceesorMask(void) {}
