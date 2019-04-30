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

/// <summary>
/// —водка дл€ Form1
/// </summary>
public
ref class MainView : public System::Windows::Forms::Form {
public:
  MainView(void) {
    InitializeComponent();
    _CPUInformation = new CPUInformation();
    _SpeculationControl = new SpeculationControl();
    _WindowsSpeculationControl = new WindowsSpeculationControl();
    if (!_CPUInformation->GetProcessorFeatureFlagsExtendedExEDX(
            ProcessorFeatureFlagsExtendedExEDX_IBRS_IBPB)) {
      IBRS_checkBox->Enabled = false;
      IBPB_checkBox->Enabled = false;

    } else {
      IBRS_AND_IBPB_support_checkBox->Checked = true;
    }

    if (!_CPUInformation->GetProcessorFeatureFlagsExtendedExEDX(
            ProcessorFeatureFlagsExtendedExEDX_STIBP)) {
      STIBP_checkBox->Enabled = false;
    } else {
      STIBP_support_checkBox->Checked = true;
    }

    if (!_CPUInformation->GetProcessorFeatureFlagsExtendedExEDX(
            ProcessorFeatureFlagsExtendedExEDX_SSBD)) {
      SSBD_checkBox->Enabled = false;
    } else {
      SSBD_support_checkBox->Checked = true;
    }

    if (!_CPUInformation->GetProcessorFeatureFlagsExtendedExEDX(
            ProcessorFeatureFlagsExtendedExEDX_L1D_FLUSH)) {
      L1D_FLUSH_checkBox->Enabled = false;
    } else {
      L1D_FLUSH_support_checkBox->Checked = true;
    }

    INVPCID_support_checkBox->Checked =
        _CPUInformation->GetProcessorFeatureFlagsExtendedEx(
            ProcessorFeatureFlagsExtendedEx_INVPCID);
    SMAP_support_checkBox->Checked =
        _CPUInformation->GetProcessorFeatureFlagsExtendedEx(
            ProcessorFeatureFlagsExtendedEx_SMAP);
    SMEP_support_checkBox->Checked =
        _CPUInformation->GetProcessorFeatureFlagsExtendedEx(
            ProcessorFeatureFlagsExtendedEx_SMEP);
    PCID_support_checkBox->Checked =
        _CPUInformation->GetProcessorFeatureFlagsECX(
            ProcessorFeatureFlagsECX_PCID);
    if (!SMEP_support_checkBox->Checked) {
      SMEP_checkBox->Enabled = false;
    }

    if (!SMAP_support_checkBox->Checked) {
      SMAP_checkBox->Enabled = false;
    }
    if (!PCID_support_checkBox->Checked) {
      PCID_checkBox->Enabled = false;
    }

    if (_CPUInformation->GetProcessorFeatureFlagsExtendedExEDX(
            ProcessorFeatureFlagsExtendedExEDX_IA32_ARCH_CAPABILITIES)) {
      IA32_ARCH_CAPABILITIES_support_checkBox->Checked = true;
      _SpeculationControl->GetSpeculationCapabylities();
      RDCL_NO_checkBox->Checked =
          _SpeculationControl->GetSpeculationCapabylitiesAvallibility(
              IA32_ARCH_CAPABILITIES_MSR_FLAG_RDCL_NO);
      IBRS_ALL_checkBox->Checked =
          _SpeculationControl->GetSpeculationCapabylitiesAvallibility(
              IA32_ARCH_CAPABILITIES_MSR_FLAG_IBRS_ALL);
      RSBA_checkBox->Checked =
          _SpeculationControl->GetSpeculationCapabylitiesAvallibility(
              IA32_ARCH_CAPABILITIES_MSR_FLAG_RSBA);
      SKIP_L1DFL_VMENTRY_checkBox->Checked =
          _SpeculationControl->GetSpeculationCapabylitiesAvallibility(
              IA32_ARCH_CAPABILITIES_MSR_FLAG_SKIP_L1DFL_VMENTRY);
      SSB_NO_checkBox->Checked =
          _SpeculationControl->GetSpeculationCapabylitiesAvallibility(
              IA32_ARCH_CAPABILITIES_MSR_FLAG_SSB_NO);
    } else {
      IA32_ARCH_CAPABILITIES_groupBox->Enabled = false;
    }

    SSBDHardwareVulnerable_checkBox->Checked =
        _WindowsSpeculationControl->GetSpeculationControlFlags()
            .SpeculationControlFlags.SpeculativeStoreBypassDisableRequired;
    SSBDHardwarePresent_checkBox->Checked =
        _WindowsSpeculationControl->GetSpeculationControlFlags()
            .SpeculationControlFlags.SpeculativeStoreBypassDisableSupported;
    SSBDWindowsSupportPresent_checkBox->Checked =
        _WindowsSpeculationControl->GetSpeculationControlFlags()
            .SpeculationControlFlags.SpeculativeStoreBypassDisableAvailable;
    SSBDWindowsSupportEnabledSystemWide_checkBox->Checked =
        _WindowsSpeculationControl->GetSpeculationControlFlags()
            .SpeculationControlFlags.SpeculativeStoreBypassDisabledSystemWide;

    KVAShadowRequired_checkBox->Checked =
        _WindowsSpeculationControl->GetKvaShadowFlags()
            .KvaShadowFlags.KvaShadowRequired;
    KVAShadowPcidEnabled_checkBox->Checked =
        _WindowsSpeculationControl->GetKvaShadowFlags()
            .KvaShadowFlags.KvaShadowInvpcid;
    KVAShadowWindowsSupportEnabled_checkBox->Checked =
        _WindowsSpeculationControl->GetKvaShadowFlags()
            .KvaShadowFlags.KvaShadowEnabled;
    KVAShadowWindowsSupportPresent_checkBox->Checked =
        _WindowsSpeculationControl->GetKvaShadowFlags()
            .KvaShadowFlags.KvaShadowRequiredAvailable;

    L1TFHardwareVulnerable_checkBox->Checked =
        _WindowsSpeculationControl->GetSpeculationControlFlags()
            .SpeculationControlFlags.SpeculativeStoreBypassDisableRequired;
    L1TFWindowsSupportEnabled_checkBox->Checked =
        _WindowsSpeculationControl->GetKvaShadowFlags()
            .KvaShadowFlags.L1DataCacheFlushSupported;
    L1TFWindowsSupportPresent_checkBox->Checked =
        _WindowsSpeculationControl->GetKvaShadowFlags()
            .KvaShadowFlags.L1TerminalFaultMitigationPresent;

    BTIHardwarePresent_checkBox->Checked =
        !_WindowsSpeculationControl->GetSpeculationControlFlags()
             .SpeculationControlFlags.BpbDisabledNoHardwareSupport;
    BTIDisabledBySystemPolicy_checkBox->Checked =
        _WindowsSpeculationControl->GetSpeculationControlFlags()
            .SpeculationControlFlags.BpbDisabledSystemPolicy;
    BTIWindowsSupportEnabled_checkBox->Checked =
        _WindowsSpeculationControl->GetSpeculationControlFlags()
            .SpeculationControlFlags.BpbEnabled;
    BTIWindowsSupportPresent_checkBox->Checked =
        (_WindowsSpeculationControl->GetSpeculationControlFlags()
             .SpeculationControlFlags.IbrsPresent ||
         _WindowsSpeculationControl->GetSpeculationControlFlags()
             .SpeculationControlFlags.StibpPresent) != 0;

    _SpeculationControl->SetNumProcessors(
        _CPUInformation->GetLogicalCPUCount());
    IBRS_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_IBRS);
    STIBP_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_STIBP);
    SSBD_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_SSBD);
    CPUID_Processor_Name->Text =
        gcnew String(_CPUInformation->GetBrandName().c_str());
    CPUID_Processor_Family->Text =
        String::Format("0x{0:X}", _CPUInformation->GetSignature());
    CPUID_Processor_Microcode->Text =
        String::Format("0x{0:X}", _SpeculationControl->GetMicrocodeVersion());
  }

protected:
  CPUInformation *_CPUInformation;
  WindowsSpeculationControl *_WindowsSpeculationControl;

