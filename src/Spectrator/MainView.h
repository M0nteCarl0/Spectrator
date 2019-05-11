#pragma once
#include "CPUInformation.h"
#include "SpeculationControl.h"
#include "WindowsSpeculationControl.h"
namespace Spectrator {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public
ref class MainView : public System::Windows::Forms::Form {
public:
  MainView(void);
  ~MainView(void);

protected:
  CPUInformation *_CPUInformation;
  WindowsSpeculationControl *_WindowsSpeculationControl;
  System::Windows::Forms::GroupBox ^ groupBox2;
  System::Windows::Forms::GroupBox ^ groupBox3;
  System::Windows::Forms::GroupBox ^ groupBox4;
  System::Windows::Forms::GroupBox ^ groupBox5;
  System::Windows::Forms::CheckBox ^ BTIDisabledByNoHardwareSupport_checkBox;
  System::Windows::Forms::CheckBox ^ BTIDisabledBySystemPolicy_checkBox;
  System::Windows::Forms::CheckBox ^ BTIWindowsSupportEnabled_checkBox;
  System::Windows::Forms::CheckBox ^ BTIWindowsSupportPresent_checkBox;
  System::Windows::Forms::CheckBox ^ BTIHardwarePresent_checkBox;
  System::Windows::Forms::CheckBox ^ KVAShadowWindowsSupportEnabled_checkBox;
  System::Windows::Forms::CheckBox ^ KVAShadowWindowsSupportPresent_checkBox;
  System::Windows::Forms::CheckBox ^ KVAShadowRequired_checkBox;
  System::Windows::Forms::Button ^ ReadSpecualtionControl;
  System::Windows::Forms::TabControl ^ tabControl1;
  System::Windows::Forms::TabPage ^ tabPage1;
  System::Windows::Forms::GroupBox ^ groupBox6;
  System::Windows::Forms::Button ^ WriteWORegisters;
  System::Windows::Forms::TabPage ^ tabPage2;
  System::Windows::Forms::TabPage ^ tabPage3;
  System::Windows::Forms::TabPage ^ tabPage4;
  System::Windows::Forms::TabPage ^ tabPage5;
  System::Windows::Forms::GroupBox ^ groupBox7;
  System::Windows::Forms::CheckBox ^ SSBD_support_checkBox;
  System::Windows::Forms::CheckBox ^ IA32_ARCH_CAPABILITIES_support_checkBox;
  System::Windows::Forms::CheckBox ^ L1D_FLUSH_support_checkBox;
  System::Windows::Forms::CheckBox ^ STIBP_support_checkBox;
  System::Windows::Forms::CheckBox ^ IBRS_AND_IBPB_support_checkBox;
  System::Windows::Forms::GroupBox ^ IA32_ARCH_CAPABILITIES_groupBox;
  System::Windows::Forms::CheckBox ^ SSB_NO_checkBox;
  System::Windows::Forms::CheckBox ^ SKIP_L1DFL_VMENTRY_checkBox;
  System::Windows::Forms::CheckBox ^ RSBA_checkBox;
  System::Windows::Forms::CheckBox ^ IBRS_ALL_checkBox;
  System::Windows::Forms::CheckBox ^ RDCL_NO_checkBox;
  System::Windows::Forms::CheckBox ^ KVAShadowPcidEnabled_checkBox;
  System::Windows::Forms::CheckBox ^
      SSBDWindowsSupportEnabledSystemWide_checkBox;
  System::Windows::Forms::CheckBox ^ SSBDWindowsSupportPresent_checkBox;
  System::Windows::Forms::CheckBox ^ SSBDHardwarePresent_checkBox;
  System::Windows::Forms::CheckBox ^ SSBDHardwareVulnerable_checkBox;
  System::Windows::Forms::CheckBox ^ L1TFWindowsSupportEnabled_checkBox;
  System::Windows::Forms::CheckBox ^ L1TFWindowsSupportPresent_checkBox;
  System::Windows::Forms::CheckBox ^ L1TFHardwareVulnerable_checkBox;
  System::Windows::Forms::CheckBox ^ SMEP_support_checkBox;
  System::Windows::Forms::CheckBox ^ SMAP_support_checkBox;
  System::Windows::Forms::GroupBox ^ groupBox8;
  System::Windows::Forms::Button ^ button2;
  System::Windows::Forms::Button ^ button1;
  System::Windows::Forms::CheckBox ^ PCID_checkBox;
  System::Windows::Forms::CheckBox ^ SMEP_checkBox;
  System::Windows::Forms::CheckBox ^ SMAP_checkBox;
  System::Windows::Forms::CheckBox ^ PCID_support_checkBox;
  System::Windows::Forms::CheckBox ^ INVPCID_support_checkBox;
  SpeculationControl *_SpeculationControl;
  System::Windows::Forms::StatusStrip ^ statusStrip1;
  System::Windows::Forms::ToolStripStatusLabel ^ CPUID_Processor_Name;
  System::Windows::Forms::ToolStripStatusLabel ^ CPUID_Processor_Family;
  System::Windows::Forms::ToolStripStatusLabel ^ CPUID_Processor_Microcode;
  System::Windows::Forms::GroupBox ^ groupBox1;
  System::Windows::Forms::CheckBox ^ STIBP_checkBox;
  System::Windows::Forms::CheckBox ^ IBRS_checkBox;
  System::Windows::Forms::CheckBox ^ SSBD_checkBox;
  System::Windows::Forms::CheckBox ^ IBPB_checkBox;
  System::Windows::Forms::CheckBox ^ L1D_FLUSH_checkBox;
  System::Windows::Forms::Button ^ WriteSpeculationControl;
  System::ComponentModel::Container ^ components;

  void InitializeComponent(void);
  System::Void WriteSpeculationControl_Click(System::Object ^ sender,
                                             System::EventArgs ^ e);
  System::Void ReadSpecualtionControl_Click(System::Object ^ sender,
                                            System::EventArgs ^ e);
  System::Void WriteWORegisters_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
};
} // namespace Spectrator