private:
  System::Windows::Forms::GroupBox ^ groupBox2;

protected:
private:
  System::Windows::Forms::GroupBox ^ groupBox3;

private:
  System::Windows::Forms::GroupBox ^ groupBox4;

private:
  System::Windows::Forms::GroupBox ^ groupBox5;

private:
  System::Windows::Forms::CheckBox ^ BTIDisabledByNoHardwareSupport_checkBox;

private:
  System::Windows::Forms::CheckBox ^ BTIDisabledBySystemPolicy_checkBox;

private:
  System::Windows::Forms::CheckBox ^ BTIWindowsSupportEnabled_checkBox;

private:
  System::Windows::Forms::CheckBox ^ BTIWindowsSupportPresent_checkBox;

private:
  System::Windows::Forms::CheckBox ^ BTIHardwarePresent_checkBox;

private:
  System::Windows::Forms::CheckBox ^ KVAShadowWindowsSupportEnabled_checkBox;

private:
  System::Windows::Forms::CheckBox ^ KVAShadowWindowsSupportPresent_checkBox;

private:
  System::Windows::Forms::CheckBox ^ KVAShadowRequired_checkBox;

private:
  System::Windows::Forms::Button ^ ReadSpecualtionControl;

private:
  System::Windows::Forms::TabControl ^ tabControl1;

private:
  System::Windows::Forms::TabPage ^ tabPage1;

private:
  System::Windows::Forms::GroupBox ^ groupBox6;

private:
  System::Windows::Forms::Button ^ WriteWORegisters;

private:
  System::Windows::Forms::TabPage ^ tabPage2;

private:
  System::Windows::Forms::TabPage ^ tabPage3;

private:
  System::Windows::Forms::TabPage ^ tabPage4;

private:
  System::Windows::Forms::TabPage ^ tabPage5;

private:
  System::Windows::Forms::GroupBox ^ groupBox7;

private:
  System::Windows::Forms::CheckBox ^ SSBD_support_checkBox;

private:
  System::Windows::Forms::CheckBox ^ IA32_ARCH_CAPABILITIES_support_checkBox;

private:
  System::Windows::Forms::CheckBox ^ L1D_FLUSH_support_checkBox;

private:
  System::Windows::Forms::CheckBox ^ STIBP_support_checkBox;

private:
  System::Windows::Forms::CheckBox ^ IBRS_AND_IBPB_support_checkBox;

private:
  System::Windows::Forms::GroupBox ^ IA32_ARCH_CAPABILITIES_groupBox;

private:
  System::Windows::Forms::CheckBox ^ SSB_NO_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SKIP_L1DFL_VMENTRY_checkBox;

private:
  System::Windows::Forms::CheckBox ^ RSBA_checkBox;

private:
  System::Windows::Forms::CheckBox ^ IBRS_ALL_checkBox;

private:
  System::Windows::Forms::CheckBox ^ RDCL_NO_checkBox;

private:
  System::Windows::Forms::CheckBox ^ KVAShadowPcidEnabled_checkBox;

private:
  System::Windows::Forms::CheckBox ^
      SSBDWindowsSupportEnabledSystemWide_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SSBDWindowsSupportPresent_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SSBDHardwarePresent_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SSBDHardwareVulnerable_checkBox;

private:
  System::Windows::Forms::CheckBox ^ L1TFWindowsSupportEnabled_checkBox;

private:
  System::Windows::Forms::CheckBox ^ L1TFWindowsSupportPresent_checkBox;

private:
  System::Windows::Forms::CheckBox ^ L1TFHardwareVulnerable_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SMEP_support_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SMAP_support_checkBox;

private:
  System::Windows::Forms::GroupBox ^ groupBox8;

private:
  System::Windows::Forms::Button ^ button2;

private:
  System::Windows::Forms::Button ^ button1;

private:
  System::Windows::Forms::CheckBox ^ PCID_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SMEP_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SMAP_checkBox;

private:
  System::Windows::Forms::CheckBox ^ PCID_support_checkBox;

private:
  System::Windows::Forms::CheckBox ^ INVPCID_support_checkBox;

  SpeculationControl *_SpeculationControl;
  /// <summary>
  /// ќсвободить все используемые ресурсы.
  /// </summary>
  ~MainView() {

    if (_SpeculationControl) {
      delete _SpeculationControl;
    }

    if (_CPUInformation) {
      delete _CPUInformation;
    }

    if (components) {
      delete components;
    }
  }

private:
  System::Windows::Forms::StatusStrip ^ statusStrip1;

protected:
private:
  System::Windows::Forms::ToolStripStatusLabel ^ CPUID_Processor_Name;

private:
  System::Windows::Forms::ToolStripStatusLabel ^ CPUID_Processor_Family;

private:
  System::Windows::Forms::ToolStripStatusLabel ^ CPUID_Processor_Microcode;

private:
  System::Windows::Forms::GroupBox ^ groupBox1;

private:
  System::Windows::Forms::CheckBox ^ STIBP_checkBox;

private:
  System::Windows::Forms::CheckBox ^ IBRS_checkBox;

private:
  System::Windows::Forms::CheckBox ^ SSBD_checkBox;

private:
  System::Windows::Forms::CheckBox ^ IBPB_checkBox;

private:
  System::Windows::Forms::CheckBox ^ L1D_FLUSH_checkBox;

private:
  System::Windows::Forms::Button ^ WriteSpeculationControl;

private:
  /// <summary>
  /// “ребуетс€ переменна€ конструктора.
  /// </summary>
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  /// <summary>
  /// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
  /// содержимое данного метода при помощи редактора кода.
  /// </summary>
  void InitializeComponent(void) {
    this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
    this->CPUID_Processor_Name =
        (gcnew System::Windows::Forms::ToolStripStatusLabel());
    this->CPUID_Processor_Family =
        (gcnew System::Windows::Forms::ToolStripStatusLabel());
    this->CPUID_Processor_Microcode =
        (gcnew System::Windows::Forms::ToolStripStatusLabel());
    this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
    this->ReadSpecualtionControl = (gcnew System::Windows::Forms::Button());
    this->WriteSpeculationControl = (gcnew System::Windows::Forms::Button());
    this->SSBD_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->STIBP_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->IBRS_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->L1D_FLUSH_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->IBPB_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
    this->BTIDisabledByNoHardwareSupport_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->BTIDisabledBySystemPolicy_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->BTIWindowsSupportEnabled_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->BTIWindowsSupportPresent_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->BTIHardwarePresent_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
    this->KVAShadowPcidEnabled_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->KVAShadowWindowsSupportEnabled_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->KVAShadowWindowsSupportPresent_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->KVAShadowRequired_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
    this->SSBDWindowsSupportEnabledSystemWide_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->SSBDWindowsSupportPresent_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->SSBDHardwarePresent_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->SSBDHardwareVulnerable_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
    this->L1TFWindowsSupportEnabled_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->L1TFWindowsSupportPresent_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->L1TFHardwareVulnerable_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
    this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
    this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
    this->button2 = (gcnew System::Windows::Forms::Button());
    this->button1 = (gcnew System::Windows::Forms::Button());
    this->PCID_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->SMEP_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->SMAP_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->IA32_ARCH_CAPABILITIES_groupBox =
        (gcnew System::Windows::Forms::GroupBox());
    this->SSB_NO_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->SKIP_L1DFL_VMENTRY_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->RSBA_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->IBRS_ALL_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->RDCL_NO_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
    this->PCID_support_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->INVPCID_support_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->SMEP_support_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->SMAP_support_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->SSBD_support_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->IA32_ARCH_CAPABILITIES_support_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->L1D_FLUSH_support_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->STIBP_support_checkBox = (gcnew System::Windows::Forms::CheckBox());
    this->IBRS_AND_IBPB_support_checkBox =
        (gcnew System::Windows::Forms::CheckBox());
    this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
    this->WriteWORegisters = (gcnew System::Windows::Forms::Button());
    this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
    this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
    this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
    this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
    this->statusStrip1->SuspendLayout();
    this->groupBox1->SuspendLayout();
    this->groupBox2->SuspendLayout();
    this->groupBox3->SuspendLayout();
    this->groupBox4->SuspendLayout();
    this->groupBox5->SuspendLayout();
    this->tabControl1->SuspendLayout();
    this->tabPage1->SuspendLayout();
    this->groupBox8->SuspendLayout();
    this->IA32_ARCH_CAPABILITIES_groupBox->SuspendLayout();
    this->groupBox7->SuspendLayout();
    this->groupBox6->SuspendLayout();
    this->tabPage2->SuspendLayout();
    this->tabPage3->SuspendLayout();
    this->tabPage4->SuspendLayout();
    this->tabPage5->SuspendLayout();
    this->SuspendLayout();
    //
    // statusStrip1
    //
    this->statusStrip1->Items->AddRange(
        gcnew cli::array<System::Windows::Forms::ToolStripItem ^>(3){
            this->CPUID_Processor_Name, this->CPUID_Processor_Family,
            this->CPUID_Processor_Microcode});
    this->statusStrip1->Location = System::Drawing::Point(0, 369);
    this->statusStrip1->Name = L"statusStrip1";
    this->statusStrip1->Size = System::Drawing::Size(699, 22);
    this->statusStrip1->TabIndex = 0;
    this->statusStrip1->Text = L"statusStrip1";
    //
    // CPUID_Processor_Name
    //
    this->CPUID_Processor_Name->Name = L"CPUID_Processor_Name";
    this->CPUID_Processor_Name->Size = System::Drawing::Size(118, 17);
    this->CPUID_Processor_Name->Text = L"toolStripStatusLabel1";
    //
    // CPUID_Processor_Family
    //
    this->CPUID_Processor_Family->Name = L"CPUID_Processor_Family";
    this->CPUID_Processor_Family->Size = System::Drawing::Size(70, 17);
    this->CPUID_Processor_Family->Text = L"CPU_Family";
    //
    // CPUID_Processor_Microcode
    //
    this->CPUID_Processor_Microcode->Name = L"CPUID_Processor_Microcode";
    this->CPUID_Processor_Microcode->Size = System::Drawing::Size(118, 17);
    this->CPUID_Processor_Microcode->Text = L"toolStripStatusLabel1";
    //
    // groupBox1
    //
    this->groupBox1->Controls->Add(this->ReadSpecualtionControl);
    this->groupBox1->Controls->Add(this->WriteSpeculationControl);
    this->groupBox1->Controls->Add(this->SSBD_checkBox);
    this->groupBox1->Controls->Add(this->STIBP_checkBox);
    this->groupBox1->Controls->Add(this->IBRS_checkBox);
    this->groupBox1->Location = System::Drawing::Point(0, 6);
    this->groupBox1->Name = L"groupBox1";
    this->groupBox1->Size = System::Drawing::Size(287, 175);
    this->groupBox1->TabIndex = 1;
    this->groupBox1->TabStop = false;
    this->groupBox1->Text = L"Predictor policy Control";
    //
    // ReadSpecualtionControl
    //
    this->ReadSpecualtionControl->Location = System::Drawing::Point(155, 146);
    this->ReadSpecualtionControl->Name = L"ReadSpecualtionControl";
    this->ReadSpecualtionControl->Size = System::Drawing::Size(75, 23);
    this->ReadSpecualtionControl->TabIndex = 5;
    this->ReadSpecualtionControl->Text = L"Read";
    this->ReadSpecualtionControl->UseVisualStyleBackColor = true;
    this->ReadSpecualtionControl->Click += gcnew System::EventHandler(
        this, &MainView::ReadSpecualtionControl_Click);
    //
    // WriteSpeculationControl
    //
    this->WriteSpeculationControl->Location = System::Drawing::Point(7, 146);
    this->WriteSpeculationControl->Name = L"WriteSpeculationControl";
    this->WriteSpeculationControl->Size = System::Drawing::Size(75, 23);
    this->WriteSpeculationControl->TabIndex = 3;
    this->WriteSpeculationControl->Text = L"Write";
    this->WriteSpeculationControl->UseVisualStyleBackColor = true;
    this->WriteSpeculationControl->Click += gcnew System::EventHandler(
        this, &MainView::WriteSpeculationControl_Click);
    //
    // SSBD_checkBox
    //
    this->SSBD_checkBox->AutoSize = true;
    this->SSBD_checkBox->Location = System::Drawing::Point(7, 77);
    this->SSBD_checkBox->Name = L"SSBD_checkBox";
    this->SSBD_checkBox->Size = System::Drawing::Size(223, 17);
    this->SSBD_checkBox->TabIndex = 2;
    this->SSBD_checkBox->Text = L"Speculative Store Bypass Disable (SSBD)";
    this->SSBD_checkBox->UseVisualStyleBackColor = true;
    //
    // STIBP_checkBox
    //
    this->STIBP_checkBox->AutoSize = true;
    this->STIBP_checkBox->Location = System::Drawing::Point(7, 54);
    this->STIBP_checkBox->Name = L"STIBP_checkBox";
    this->STIBP_checkBox->Size = System::Drawing::Size(257, 17);
    this->STIBP_checkBox->TabIndex = 1;
    this->STIBP_checkBox->Text =
        L"Single Thread Indirect Branch Predictors (STIBP)\r\n";
    this->STIBP_checkBox->UseVisualStyleBackColor = true;
    //
    // IBRS_checkBox
    //
    this->IBRS_checkBox->AutoSize = true;
    this->IBRS_checkBox->Location = System::Drawing::Point(7, 31);
    this->IBRS_checkBox->Name = L"IBRS_checkBox";
    this->IBRS_checkBox->Size = System::Drawing::Size(239, 17);
    this->IBRS_checkBox->TabIndex = 0;
    this->IBRS_checkBox->Text =
        L"Indirect Branch Restricted Speculation(IBRS)\r\n";
    this->IBRS_checkBox->UseVisualStyleBackColor = true;
    //
    // L1D_FLUSH_checkBox
    //
    this->L1D_FLUSH_checkBox->AutoSize = true;
    this->L1D_FLUSH_checkBox->Location = System::Drawing::Point(3, 42);
    this->L1D_FLUSH_checkBox->Name = L"L1D_FLUSH_checkBox";
    this->L1D_FLUSH_checkBox->Size = System::Drawing::Size(87, 17);
    this->L1D_FLUSH_checkBox->TabIndex = 4;
    this->L1D_FLUSH_checkBox->Text = L"L1D_FLUSH";
    this->L1D_FLUSH_checkBox->UseVisualStyleBackColor = true;
    //
    // IBPB_checkBox
    //
    this->IBPB_checkBox->AutoSize = true;
    this->IBPB_checkBox->Location = System::Drawing::Point(3, 19);
    this->IBPB_checkBox->Name = L"IBPB_checkBox";
    this->IBPB_checkBox->Size = System::Drawing::Size(214, 17);
    this->IBPB_checkBox->TabIndex = 3;
    this->IBPB_checkBox->Text = L"Indirect Branch Prediction Barrier (IBPB)";
    this->IBPB_checkBox->UseVisualStyleBackColor = true;
    //
    // groupBox2
    //
    this->groupBox2->Controls->Add(
        this->BTIDisabledByNoHardwareSupport_checkBox);
    this->groupBox2->Controls->Add(this->BTIDisabledBySystemPolicy_checkBox);
    this->groupBox2->Controls->Add(this->BTIWindowsSupportEnabled_checkBox);
    this->groupBox2->Controls->Add(this->BTIWindowsSupportPresent_checkBox);
    this->groupBox2->Controls->Add(this->BTIHardwarePresent_checkBox);
    this->groupBox2->Location = System::Drawing::Point(3, 3);
    this->groupBox2->Name = L"groupBox2";
    this->groupBox2->Size = System::Drawing::Size(577, 333);
    this->groupBox2->TabIndex = 2;
    this->groupBox2->TabStop = false;
    this->groupBox2->Text = L"Branch Target Injection";
    //
    // BTIDisabledByNoHardwareSupport_checkBox
    //
    this->BTIDisabledByNoHardwareSupport_checkBox->AutoCheck = false;
    this->BTIDisabledByNoHardwareSupport_checkBox->AutoSize = true;
    this->BTIDisabledByNoHardwareSupport_checkBox->Location =
        System::Drawing::Point(5, 111);
    this->BTIDisabledByNoHardwareSupport_checkBox->Name =
        L"BTIDisabledByNoHardwareSupport_checkBox";
    this->BTIDisabledByNoHardwareSupport_checkBox->Size =
        System::Drawing::Size(503, 17);
    this->BTIDisabledByNoHardwareSupport_checkBox->TabIndex = 5;
    this->BTIDisabledByNoHardwareSupport_checkBox->Text =
        L"Windows OS support for branch target injection mitigation is "
        L"disabled by absence "
        L"of hardware support";
    this->BTIDisabledByNoHardwareSupport_checkBox->UseVisualStyleBackColor =
        true;
    //
    // BTIDisabledBySystemPolicy_checkBox
    //
    this->BTIDisabledBySystemPolicy_checkBox->AutoCheck = false;
    this->BTIDisabledBySystemPolicy_checkBox->AutoSize = true;
    this->BTIDisabledBySystemPolicy_checkBox->Location =
        System::Drawing::Point(6, 88);
    this->BTIDisabledBySystemPolicy_checkBox->Name =
        L"BTIDisabledBySystemPolicy_checkBox";
    this->BTIDisabledBySystemPolicy_checkBox->Size =
        System::Drawing::Size(427, 17);
    this->BTIDisabledBySystemPolicy_checkBox->TabIndex = 4;
    this->BTIDisabledBySystemPolicy_checkBox->Text =
        L"Windows OS support for branch target injection mitigation is "
        L"disabled by system p"
        L"olicy";
    this->BTIDisabledBySystemPolicy_checkBox->UseVisualStyleBackColor = true;
    //
    // BTIWindowsSupportEnabled_checkBox
    //
    this->BTIWindowsSupportEnabled_checkBox->AutoCheck = false;
    this->BTIWindowsSupportEnabled_checkBox->AutoSize = true;
    this->BTIWindowsSupportEnabled_checkBox->Location =
        System::Drawing::Point(6, 65);
    this->BTIWindowsSupportEnabled_checkBox->Name =
        L"BTIWindowsSupportEnabled_checkBox";
    this->BTIWindowsSupportEnabled_checkBox->Size =
        System::Drawing::Size(347, 17);
    this->BTIWindowsSupportEnabled_checkBox->TabIndex = 3;
    this->BTIWindowsSupportEnabled_checkBox->Text =
        L"Windows OS support for branch target injection mitigation is enabled";
    this->BTIWindowsSupportEnabled_checkBox->UseVisualStyleBackColor = true;
    //
    // BTIWindowsSupportPresent_checkBox
    //
    this->BTIWindowsSupportPresent_checkBox->AutoCheck = false;
    this->BTIWindowsSupportPresent_checkBox->AutoSize = true;
    this->BTIWindowsSupportPresent_checkBox->Location =
        System::Drawing::Point(6, 42);
    this->BTIWindowsSupportPresent_checkBox->Name =
        L"BTIWindowsSupportPresent_checkBox";
    this->BTIWindowsSupportPresent_checkBox->Size =
        System::Drawing::Size(344, 17);
    this->BTIWindowsSupportPresent_checkBox->TabIndex = 2;
    this->BTIWindowsSupportPresent_checkBox->Text =
        L"Windows OS support for branch target injection mitigation is present";
    this->BTIWindowsSupportPresent_checkBox->UseVisualStyleBackColor = true;
    //
    // BTIHardwarePresent_checkBox
    //
    this->BTIHardwarePresent_checkBox->AutoCheck = false;
    this->BTIHardwarePresent_checkBox->AutoSize = true;
    this->BTIHardwarePresent_checkBox->Location = System::Drawing::Point(6, 19);
    this->BTIHardwarePresent_checkBox->Name = L"BTIHardwarePresent_checkBox";
    this->BTIHardwarePresent_checkBox->Size = System::Drawing::Size(328, 17);
    this->BTIHardwarePresent_checkBox->TabIndex = 1;
    this->BTIHardwarePresent_checkBox->Text =
        L"Hardware support for branch target injection mitigation is present";
    this->BTIHardwarePresent_checkBox->UseVisualStyleBackColor = true;
    //
    // groupBox3
    //
    this->groupBox3->Controls->Add(this->KVAShadowPcidEnabled_checkBox);
    this->groupBox3->Controls->Add(
        this->KVAShadowWindowsSupportEnabled_checkBox);
    this->groupBox3->Controls->Add(
        this->KVAShadowWindowsSupportPresent_checkBox);
    this->groupBox3->Controls->Add(this->KVAShadowRequired_checkBox);
    this->groupBox3->Location = System::Drawing::Point(3, 3);
    this->groupBox3->Name = L"groupBox3";
    this->groupBox3->Size = System::Drawing::Size(577, 336);
    this->groupBox3->TabIndex = 3;
    this->groupBox3->TabStop = false;
    this->groupBox3->Text = L"Rogue data cache load";
    //
    // KVAShadowPcidEnabled_checkBox
    //
    this->KVAShadowPcidEnabled_checkBox->AutoCheck = false;
    this->KVAShadowPcidEnabled_checkBox->AutoSize = true;
    this->KVAShadowPcidEnabled_checkBox->Location =
        System::Drawing::Point(6, 88);
    this->KVAShadowPcidEnabled_checkBox->Name =
        L"KVAShadowPcidEnabled_checkBox";
    this->KVAShadowPcidEnabled_checkBox->Size = System::Drawing::Size(340, 17);
    this->KVAShadowPcidEnabled_checkBox->TabIndex = 5;
    this->KVAShadowPcidEnabled_checkBox->Text =
        L"Windows OS support for PCID performance optimization is enabled";
    this->KVAShadowPcidEnabled_checkBox->UseVisualStyleBackColor = true;
    //
    // KVAShadowWindowsSupportEnabled_checkBox
    //
    this->KVAShadowWindowsSupportEnabled_checkBox->AutoCheck = false;
    this->KVAShadowWindowsSupportEnabled_checkBox->AutoSize = true;
    this->KVAShadowWindowsSupportEnabled_checkBox->Location =
        System::Drawing::Point(6, 65);
    this->KVAShadowWindowsSupportEnabled_checkBox->Name =
        L"KVAShadowWindowsSupportEnabled_checkBox";
    this->KVAShadowWindowsSupportEnabled_checkBox->Size =
        System::Drawing::Size(281, 17);
    this->KVAShadowWindowsSupportEnabled_checkBox->TabIndex = 4;
    this->KVAShadowWindowsSupportEnabled_checkBox->Text =
        L"Windows OS support for kernel VA shadow is enabled";
    this->KVAShadowWindowsSupportEnabled_checkBox->UseVisualStyleBackColor =
        true;
    //
    // KVAShadowWindowsSupportPresent_checkBox
    //
    this->KVAShadowWindowsSupportPresent_checkBox->AutoCheck = false;
    this->KVAShadowWindowsSupportPresent_checkBox->AutoSize = true;
    this->KVAShadowWindowsSupportPresent_checkBox->Location =
        System::Drawing::Point(6, 42);
    this->KVAShadowWindowsSupportPresent_checkBox->Name =
        L"KVAShadowWindowsSupportPresent_checkBox";
    this->KVAShadowWindowsSupportPresent_checkBox->Size =
        System::Drawing::Size(278, 17);
    this->KVAShadowWindowsSupportPresent_checkBox->TabIndex = 3;
    this->KVAShadowWindowsSupportPresent_checkBox->Text =
        L"Windows OS support for kernel VA shadow is present";
    this->KVAShadowWindowsSupportPresent_checkBox->UseVisualStyleBackColor =
        true;
    //
    // KVAShadowRequired_checkBox
    //
    this->KVAShadowRequired_checkBox->AutoCheck = false;
    this->KVAShadowRequired_checkBox->AutoSize = true;
    this->KVAShadowRequired_checkBox->Location = System::Drawing::Point(6, 19);
    this->KVAShadowRequired_checkBox->Name = L"KVAShadowRequired_checkBox";
    this->KVAShadowRequired_checkBox->Size = System::Drawing::Size(215, 17);
    this->KVAShadowRequired_checkBox->TabIndex = 2;
    this->KVAShadowRequired_checkBox->Text =
        L"Hardware requires kernel VA shadowing";
    this->KVAShadowRequired_checkBox->UseVisualStyleBackColor = true;
    //
    // groupBox4
    //
    this->groupBox4->Controls->Add(
        this->SSBDWindowsSupportEnabledSystemWide_checkBox);
    this->groupBox4->Controls->Add(this->SSBDWindowsSupportPresent_checkBox);
    this->groupBox4->Controls->Add(this->SSBDHardwarePresent_checkBox);
    this->groupBox4->Controls->Add(this->SSBDHardwareVulnerable_checkBox);
    this->groupBox4->Location = System::Drawing::Point(6, 6);
    this->groupBox4->Name = L"groupBox4";
    this->groupBox4->Size = System::Drawing::Size(571, 330);
    this->groupBox4->TabIndex = 4;
    this->groupBox4->TabStop = false;
    this->groupBox4->Text = L"Speculative store bypass";
    //
    // SSBDWindowsSupportEnabledSystemWide_checkBox
    //
    this->SSBDWindowsSupportEnabledSystemWide_checkBox->AutoCheck = false;
    this->SSBDWindowsSupportEnabledSystemWide_checkBox->AutoSize = true;
    this->SSBDWindowsSupportEnabledSystemWide_checkBox->Location =
        System::Drawing::Point(12, 88);
    this->SSBDWindowsSupportEnabledSystemWide_checkBox->Name =
        L"SSBDWindowsSupportEnabledSystemWide_checkBox";
    this->SSBDWindowsSupportEnabledSystemWide_checkBox->Size =
        System::Drawing::Size(407, 17);
    this->SSBDWindowsSupportEnabledSystemWide_checkBox->TabIndex = 6;
    this->SSBDWindowsSupportEnabledSystemWide_checkBox->Text =
        L"Windows OS support for speculative store bypass disable is enabled "
        L"system-wide";
    this->SSBDWindowsSupportEnabledSystemWide_checkBox
        ->UseVisualStyleBackColor = true;
    //
    // SSBDWindowsSupportPresent_checkBox
    //
    this->SSBDWindowsSupportPresent_checkBox->AutoCheck = false;
    this->SSBDWindowsSupportPresent_checkBox->AutoSize = true;
    this->SSBDWindowsSupportPresent_checkBox->Location =
        System::Drawing::Point(12, 65);
    this->SSBDWindowsSupportPresent_checkBox->Name =
        L"SSBDWindowsSupportPresent_checkBox";
    this->SSBDWindowsSupportPresent_checkBox->Size =
        System::Drawing::Size(344, 17);
    this->SSBDWindowsSupportPresent_checkBox->TabIndex = 5;
    this->SSBDWindowsSupportPresent_checkBox->Text =
        L"Windows OS support for speculative store bypass disable is present";
    this->SSBDWindowsSupportPresent_checkBox->UseVisualStyleBackColor = true;
    //
    // SSBDHardwarePresent_checkBox
    //
    this->SSBDHardwarePresent_checkBox->AutoCheck = false;
    this->SSBDHardwarePresent_checkBox->AutoSize = true;
    this->SSBDHardwarePresent_checkBox->Location =
        System::Drawing::Point(12, 42);
    this->SSBDHardwarePresent_checkBox->Name = L"SSBDHardwarePresent_checkBox";
    this->SSBDHardwarePresent_checkBox->Size = System::Drawing::Size(328, 17);
    this->SSBDHardwarePresent_checkBox->TabIndex = 4;
    this->SSBDHardwarePresent_checkBox->Text =
        L"Hardware support for speculative store bypass disable is present";
    this->SSBDHardwarePresent_checkBox->UseVisualStyleBackColor = true;
    //
    // SSBDHardwareVulnerable_checkBox
    //
    this->SSBDHardwareVulnerable_checkBox->AutoCheck = false;
    this->SSBDHardwareVulnerable_checkBox->AutoSize = true;
    this->SSBDHardwareVulnerable_checkBox->Location =
        System::Drawing::Point(12, 19);
    this->SSBDHardwareVulnerable_checkBox->Name =
        L"SSBDHardwareVulnerable_checkBox";
    this->SSBDHardwareVulnerable_checkBox->Size =
        System::Drawing::Size(265, 17);
    this->SSBDHardwareVulnerable_checkBox->TabIndex = 3;
    this->SSBDHardwareVulnerable_checkBox->Text =
        L"Hardware is vulnerable to speculative store bypass";
    this->SSBDHardwareVulnerable_checkBox->UseVisualStyleBackColor = true;
    //
    // groupBox5
    //
    this->groupBox5->Controls->Add(this->L1TFWindowsSupportEnabled_checkBox);
    this->groupBox5->Controls->Add(this->L1TFWindowsSupportPresent_checkBox);
    this->groupBox5->Controls->Add(this->L1TFHardwareVulnerable_checkBox);
    this->groupBox5->Location = System::Drawing::Point(3, 3);
    this->groupBox5->Name = L"groupBox5";
    this->groupBox5->Size = System::Drawing::Size(577, 333);
    this->groupBox5->TabIndex = 5;
    this->groupBox5->TabStop = false;
    this->groupBox5->Text = L"L1 terminal fault";
    //
    // L1TFWindowsSupportEnabled_checkBox
    //
    this->L1TFWindowsSupportEnabled_checkBox->AutoCheck = false;
    this->L1TFWindowsSupportEnabled_checkBox->AutoSize = true;
    this->L1TFWindowsSupportEnabled_checkBox->Location =
        System::Drawing::Point(5, 65);
    this->L1TFWindowsSupportEnabled_checkBox->Name =
        L"L1TFWindowsSupportEnabled_checkBox";
    this->L1TFWindowsSupportEnabled_checkBox->Size =
        System::Drawing::Size(316, 17);
    this->L1TFWindowsSupportEnabled_checkBox->TabIndex = 5;
    this->L1TFWindowsSupportEnabled_checkBox->Text =
        L"Windows OS support for L1 terminal fault mitigation is enabled";
    this->L1TFWindowsSupportEnabled_checkBox->UseVisualStyleBackColor = true;
    //
    // L1TFWindowsSupportPresent_checkBox
    //
    this->L1TFWindowsSupportPresent_checkBox->AutoCheck = false;
    this->L1TFWindowsSupportPresent_checkBox->AutoSize = true;
    this->L1TFWindowsSupportPresent_checkBox->Location =
        System::Drawing::Point(5, 42);
    this->L1TFWindowsSupportPresent_checkBox->Name =
        L"L1TFWindowsSupportPresent_checkBox";
    this->L1TFWindowsSupportPresent_checkBox->Size =
        System::Drawing::Size(313, 17);
    this->L1TFWindowsSupportPresent_checkBox->TabIndex = 4;
    this->L1TFWindowsSupportPresent_checkBox->Text =
        L"Windows OS support for L1 terminal fault mitigation is present";
    this->L1TFWindowsSupportPresent_checkBox->UseVisualStyleBackColor = true;
    //
    // L1TFHardwareVulnerable_checkBox
    //
    this->L1TFHardwareVulnerable_checkBox->AutoCheck = false;
    this->L1TFHardwareVulnerable_checkBox->AutoSize = true;
    this->L1TFHardwareVulnerable_checkBox->Location =
        System::Drawing::Point(6, 19);
    this->L1TFHardwareVulnerable_checkBox->Name =
        L"L1TFHardwareVulnerable_checkBox";
    this->L1TFHardwareVulnerable_checkBox->Size =
        System::Drawing::Size(223, 17);
    this->L1TFHardwareVulnerable_checkBox->TabIndex = 3;
    this->L1TFHardwareVulnerable_checkBox->Text =
        L"Hardware is vulnerable to L1 terminal fault";
    this->L1TFHardwareVulnerable_checkBox->UseVisualStyleBackColor = true;
    //
    // tabControl1
    //
    this->tabControl1->Controls->Add(this->tabPage1);
    this->tabControl1->Controls->Add(this->tabPage2);
    this->tabControl1->Controls->Add(this->tabPage3);
    this->tabControl1->Controls->Add(this->tabPage4);
    this->tabControl1->Controls->Add(this->tabPage5);
    this->tabControl1->Location = System::Drawing::Point(0, 1);
    this->tabControl1->Name = L"tabControl1";
    this->tabControl1->SelectedIndex = 0;
    this->tabControl1->Size = System::Drawing::Size(699, 365);
    this->tabControl1->TabIndex = 5;
    //
    // tabPage1
    //
    this->tabPage1->Controls->Add(this->groupBox8);
    this->tabPage1->Controls->Add(this->IA32_ARCH_CAPABILITIES_groupBox);
    this->tabPage1->Controls->Add(this->groupBox7);
    this->tabPage1->Controls->Add(this->groupBox6);
    this->tabPage1->Controls->Add(this->groupBox1);
    this->tabPage1->Location = System::Drawing::Point(4, 22);
    this->tabPage1->Name = L"tabPage1";
    this->tabPage1->Padding = System::Windows::Forms::Padding(3);
    this->tabPage1->Size = System::Drawing::Size(691, 339);
    this->tabPage1->TabIndex = 0;
    this->tabPage1->Text = L"MSR Control";
    this->tabPage1->UseVisualStyleBackColor = true;
    //
    // groupBox8
    //
    this->groupBox8->Controls->Add(this->button2);
    this->groupBox8->Controls->Add(this->button1);
    this->groupBox8->Controls->Add(this->PCID_checkBox);
    this->groupBox8->Controls->Add(this->SMEP_checkBox);
    this->groupBox8->Controls->Add(this->SMAP_checkBox);
    this->groupBox8->Enabled = false;
    this->groupBox8->Location = System::Drawing::Point(503, 181);
    this->groupBox8->Name = L"groupBox8";
    this->groupBox8->Size = System::Drawing::Size(180, 152);
    this->groupBox8->TabIndex = 5;
    this->groupBox8->TabStop = false;
    this->groupBox8->Text = L"CR4 Control";
    //
    // button2
    //
    this->button2->Location = System::Drawing::Point(99, 120);
    this->button2->Name = L"button2";
    this->button2->Size = System::Drawing::Size(75, 23);
    this->button2->TabIndex = 11;
    this->button2->Text = L"Write";
    this->button2->UseVisualStyleBackColor = true;
    //
    // button1
    //
    this->button1->Location = System::Drawing::Point(6, 120);
    this->button1->Name = L"button1";
    this->button1->Size = System::Drawing::Size(75, 23);
    this->button1->TabIndex = 10;
    this->button1->Text = L"Read";
    this->button1->UseVisualStyleBackColor = true;
    //
    // PCID_checkBox
    //
    this->PCID_checkBox->AutoCheck = false;
    this->PCID_checkBox->AutoSize = true;
    this->PCID_checkBox->Location = System::Drawing::Point(6, 65);
    this->PCID_checkBox->Name = L"PCID_checkBox";
    this->PCID_checkBox->Size = System::Drawing::Size(51, 17);
    this->PCID_checkBox->TabIndex = 9;
    this->PCID_checkBox->Text = L"PCID";
    this->PCID_checkBox->UseVisualStyleBackColor = true;
    //
    // SMEP_checkBox
    //
    this->SMEP_checkBox->AutoCheck = false;
    this->SMEP_checkBox->AutoSize = true;
    this->SMEP_checkBox->Location = System::Drawing::Point(6, 42);
    this->SMEP_checkBox->Name = L"SMEP_checkBox";
    this->SMEP_checkBox->Size = System::Drawing::Size(56, 17);
    this->SMEP_checkBox->TabIndex = 8;
    this->SMEP_checkBox->Text = L"SMEP";
    this->SMEP_checkBox->UseVisualStyleBackColor = true;
    //
    // SMAP_checkBox
    //
    this->SMAP_checkBox->AutoCheck = false;
    this->SMAP_checkBox->AutoSize = true;
    this->SMAP_checkBox->Location = System::Drawing::Point(6, 19);
    this->SMAP_checkBox->Name = L"SMAP_checkBox";
    this->SMAP_checkBox->Size = System::Drawing::Size(56, 17);
    this->SMAP_checkBox->TabIndex = 7;
    this->SMAP_checkBox->Text = L"SMAP";
    this->SMAP_checkBox->UseVisualStyleBackColor = true;
    //
    // IA32_ARCH_CAPABILITIES_groupBox
    //
    this->IA32_ARCH_CAPABILITIES_groupBox->Controls->Add(this->SSB_NO_checkBox);
    this->IA32_ARCH_CAPABILITIES_groupBox->Controls->Add(
        this->SKIP_L1DFL_VMENTRY_checkBox);
    this->IA32_ARCH_CAPABILITIES_groupBox->Controls->Add(this->RSBA_checkBox);
    this->IA32_ARCH_CAPABILITIES_groupBox->Controls->Add(
        this->IBRS_ALL_checkBox);
    this->IA32_ARCH_CAPABILITIES_groupBox->Controls->Add(
        this->RDCL_NO_checkBox);
    this->IA32_ARCH_CAPABILITIES_groupBox->Location =
        System::Drawing::Point(292, 181);
    this->IA32_ARCH_CAPABILITIES_groupBox->Name =
        L"IA32_ARCH_CAPABILITIES_groupBox";
    this->IA32_ARCH_CAPABILITIES_groupBox->Size =
        System::Drawing::Size(205, 155);
    this->IA32_ARCH_CAPABILITIES_groupBox->TabIndex = 4;
    this->IA32_ARCH_CAPABILITIES_groupBox->TabStop = false;
    this->IA32_ARCH_CAPABILITIES_groupBox->Text = L"IA32_ARCH_CAPABILITIES MSR";
    //
    // SSB_NO_checkBox
    //
    this->SSB_NO_checkBox->AutoCheck = false;
    this->SSB_NO_checkBox->AutoSize = true;
    this->SSB_NO_checkBox->Location = System::Drawing::Point(6, 111);
    this->SSB_NO_checkBox->Name = L"SSB_NO_checkBox";
    this->SSB_NO_checkBox->Size = System::Drawing::Size(69, 17);
    this->SSB_NO_checkBox->TabIndex = 6;
    this->SSB_NO_checkBox->Text = L"SSB_NO";
    this->SSB_NO_checkBox->UseVisualStyleBackColor = true;
    //
    // SKIP_L1DFL_VMENTRY_checkBox
    //
    this->SKIP_L1DFL_VMENTRY_checkBox->AutoCheck = false;
    this->SKIP_L1DFL_VMENTRY_checkBox->AutoSize = true;
    this->SKIP_L1DFL_VMENTRY_checkBox->Location = System::Drawing::Point(6, 88);
    this->SKIP_L1DFL_VMENTRY_checkBox->Name = L"SKIP_L1DFL_VMENTRY_checkBox";
    this->SKIP_L1DFL_VMENTRY_checkBox->Size = System::Drawing::Size(147, 17);
    this->SKIP_L1DFL_VMENTRY_checkBox->TabIndex = 5;
    this->SKIP_L1DFL_VMENTRY_checkBox->Text = L"SKIP_L1DFL_VMENTRY";
    this->SKIP_L1DFL_VMENTRY_checkBox->UseVisualStyleBackColor = true;
    //
    // RSBA_checkBox
    //
    this->RSBA_checkBox->AutoCheck = false;
    this->RSBA_checkBox->AutoSize = true;
    this->RSBA_checkBox->Location = System::Drawing::Point(6, 65);
    this->RSBA_checkBox->Name = L"RSBA_checkBox";
    this->RSBA_checkBox->Size = System::Drawing::Size(55, 17);
    this->RSBA_checkBox->TabIndex = 4;
    this->RSBA_checkBox->Text = L"RSBA";
    this->RSBA_checkBox->UseVisualStyleBackColor = true;
    //
    // IBRS_ALL_checkBox
    //
    this->IBRS_ALL_checkBox->AutoCheck = false;
    this->IBRS_ALL_checkBox->AutoSize = true;
    this->IBRS_ALL_checkBox->Location = System::Drawing::Point(6, 42);
    this->IBRS_ALL_checkBox->Name = L"IBRS_ALL_checkBox";
    this->IBRS_ALL_checkBox->Size = System::Drawing::Size(76, 17);
    this->IBRS_ALL_checkBox->TabIndex = 3;
    this->IBRS_ALL_checkBox->Text = L"IBRS_ALL";
    this->IBRS_ALL_checkBox->UseVisualStyleBackColor = true;
    //
    // RDCL_NO_checkBox
    //
    this->RDCL_NO_checkBox->AutoCheck = false;
    this->RDCL_NO_checkBox->AutoSize = true;
    this->RDCL_NO_checkBox->Location = System::Drawing::Point(6, 19);
    this->RDCL_NO_checkBox->Name = L"RDCL_NO_checkBox";
    this->RDCL_NO_checkBox->Size = System::Drawing::Size(77, 17);
    this->RDCL_NO_checkBox->TabIndex = 2;
    this->RDCL_NO_checkBox->Text = L"RDCL_NO";
    this->RDCL_NO_checkBox->UseVisualStyleBackColor = true;
    //
    // groupBox7
    //
    this->groupBox7->Controls->Add(this->PCID_support_checkBox);
    this->groupBox7->Controls->Add(this->INVPCID_support_checkBox);
    this->groupBox7->Controls->Add(this->SMEP_support_checkBox);
    this->groupBox7->Controls->Add(this->SMAP_support_checkBox);
    this->groupBox7->Controls->Add(this->SSBD_support_checkBox);
    this->groupBox7->Controls->Add(
        this->IA32_ARCH_CAPABILITIES_support_checkBox);
    this->groupBox7->Controls->Add(this->L1D_FLUSH_support_checkBox);
    this->groupBox7->Controls->Add(this->STIBP_support_checkBox);
    this->groupBox7->Controls->Add(this->IBRS_AND_IBPB_support_checkBox);
    this->groupBox7->Location = System::Drawing::Point(292, 6);
    this->groupBox7->Name = L"groupBox7";
    this->groupBox7->Size = System::Drawing::Size(385, 175);
    this->groupBox7->TabIndex = 3;
    this->groupBox7->TabStop = false;
    this->groupBox7->Text = L"CPUID Information";
    //
    // PCID_support_checkBox
    //
    this->PCID_support_checkBox->AutoCheck = false;
    this->PCID_support_checkBox->AutoSize = true;
    this->PCID_support_checkBox->Location = System::Drawing::Point(211, 94);
    this->PCID_support_checkBox->Name = L"PCID_support_checkBox";
    this->PCID_support_checkBox->Size = System::Drawing::Size(89, 17);
    this->PCID_support_checkBox->TabIndex = 9;
    this->PCID_support_checkBox->Text = L"PCID support";
    this->PCID_support_checkBox->UseVisualStyleBackColor = true;
    //
    // INVPCID_support_checkBox
    //
    this->INVPCID_support_checkBox->AutoCheck = false;
    this->INVPCID_support_checkBox->AutoSize = true;
    this->INVPCID_support_checkBox->Location = System::Drawing::Point(211, 71);
    this->INVPCID_support_checkBox->Name = L"INVPCID_support_checkBox";
    this->INVPCID_support_checkBox->Size = System::Drawing::Size(107, 17);
    this->INVPCID_support_checkBox->TabIndex = 8;
    this->INVPCID_support_checkBox->Text = L"INVPCID support";
    this->INVPCID_support_checkBox->UseVisualStyleBackColor = true;
    //
    // SMEP_support_checkBox
    //
    this->SMEP_support_checkBox->AutoCheck = false;
    this->SMEP_support_checkBox->AutoSize = true;
    this->SMEP_support_checkBox->Location = System::Drawing::Point(211, 48);
    this->SMEP_support_checkBox->Name = L"SMEP_support_checkBox";
    this->SMEP_support_checkBox->Size = System::Drawing::Size(94, 17);
    this->SMEP_support_checkBox->TabIndex = 7;
    this->SMEP_support_checkBox->Text = L"SMEP support";
    this->SMEP_support_checkBox->UseVisualStyleBackColor = true;
    //
    // SMAP_support_checkBox
    //
    this->SMAP_support_checkBox->AutoCheck = false;
    this->SMAP_support_checkBox->AutoSize = true;
    this->SMAP_support_checkBox->Location = System::Drawing::Point(211, 25);
    this->SMAP_support_checkBox->Name = L"SMAP_support_checkBox";
    this->SMAP_support_checkBox->Size = System::Drawing::Size(94, 17);
    this->SMAP_support_checkBox->TabIndex = 6;
    this->SMAP_support_checkBox->Text = L"SMAP support";
    this->SMAP_support_checkBox->UseVisualStyleBackColor = true;
    //
    // SSBD_support_checkBox
    //
    this->SSBD_support_checkBox->AutoCheck = false;
    this->SSBD_support_checkBox->AutoSize = true;
    this->SSBD_support_checkBox->Location = System::Drawing::Point(6, 117);
    this->SSBD_support_checkBox->Name = L"SSBD_support_checkBox";
    this->SSBD_support_checkBox->Size = System::Drawing::Size(93, 17);
    this->SSBD_support_checkBox->TabIndex = 5;
    this->SSBD_support_checkBox->Text = L"SSBD support";
    this->SSBD_support_checkBox->UseVisualStyleBackColor = true;
    //
    // IA32_ARCH_CAPABILITIES_support_checkBox
    //
    this->IA32_ARCH_CAPABILITIES_support_checkBox->AutoCheck = false;
    this->IA32_ARCH_CAPABILITIES_support_checkBox->AutoSize = true;
    this->IA32_ARCH_CAPABILITIES_support_checkBox->Location =
        System::Drawing::Point(6, 94);
    this->IA32_ARCH_CAPABILITIES_support_checkBox->Name =
        L"IA32_ARCH_CAPABILITIES_support_checkBox";
    this->IA32_ARCH_CAPABILITIES_support_checkBox->Size =
        System::Drawing::Size(199, 17);
    this->IA32_ARCH_CAPABILITIES_support_checkBox->TabIndex = 4;
    this->IA32_ARCH_CAPABILITIES_support_checkBox->Text =
        L"IA32_ARCH_CAPABILITIES support";
    this->IA32_ARCH_CAPABILITIES_support_checkBox->UseVisualStyleBackColor =
        true;
    //
    // L1D_FLUSH_support_checkBox
    //
    this->L1D_FLUSH_support_checkBox->AutoCheck = false;
    this->L1D_FLUSH_support_checkBox->AutoSize = true;
    this->L1D_FLUSH_support_checkBox->Location = System::Drawing::Point(6, 71);
    this->L1D_FLUSH_support_checkBox->Name = L"L1D_FLUSH_support_checkBox";
    this->L1D_FLUSH_support_checkBox->Size = System::Drawing::Size(125, 17);
    this->L1D_FLUSH_support_checkBox->TabIndex = 3;
    this->L1D_FLUSH_support_checkBox->Text = L"L1D_FLUSH support";
    this->L1D_FLUSH_support_checkBox->UseVisualStyleBackColor = true;
    //
    // STIBP_support_checkBox
    //
    this->STIBP_support_checkBox->AutoCheck = false;
    this->STIBP_support_checkBox->AutoSize = true;
    this->STIBP_support_checkBox->Location = System::Drawing::Point(6, 48);
    this->STIBP_support_checkBox->Name = L"STIBP_support_checkBox";
    this->STIBP_support_checkBox->Size = System::Drawing::Size(95, 17);
    this->STIBP_support_checkBox->TabIndex = 2;
    this->STIBP_support_checkBox->Text = L"STIBP support";
    this->STIBP_support_checkBox->UseVisualStyleBackColor = true;
    //
    // IBRS_AND_IBPB_support_checkBox
    //
    this->IBRS_AND_IBPB_support_checkBox->AutoCheck = false;
    this->IBRS_AND_IBPB_support_checkBox->AutoSize = true;
    this->IBRS_AND_IBPB_support_checkBox->Location =
        System::Drawing::Point(6, 25);
    this->IBRS_AND_IBPB_support_checkBox->Name =
        L"IBRS_AND_IBPB_support_checkBox";
    this->IBRS_AND_IBPB_support_checkBox->Size = System::Drawing::Size(119, 17);
    this->IBRS_AND_IBPB_support_checkBox->TabIndex = 1;
    this->IBRS_AND_IBPB_support_checkBox->Text = L"IBRS&&IBPB support";
    this->IBRS_AND_IBPB_support_checkBox->UseVisualStyleBackColor = true;
    //
    // groupBox6
    //
    this->groupBox6->Controls->Add(this->WriteWORegisters);
    this->groupBox6->Controls->Add(this->IBPB_checkBox);
    this->groupBox6->Controls->Add(this->L1D_FLUSH_checkBox);
    this->groupBox6->Location = System::Drawing::Point(0, 181);
    this->groupBox6->Name = L"groupBox6";
    this->groupBox6->Size = System::Drawing::Size(287, 155);
    this->groupBox6->TabIndex = 2;
    this->groupBox6->TabStop = false;
    this->groupBox6->Text = L"WriteOnlyRegistres";
    //
    // WriteWORegisters
    //
    this->WriteWORegisters->Location = System::Drawing::Point(3, 120);
    this->WriteWORegisters->Name = L"WriteWORegisters";
    this->WriteWORegisters->Size = System::Drawing::Size(75, 23);
    this->WriteWORegisters->TabIndex = 5;
    this->WriteWORegisters->Text = L"Write";
    this->WriteWORegisters->UseVisualStyleBackColor = true;
    this->WriteWORegisters->Click +=
        gcnew System::EventHandler(this, &MainView::WriteWORegisters_Click);
    //
    // tabPage2
    //
    this->tabPage2->Controls->Add(this->groupBox4);
    this->tabPage2->Location = System::Drawing::Point(4, 22);
    this->tabPage2->Name = L"tabPage2";
    this->tabPage2->Padding = System::Windows::Forms::Padding(3);
    this->tabPage2->Size = System::Drawing::Size(691, 339);
    this->tabPage2->TabIndex = 1;
    this->tabPage2->Text = L"Speculative store bypass";
    this->tabPage2->UseVisualStyleBackColor = true;
    //
    // tabPage3
    //
    this->tabPage3->Controls->Add(this->groupBox3);
    this->tabPage3->Location = System::Drawing::Point(4, 22);
    this->tabPage3->Name = L"tabPage3";
    this->tabPage3->Size = System::Drawing::Size(691, 339);
    this->tabPage3->TabIndex = 2;
    this->tabPage3->Text = L"Rogue data cache load";
    this->tabPage3->UseVisualStyleBackColor = true;
    //
    // tabPage4
    //
    this->tabPage4->Controls->Add(this->groupBox5);
    this->tabPage4->Location = System::Drawing::Point(4, 22);
    this->tabPage4->Name = L"tabPage4";
    this->tabPage4->Size = System::Drawing::Size(691, 339);
    this->tabPage4->TabIndex = 3;
    this->tabPage4->Text = L"L1 terminal fault";
    this->tabPage4->UseVisualStyleBackColor = true;
    //
    // tabPage5
    //
    this->tabPage5->Controls->Add(this->groupBox2);
    this->tabPage5->Location = System::Drawing::Point(4, 22);
    this->tabPage5->Name = L"tabPage5";
    this->tabPage5->Size = System::Drawing::Size(691, 339);
    this->tabPage5->TabIndex = 4;
    this->tabPage5->Text = L"Branch Target Injection";
    this->tabPage5->UseVisualStyleBackColor = true;
    //
    // MainView
    //
    this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
    this->ClientSize = System::Drawing::Size(699, 391);
    this->Controls->Add(this->tabControl1);
    this->Controls->Add(this->statusStrip1);
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
    this->MaximizeBox = false;
    this->Name = L"MainView";
    this->Text = L"Spectrator";
    this->statusStrip1->ResumeLayout(false);
    this->statusStrip1->PerformLayout();
    this->groupBox1->ResumeLayout(false);
    this->groupBox1->PerformLayout();
    this->groupBox2->ResumeLayout(false);
    this->groupBox2->PerformLayout();
    this->groupBox3->ResumeLayout(false);
    this->groupBox3->PerformLayout();
    this->groupBox4->ResumeLayout(false);
    this->groupBox4->PerformLayout();
    this->groupBox5->ResumeLayout(false);
    this->groupBox5->PerformLayout();
    this->tabControl1->ResumeLayout(false);
    this->tabPage1->ResumeLayout(false);
    this->groupBox8->ResumeLayout(false);
    this->groupBox8->PerformLayout();
    this->IA32_ARCH_CAPABILITIES_groupBox->ResumeLayout(false);
    this->IA32_ARCH_CAPABILITIES_groupBox->PerformLayout();
    this->groupBox7->ResumeLayout(false);
    this->groupBox7->PerformLayout();
    this->groupBox6->ResumeLayout(false);
    this->groupBox6->PerformLayout();
    this->tabPage2->ResumeLayout(false);
    this->tabPage3->ResumeLayout(false);
    this->tabPage4->ResumeLayout(false);
    this->tabPage5->ResumeLayout(false);
    this->ResumeLayout(false);
    this->PerformLayout();
  }
#pragma endregion
private:
  System::Void WriteSpeculationControl_Click(System::Object ^ sender,
                                             System::EventArgs ^ e) {

    _SpeculationControl->SetSpeculationControlFlagState(
        IA32_SPEC_CTRL_MSR_FLAG_IBRS, IBRS_checkBox->Checked);
    _SpeculationControl->SetSpeculationControlFlagState(
        IA32_SPEC_CTRL_MSR_FLAG_SSBD, SSBD_checkBox->Checked);
    _SpeculationControl->SetSpeculationControlFlagState(
        IA32_SPEC_CTRL_MSR_FLAG_STIBP, STIBP_checkBox->Checked);
    _SpeculationControl->ApplyPerPackageSpeculationControl();
    _SpeculationControl->GetSpeculationControlSettings();
    IBRS_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_IBRS);
    STIBP_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_STIBP);
    SSBD_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_SSBD);
  }

private:
  System::Void ReadSpecualtionControl_Click(System::Object ^ sender,
                                            System::EventArgs ^ e) {
    _SpeculationControl->GetSpeculationControlSettings();
    IBRS_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_IBRS);
    STIBP_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_STIBP);
    SSBD_checkBox->Checked =
        _SpeculationControl->GetSpeculationControlSettingsActivity(
            IA32_SPEC_CTRL_MSR_FLAG_SSBD);
  }

private:
  System::Void WriteWORegisters_Click(System::Object ^ sender,
                                      System::EventArgs ^ e) {

    if (_CPUInformation->GetProcessorFeatureFlagsExtendedExEDX(
            ProcessorFeatureFlagsExtendedExEDX_IBRS_IBPB)) {
      _SpeculationControl->SetStatePredictionControl(
          IA32_PRED_CMD_MSR_FLAG_IBPB, IBPB_checkBox->Checked);
      _SpeculationControl->ApplyPerPackagePredictionControl();
    }

    if (_CPUInformation->GetProcessorFeatureFlagsExtendedExEDX(
            ProcessorFeatureFlagsExtendedExEDX_L1D_FLUSH)) {
      _SpeculationControl->SetStateFlushCaches(
          IA32_FLUSH_CMD_MSR_FLAG_IA32_FLUSH_CMD, L1D_FLUSH_checkBox->Checked);
      _SpeculationControl->ApplyPerPackageFlushCachesControl();
    }
  }
};
} // namespace Spectrator
