#pragma once
#include "list.h"
#include "polinom.h"
#include "stdafx.h"

namespace PolynomialsFrontend {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for PolyUi
/// </summary>
public
ref class PolyUi : public System::Windows::Forms::Form {
  List<Polinom>* pols = new List<Polinom>();

 public:
  PolyUi(void) { InitializeComponent(); }

 protected:
  /// <summary>
  /// Clean up any resources being used.
  /// </summary>
  ~PolyUi() {
    if (components) {
      delete components;
    }
  }

 private:
 protected:
 private:
 private:
 private:
  System::Windows::Forms::TextBox ^ NewStr;

 private:
  System::Windows::Forms::ListBox ^ Bank;

 private:
  System::Windows::Forms::Label ^ HintDoSum;

 private:
  System::Windows::Forms::Label ^ HintNewStr;

 private:
  System::Windows::Forms::Label ^ HintBank;

 private:
  System::Windows::Forms::Label ^ label1;

 private:
  System::Windows::Forms::TextBox ^ SumNA;

 private:
  System::Windows::Forms::TextBox ^ SumStrA;

 private:
 private:
 private:
 private:
  System::Windows::Forms::Label ^ label2;

 private:
  System::Windows::Forms::TextBox ^ SumNB;

 private:
  System::Windows::Forms::TextBox ^ SumStrB;

 private:
 private:
 private:
  System::Windows::Forms::Label ^ label3;

 private:
  System::Windows::Forms::Label ^ hint;

 private:
 private:
 private:
  System::Windows::Forms::Label ^ label5;

 private:
  System::Windows::Forms::Label ^ SumRes;

 private:


 private:


 private:
 private:
 private:
 private:


 private:
  System::Windows::Forms::Label ^ MultRes;

 private:
 private:
  System::Windows::Forms::Label ^ label8;

 private:
  System::Windows::Forms::Label ^ label9;

 private:
  System::Windows::Forms::Label ^ label10;

 private:
  System::Windows::Forms::TextBox ^ MultStrB;

 private:


 private:
  System::Windows::Forms::TextBox ^ MultNB;

 private:


 private:
  System::Windows::Forms::Label ^ label11;

 private:
  System::Windows::Forms::TextBox ^ MultStrA;

 private:
  System::Windows::Forms::TextBox ^ MultNA;

 private:


 private:


 private:
  System::Windows::Forms::Label ^ label12;

 private:
  System::Windows::Forms::Label ^ label13;

 private:
  System::Windows::Forms::Label ^ DerRes;

 private:
 private:
  System::Windows::Forms::Label ^ label15;

 private:
  System::Windows::Forms::TextBox ^ DerStr;

 private:
  System::Windows::Forms::TextBox ^ DerN;

 private:


 private:


 private:
  System::Windows::Forms::Label ^ label16;

 private:
  System::Windows::Forms::Label ^ label17;

 private:
  System::Windows::Forms::Label ^ RootRes;

 private:
 private:
  System::Windows::Forms::Label ^ label19;

 private:
  System::Windows::Forms::TextBox ^ RootStr;

 private:
  System::Windows::Forms::TextBox ^ RootN;

 private:


 private:


 private:
  System::Windows::Forms::Label ^ label20;

 private:
  System::Windows::Forms::Label ^ label21;

 private:
  System::Windows::Forms::Label ^ ValRes;

 private:
 private:
  System::Windows::Forms::Label ^ label23;

 private:
  System::Windows::Forms::TextBox ^ textBox13;

 private:
  System::Windows::Forms::TextBox ^ textBox14;

 private:
  System::Windows::Forms::Label ^ label24;

 private:
  System::Windows::Forms::Label ^ label25;

 private:
  System::Windows::Forms::TextBox ^ ValVars;

 private:


 private:
  System::Windows::Forms::Label ^ label26;

 private:
  System::Windows::Forms::TextBox ^ DerVar;

 private:


 private:
  System::Windows::Forms::Label ^ label4;

 private:
  System::Windows::Forms::Button ^ PushButton;

 private:


 private:
  System::Windows::Forms::Label ^ label6;

 private:
  System::Windows::Forms::TextBox ^ DerTimes;

 private:
  System::Windows::Forms::Button ^ FromFile;

 private:
  System::Windows::Forms::Button ^ SumPush;

 private:
  System::Windows::Forms::Button ^ MultPush;

 private:
  System::Windows::Forms::Button ^ DerPush;

 private:


 private:


 private:


 private:
 private:
 private:
 private:
 protected:
 private:
 private:
 private:
 private:
 protected:
 private:
  /// <summary>
  /// Required designer variable.
  /// </summary>
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  /// <summary>
  /// Required method for Designer support - do not modify
  /// the contents of this method with the code editor.
  /// </summary>
  void InitializeComponent(void) {
    this->PushButton = (gcnew System::Windows::Forms::Button());
    this->NewStr = (gcnew System::Windows::Forms::TextBox());
    this->Bank = (gcnew System::Windows::Forms::ListBox());
    this->HintDoSum = (gcnew System::Windows::Forms::Label());
    this->HintNewStr = (gcnew System::Windows::Forms::Label());
    this->HintBank = (gcnew System::Windows::Forms::Label());
    this->label1 = (gcnew System::Windows::Forms::Label());
    this->SumNA = (gcnew System::Windows::Forms::TextBox());
    this->SumStrA = (gcnew System::Windows::Forms::TextBox());
    this->label2 = (gcnew System::Windows::Forms::Label());
    this->SumNB = (gcnew System::Windows::Forms::TextBox());
    this->SumStrB = (gcnew System::Windows::Forms::TextBox());
    this->label3 = (gcnew System::Windows::Forms::Label());
    this->hint = (gcnew System::Windows::Forms::Label());
    this->label5 = (gcnew System::Windows::Forms::Label());
    this->SumRes = (gcnew System::Windows::Forms::Label());
    this->MultRes = (gcnew System::Windows::Forms::Label());
    this->label8 = (gcnew System::Windows::Forms::Label());
    this->label9 = (gcnew System::Windows::Forms::Label());
    this->label10 = (gcnew System::Windows::Forms::Label());
    this->MultStrB = (gcnew System::Windows::Forms::TextBox());
    this->MultNB = (gcnew System::Windows::Forms::TextBox());
    this->label11 = (gcnew System::Windows::Forms::Label());
    this->MultStrA = (gcnew System::Windows::Forms::TextBox());
    this->MultNA = (gcnew System::Windows::Forms::TextBox());
    this->label12 = (gcnew System::Windows::Forms::Label());
    this->label13 = (gcnew System::Windows::Forms::Label());
    this->DerRes = (gcnew System::Windows::Forms::Label());
    this->label15 = (gcnew System::Windows::Forms::Label());
    this->DerStr = (gcnew System::Windows::Forms::TextBox());
    this->DerN = (gcnew System::Windows::Forms::TextBox());
    this->label16 = (gcnew System::Windows::Forms::Label());
    this->label17 = (gcnew System::Windows::Forms::Label());
    this->RootRes = (gcnew System::Windows::Forms::Label());
    this->label19 = (gcnew System::Windows::Forms::Label());
    this->RootStr = (gcnew System::Windows::Forms::TextBox());
    this->RootN = (gcnew System::Windows::Forms::TextBox());
    this->label20 = (gcnew System::Windows::Forms::Label());
    this->label21 = (gcnew System::Windows::Forms::Label());
    this->ValRes = (gcnew System::Windows::Forms::Label());
    this->label23 = (gcnew System::Windows::Forms::Label());
    this->textBox13 = (gcnew System::Windows::Forms::TextBox());
    this->textBox14 = (gcnew System::Windows::Forms::TextBox());
    this->label24 = (gcnew System::Windows::Forms::Label());
    this->label25 = (gcnew System::Windows::Forms::Label());
    this->ValVars = (gcnew System::Windows::Forms::TextBox());
    this->label26 = (gcnew System::Windows::Forms::Label());
    this->DerVar = (gcnew System::Windows::Forms::TextBox());
    this->label4 = (gcnew System::Windows::Forms::Label());
    this->label6 = (gcnew System::Windows::Forms::Label());
    this->DerTimes = (gcnew System::Windows::Forms::TextBox());
    this->FromFile = (gcnew System::Windows::Forms::Button());
    this->SumPush = (gcnew System::Windows::Forms::Button());
    this->MultPush = (gcnew System::Windows::Forms::Button());
    this->DerPush = (gcnew System::Windows::Forms::Button());
    this->SuspendLayout();
    //
    // PushButton
    //
    this->PushButton->BackColor = System::Drawing::Color::GhostWhite;
    this->PushButton->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->PushButton->Location = System::Drawing::Point(300, 692);
    this->PushButton->Name = L"PushButton";
    this->PushButton->Size = System::Drawing::Size(73, 25);
    this->PushButton->TabIndex = 1;
    this->PushButton->Text = L"push";
    this->PushButton->UseVisualStyleBackColor = false;
    this->PushButton->Click +=
        gcnew System::EventHandler(this, &PolyUi::button1_Click);
    //
    // NewStr
    //
    this->NewStr->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->NewStr->Location = System::Drawing::Point(13, 694);
    this->NewStr->Name = L"NewStr";
    this->NewStr->Size = System::Drawing::Size(281, 23);
    this->NewStr->TabIndex = 2;
    //
    // Bank
    //
    this->Bank->Font = (gcnew System::Drawing::Font(
        L"Consolas", 12, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->Bank->FormattingEnabled = true;
    this->Bank->ItemHeight = 19;
    this->Bank->Location = System::Drawing::Point(13, 51);
    this->Bank->Name = L"Bank";
    this->Bank->Size = System::Drawing::Size(461, 612);
    this->Bank->TabIndex = 3;
    //
    // HintDoSum
    //
    this->HintDoSum->AutoSize = true;
    this->HintDoSum->Font = (gcnew System::Drawing::Font(
        L"Consolas", 30, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->HintDoSum->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->HintDoSum->Location = System::Drawing::Point(482, 12);
    this->HintDoSum->Name = L"HintDoSum";
    this->HintDoSum->Size = System::Drawing::Size(108, 47);
    this->HintDoSum->TabIndex = 4;
    this->HintDoSum->Text = L"Sum:";
    //
    // HintNewStr
    //
    this->HintNewStr->AutoSize = true;
    this->HintNewStr->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->HintNewStr->ForeColor =
        System::Drawing::SystemColors::ButtonHighlight;
    this->HintNewStr->Location = System::Drawing::Point(12, 674);
    this->HintNewStr->Name = L"HintNewStr";
    this->HintNewStr->Size = System::Drawing::Size(200, 17);
    this->HintNewStr->TabIndex = 5;
    this->HintNewStr->Text = L"Enter your polinom here:";
    //
    // HintBank
    //
    this->HintBank->AutoSize = true;
    this->HintBank->Font = (gcnew System::Drawing::Font(
        L"Consolas", 20, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->HintBank->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->HintBank->Location = System::Drawing::Point(16, 12);
    this->HintBank->Name = L"HintBank";
    this->HintBank->Size = System::Drawing::Size(300, 32);
    this->HintBank->TabIndex = 6;
    this->HintBank->Text = L"Your polinoms here:";
    //
    // label1
    //
    this->label1->AutoSize = true;
    this->label1->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label1->Location = System::Drawing::Point(485, 65);
    this->label1->Name = L"label1";
    this->label1->Size = System::Drawing::Size(40, 17);
    this->label1->TabIndex = 7;
    this->label1->Text = L"By N";
    //
    // SumNA
    //
    this->SumNA->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->SumNA->Location = System::Drawing::Point(488, 85);
    this->SumNA->Name = L"SumNA";
    this->SumNA->Size = System::Drawing::Size(36, 23);
    this->SumNA->TabIndex = 8;
    this->SumNA->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::SumNA_TextChanged);
    //
    // SumStrA
    //
    this->SumStrA->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->SumStrA->Location = System::Drawing::Point(530, 85);
    this->SumStrA->Name = L"SumStrA";
    this->SumStrA->Size = System::Drawing::Size(268, 23);
    this->SumStrA->TabIndex = 9;
    this->SumStrA->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::SumStrA_TextChanged);
    //
    // label2
    //
    this->label2->AutoSize = true;
    this->label2->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label2->Location = System::Drawing::Point(804, 88);
    this->label2->Name = L"label2";
    this->label2->Size = System::Drawing::Size(16, 17);
    this->label2->TabIndex = 10;
    this->label2->Text = L"+";
    //
    // SumNB
    //
    this->SumNB->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->SumNB->Location = System::Drawing::Point(826, 85);
    this->SumNB->Name = L"SumNB";
    this->SumNB->Size = System::Drawing::Size(36, 23);
    this->SumNB->TabIndex = 11;
    this->SumNB->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::SumNB_TextChanged);
    //
    // SumStrB
    //
    this->SumStrB->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->SumStrB->Location = System::Drawing::Point(868, 85);
    this->SumStrB->Name = L"SumStrB";
    this->SumStrB->Size = System::Drawing::Size(268, 23);
    this->SumStrB->TabIndex = 12;
    this->SumStrB->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::SumStrB_TextChanged);
    //
    // label3
    //
    this->label3->AutoSize = true;
    this->label3->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label3->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label3->Location = System::Drawing::Point(823, 65);
    this->label3->Name = L"label3";
    this->label3->Size = System::Drawing::Size(40, 17);
    this->label3->TabIndex = 13;
    this->label3->Text = L"By N";
    //
    // hint
    //
    this->hint->AutoSize = true;
    this->hint->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->hint->ForeColor = System::Drawing::SystemColors::ControlLightLight;
    this->hint->Location = System::Drawing::Point(531, 65);
    this->hint->Name = L"hint";
    this->hint->Size = System::Drawing::Size(56, 17);
    this->hint->TabIndex = 14;
    this->hint->Text = L"By str";
    //
    // label5
    //
    this->label5->AutoSize = true;
    this->label5->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label5->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label5->Location = System::Drawing::Point(869, 65);
    this->label5->Name = L"label5";
    this->label5->Size = System::Drawing::Size(56, 17);
    this->label5->TabIndex = 15;
    this->label5->Text = L"By str";
    //
    // SumRes
    //
    this->SumRes->AutoSize = true;
    this->SumRes->Font = (gcnew System::Drawing::Font(
        L"Consolas", 15, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->SumRes->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->SumRes->Location = System::Drawing::Point(485, 121);
    this->SumRes->Name = L"SumRes";
    this->SumRes->Size = System::Drawing::Size(164, 23);
    this->SumRes->TabIndex = 16;
    this->SumRes->Text = L"Result: daafsd";
    //
    // MultRes
    //
    this->MultRes->AutoSize = true;
    this->MultRes->Font = (gcnew System::Drawing::Font(
        L"Consolas", 15, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->MultRes->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->MultRes->Location = System::Drawing::Point(485, 260);
    this->MultRes->Name = L"MultRes";
    this->MultRes->Size = System::Drawing::Size(164, 23);
    this->MultRes->TabIndex = 28;
    this->MultRes->Text = L"Result: daafsd";
    //
    // label8
    //
    this->label8->AutoSize = true;
    this->label8->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label8->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label8->Location = System::Drawing::Point(869, 204);
    this->label8->Name = L"label8";
    this->label8->Size = System::Drawing::Size(56, 17);
    this->label8->TabIndex = 27;
    this->label8->Text = L"By str";
    //
    // label9
    //
    this->label9->AutoSize = true;
    this->label9->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label9->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label9->Location = System::Drawing::Point(531, 204);
    this->label9->Name = L"label9";
    this->label9->Size = System::Drawing::Size(56, 17);
    this->label9->TabIndex = 26;
    this->label9->Text = L"By str";
    //
    // label10
    //
    this->label10->AutoSize = true;
    this->label10->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label10->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label10->Location = System::Drawing::Point(823, 204);
    this->label10->Name = L"label10";
    this->label10->Size = System::Drawing::Size(40, 17);
    this->label10->TabIndex = 25;
    this->label10->Text = L"By N";
    //
    // MultStrB
    //
    this->MultStrB->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->MultStrB->Location = System::Drawing::Point(868, 224);
    this->MultStrB->Name = L"MultStrB";
    this->MultStrB->Size = System::Drawing::Size(268, 23);
    this->MultStrB->TabIndex = 24;
    this->MultStrB->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::MultStrB_TextChanged);
    //
    // MultNB
    //
    this->MultNB->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->MultNB->Location = System::Drawing::Point(826, 224);
    this->MultNB->Name = L"MultNB";
    this->MultNB->Size = System::Drawing::Size(36, 23);
    this->MultNB->TabIndex = 23;
    this->MultNB->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::MultNB_TextChanged);
    //
    // label11
    //
    this->label11->AutoSize = true;
    this->label11->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label11->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label11->Location = System::Drawing::Point(804, 227);
    this->label11->Name = L"label11";
    this->label11->Size = System::Drawing::Size(16, 17);
    this->label11->TabIndex = 22;
    this->label11->Text = L"*";
    //
    // MultStrA
    //
    this->MultStrA->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->MultStrA->Location = System::Drawing::Point(530, 224);
    this->MultStrA->Name = L"MultStrA";
    this->MultStrA->Size = System::Drawing::Size(268, 23);
    this->MultStrA->TabIndex = 21;
    this->MultStrA->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::MultStrA_TextChanged);
    //
    // MultNA
    //
    this->MultNA->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->MultNA->Location = System::Drawing::Point(488, 224);
    this->MultNA->Name = L"MultNA";
    this->MultNA->Size = System::Drawing::Size(36, 23);
    this->MultNA->TabIndex = 20;
    this->MultNA->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::MultNA_TextChanged);
    //
    // label12
    //
    this->label12->AutoSize = true;
    this->label12->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label12->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label12->Location = System::Drawing::Point(485, 204);
    this->label12->Name = L"label12";
    this->label12->Size = System::Drawing::Size(40, 17);
    this->label12->TabIndex = 19;
    this->label12->Text = L"By N";
    //
    // label13
    //
    this->label13->AutoSize = true;
    this->label13->Font = (gcnew System::Drawing::Font(
        L"Consolas", 30, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label13->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label13->Location = System::Drawing::Point(482, 151);
    this->label13->Name = L"label13";
    this->label13->Size = System::Drawing::Size(196, 47);
    this->label13->TabIndex = 18;
    this->label13->Text = L"Multipy:";
    //
    // DerRes
    //
    this->DerRes->AutoSize = true;
    this->DerRes->Font = (gcnew System::Drawing::Font(
        L"Consolas", 15, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->DerRes->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->DerRes->Location = System::Drawing::Point(485, 410);
    this->DerRes->Name = L"DerRes";
    this->DerRes->Size = System::Drawing::Size(164, 23);
    this->DerRes->TabIndex = 35;
    this->DerRes->Text = L"Result: daafsd";
    //
    // label15
    //
    this->label15->AutoSize = true;
    this->label15->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label15->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label15->Location = System::Drawing::Point(531, 354);
    this->label15->Name = L"label15";
    this->label15->Size = System::Drawing::Size(56, 17);
    this->label15->TabIndex = 34;
    this->label15->Text = L"By str";
    //
    // DerStr
    //
    this->DerStr->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->DerStr->Location = System::Drawing::Point(530, 374);
    this->DerStr->Name = L"DerStr";
    this->DerStr->Size = System::Drawing::Size(268, 23);
    this->DerStr->TabIndex = 33;
    this->DerStr->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::DerStr_TextChanged);
    //
    // DerN
    //
    this->DerN->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->DerN->Location = System::Drawing::Point(488, 374);
    this->DerN->Name = L"DerN";
    this->DerN->Size = System::Drawing::Size(36, 23);
    this->DerN->TabIndex = 32;
    this->DerN->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::DerN_TextChanged);
    //
    // label16
    //
    this->label16->AutoSize = true;
    this->label16->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label16->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label16->Location = System::Drawing::Point(485, 354);
    this->label16->Name = L"label16";
    this->label16->Size = System::Drawing::Size(40, 17);
    this->label16->TabIndex = 31;
    this->label16->Text = L"By N";
    //
    // label17
    //
    this->label17->AutoSize = true;
    this->label17->Font = (gcnew System::Drawing::Font(
        L"Consolas", 30, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label17->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label17->Location = System::Drawing::Point(482, 301);
    this->label17->Name = L"label17";
    this->label17->Size = System::Drawing::Size(262, 47);
    this->label17->TabIndex = 30;
    this->label17->Text = L"Derivative:";
    //
    // RootRes
    //
    this->RootRes->AutoSize = true;
    this->RootRes->Font = (gcnew System::Drawing::Font(
        L"Consolas", 15, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->RootRes->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->RootRes->Location = System::Drawing::Point(483, 694);
    this->RootRes->Name = L"RootRes";
    this->RootRes->Size = System::Drawing::Size(164, 23);
    this->RootRes->TabIndex = 41;
    this->RootRes->Text = L"Result: daafsd";
    //
    // label19
    //
    this->label19->AutoSize = true;
    this->label19->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label19->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label19->Location = System::Drawing::Point(529, 638);
    this->label19->Name = L"label19";
    this->label19->Size = System::Drawing::Size(56, 17);
    this->label19->TabIndex = 40;
    this->label19->Text = L"By str";
    //
    // RootStr
    //
    this->RootStr->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->RootStr->Location = System::Drawing::Point(528, 658);
    this->RootStr->Name = L"RootStr";
    this->RootStr->Size = System::Drawing::Size(268, 23);
    this->RootStr->TabIndex = 39;
    this->RootStr->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::RootStr_TextChanged);
    //
    // RootN
    //
    this->RootN->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->RootN->Location = System::Drawing::Point(486, 658);
    this->RootN->Name = L"RootN";
    this->RootN->Size = System::Drawing::Size(36, 23);
    this->RootN->TabIndex = 38;
    this->RootN->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::RootN_TextChanged);
    //
    // label20
    //
    this->label20->AutoSize = true;
    this->label20->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label20->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label20->Location = System::Drawing::Point(483, 638);
    this->label20->Name = L"label20";
    this->label20->Size = System::Drawing::Size(40, 17);
    this->label20->TabIndex = 37;
    this->label20->Text = L"By N";
    //
    // label21
    //
    this->label21->AutoSize = true;
    this->label21->Font = (gcnew System::Drawing::Font(
        L"Consolas", 30, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label21->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label21->Location = System::Drawing::Point(480, 585);
    this->label21->Name = L"label21";
    this->label21->Size = System::Drawing::Size(240, 47);
    this->label21->TabIndex = 36;
    this->label21->Text = L"Int roots:";
    //
    // ValRes
    //
    this->ValRes->AutoSize = true;
    this->ValRes->Font = (gcnew System::Drawing::Font(
        L"Consolas", 15, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->ValRes->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->ValRes->Location = System::Drawing::Point(485, 552);
    this->ValRes->Name = L"ValRes";
    this->ValRes->Size = System::Drawing::Size(164, 23);
    this->ValRes->TabIndex = 47;
    this->ValRes->Text = L"Result: daafsd";
    //
    // label23
    //
    this->label23->AutoSize = true;
    this->label23->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label23->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label23->Location = System::Drawing::Point(531, 496);
    this->label23->Name = L"label23";
    this->label23->Size = System::Drawing::Size(56, 17);
    this->label23->TabIndex = 46;
    this->label23->Text = L"By str";
    //
    // textBox13
    //
    this->textBox13->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->textBox13->Location = System::Drawing::Point(530, 516);
    this->textBox13->Name = L"textBox13";
    this->textBox13->Size = System::Drawing::Size(268, 23);
    this->textBox13->TabIndex = 45;
    //
    // textBox14
    //
    this->textBox14->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->textBox14->Location = System::Drawing::Point(488, 516);
    this->textBox14->Name = L"textBox14";
    this->textBox14->Size = System::Drawing::Size(36, 23);
    this->textBox14->TabIndex = 44;
    //
    // label24
    //
    this->label24->AutoSize = true;
    this->label24->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label24->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label24->Location = System::Drawing::Point(485, 496);
    this->label24->Name = L"label24";
    this->label24->Size = System::Drawing::Size(40, 17);
    this->label24->TabIndex = 43;
    this->label24->Text = L"By N";
    //
    // label25
    //
    this->label25->AutoSize = true;
    this->label25->Font = (gcnew System::Drawing::Font(
        L"Consolas", 30, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label25->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label25->Location = System::Drawing::Point(482, 443);
    this->label25->Name = L"label25";
    this->label25->Size = System::Drawing::Size(306, 47);
    this->label25->TabIndex = 42;
    this->label25->Text = L"Val at point:";
    //
    // ValVars
    //
    this->ValVars->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->ValVars->Location = System::Drawing::Point(824, 516);
    this->ValVars->Name = L"ValVars";
    this->ValVars->Size = System::Drawing::Size(268, 23);
    this->ValVars->TabIndex = 48;
    this->ValVars->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::ValVars_TextChanged);
    //
    // label26
    //
    this->label26->AutoSize = true;
    this->label26->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label26->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label26->Location = System::Drawing::Point(823, 496);
    this->label26->Name = L"label26";
    this->label26->Size = System::Drawing::Size(240, 17);
    this->label26->TabIndex = 49;
    this->label26->Text = L"Var values: like(x = 2 y = 4)";
    //
    // DerVar
    //
    this->DerVar->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->DerVar->Location = System::Drawing::Point(804, 374);
    this->DerVar->Name = L"DerVar";
    this->DerVar->Size = System::Drawing::Size(36, 23);
    this->DerVar->TabIndex = 50;
    this->DerVar->Text = L"x";
    this->DerVar->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::DerVar_TextChanged);
    //
    // label4
    //
    this->label4->AutoSize = true;
    this->label4->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label4->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label4->Location = System::Drawing::Point(804, 354);
    this->label4->Name = L"label4";
    this->label4->Size = System::Drawing::Size(40, 17);
    this->label4->TabIndex = 51;
    this->label4->Text = L"Var:";
    //
    // label6
    //
    this->label6->AutoSize = true;
    this->label6->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->label6->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
    this->label6->Location = System::Drawing::Point(850, 354);
    this->label6->Name = L"label6";
    this->label6->Size = System::Drawing::Size(24, 17);
    this->label6->TabIndex = 53;
    this->label6->Text = L"N:";
    //
    // DerTimes
    //
    this->DerTimes->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->DerTimes->Location = System::Drawing::Point(846, 374);
    this->DerTimes->Name = L"DerTimes";
    this->DerTimes->Size = System::Drawing::Size(36, 23);
    this->DerTimes->TabIndex = 54;
    this->DerTimes->Text = L"1";
    this->DerTimes->TextChanged +=
        gcnew System::EventHandler(this, &PolyUi::DerTimes_TextChanged);
    //
    // FromFile
    //
    this->FromFile->BackColor = System::Drawing::Color::GhostWhite;
    this->FromFile->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->FromFile->Location = System::Drawing::Point(379, 692);
    this->FromFile->Name = L"FromFile";
    this->FromFile->Size = System::Drawing::Size(95, 25);
    this->FromFile->TabIndex = 55;
    this->FromFile->Text = L"from file";
    this->FromFile->UseVisualStyleBackColor = false;
    this->FromFile->Click +=
        gcnew System::EventHandler(this, &PolyUi::FromFile_Click);
    //
    // SumPush
    //
    this->SumPush->BackColor = System::Drawing::Color::GhostWhite;
    this->SumPush->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->SumPush->Location = System::Drawing::Point(1041, 119);
    this->SumPush->Name = L"SumPush";
    this->SumPush->Size = System::Drawing::Size(95, 25);
    this->SumPush->TabIndex = 56;
    this->SumPush->Text = L"push";
    this->SumPush->UseVisualStyleBackColor = false;
    this->SumPush->Click +=
        gcnew System::EventHandler(this, &PolyUi::SumPush_Click);
    //
    // MultPush
    //
    this->MultPush->BackColor = System::Drawing::Color::GhostWhite;
    this->MultPush->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->MultPush->Location = System::Drawing::Point(1041, 261);
    this->MultPush->Name = L"MultPush";
    this->MultPush->Size = System::Drawing::Size(95, 25);
    this->MultPush->TabIndex = 57;
    this->MultPush->Text = L"push";
    this->MultPush->UseVisualStyleBackColor = false;
    this->MultPush->Click +=
        gcnew System::EventHandler(this, &PolyUi::MultPush_Click);
    //
    // DerPush
    //
    this->DerPush->BackColor = System::Drawing::Color::GhostWhite;
    this->DerPush->Font = (gcnew System::Drawing::Font(
        L"Consolas", 10, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->DerPush->Location = System::Drawing::Point(1041, 408);
    this->DerPush->Name = L"DerPush";
    this->DerPush->Size = System::Drawing::Size(95, 25);
    this->DerPush->TabIndex = 58;
    this->DerPush->Text = L"push";
    this->DerPush->UseVisualStyleBackColor = false;
    this->DerPush->Click +=
        gcnew System::EventHandler(this, &PolyUi::DerPush_Click);
    //
    // PolyUi
    //
    this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->BackColor = System::Drawing::Color::BlueViolet;
    this->ClientSize = System::Drawing::Size(1348, 727);
    this->Controls->Add(this->DerPush);
    this->Controls->Add(this->MultPush);
    this->Controls->Add(this->SumPush);
    this->Controls->Add(this->FromFile);
    this->Controls->Add(this->label6);
    this->Controls->Add(this->label4);
    this->Controls->Add(this->DerVar);
    this->Controls->Add(this->label26);
    this->Controls->Add(this->ValVars);
    this->Controls->Add(this->ValRes);
    this->Controls->Add(this->label23);
    this->Controls->Add(this->textBox13);
    this->Controls->Add(this->textBox14);
    this->Controls->Add(this->label24);
    this->Controls->Add(this->label25);
    this->Controls->Add(this->RootRes);
    this->Controls->Add(this->label19);
    this->Controls->Add(this->RootStr);
    this->Controls->Add(this->RootN);
    this->Controls->Add(this->label20);
    this->Controls->Add(this->label21);
    this->Controls->Add(this->DerRes);
    this->Controls->Add(this->label15);
    this->Controls->Add(this->DerStr);
    this->Controls->Add(this->DerN);
    this->Controls->Add(this->label16);
    this->Controls->Add(this->label17);
    this->Controls->Add(this->MultRes);
    this->Controls->Add(this->label8);
    this->Controls->Add(this->label9);
    this->Controls->Add(this->label10);
    this->Controls->Add(this->MultStrB);
    this->Controls->Add(this->MultNB);
    this->Controls->Add(this->label11);
    this->Controls->Add(this->MultStrA);
    this->Controls->Add(this->MultNA);
    this->Controls->Add(this->label12);
    this->Controls->Add(this->label13);
    this->Controls->Add(this->SumRes);
    this->Controls->Add(this->label5);
    this->Controls->Add(this->hint);
    this->Controls->Add(this->label3);
    this->Controls->Add(this->SumStrB);
    this->Controls->Add(this->SumNB);
    this->Controls->Add(this->label2);
    this->Controls->Add(this->SumStrA);
    this->Controls->Add(this->SumNA);
    this->Controls->Add(this->label1);
    this->Controls->Add(this->HintBank);
    this->Controls->Add(this->HintNewStr);
    this->Controls->Add(this->HintDoSum);
    this->Controls->Add(this->Bank);
    this->Controls->Add(this->NewStr);
    this->Controls->Add(this->PushButton);
    this->Controls->Add(this->DerTimes);
    this->Name = L"PolyUi";
    this->Text = L"PolyUi";
    this->ResumeLayout(false);
    this->PerformLayout();
  }
#pragma endregion
 private:
  string updateSum() {
    std::string stra = marshal_as<std::string>(SumStrA->Text->ToString());
    std::string strb = marshal_as<std::string>(SumStrB->Text->ToString());
    std::string strna = marshal_as<std::string>(SumNA->Text->ToString());
    std::string strnb = marshal_as<std::string>(SumNB->Text->ToString());
    try {
      stra = pols->at(stoi(strna) - 1)->data.toStr();
    } catch (...) {
    }
    try {
      strb = pols->at(stoi(strnb) - 1)->data.toStr();
    } catch (...) {
    }
    Polinom a(stra), b(strb);
    string st = (a + b).toStr();
    SumRes->Text = gcnew String(("Result: " + (a + b).toStr()).c_str());
    return st;
  }
  string updateDer() {
    std::string stra = marshal_as<std::string>(DerStr->Text->ToString());
    std::string strna = marshal_as<std::string>(DerN->Text->ToString());
    std::string strb = marshal_as<std::string>(DerVar->Text->ToString());
    try {
      stra = pols->at(stoi(strna) - 1)->data.toStr();
    } catch (...) {
    }
    try {
    Polinom a(stra);
      string st = (a.derivative(strb[0], stoi(marshal_as<std::string>(
                                             DerTimes->Text->ToString()))))
                      .toStr();
    DerRes->Text = gcnew String(
        ("Result: " + (a.derivative(strb[0], stoi(marshal_as<std::string>(
                                                 DerTimes->Text->ToString()))))
                          .toStr())
            .c_str());
      return st;
    } catch (...) {
    }
    
  }
  string updateMult() {
    std::string stra = marshal_as<std::string>(MultStrA->Text->ToString());
    std::string strb = marshal_as<std::string>(MultStrB->Text->ToString());
    std::string strna = marshal_as<std::string>(MultNA->Text->ToString());
    std::string strnb = marshal_as<std::string>(MultNB->Text->ToString());
    try {
      stra = pols->at(stoi(strna) - 1)->data.toStr();
    } catch (...) {
    }
    try {
      strb = pols->at(stoi(strnb) - 1)->data.toStr();
    } catch (...) {
    }
    Polinom a(stra), b(strb);
    string st = (a * b).toStr();
    MultRes->Text = gcnew String(("Result: " + (a * b).toStr()).c_str());
    return st;
  }
  void uptateRoots() {
    std::string stra = marshal_as<std::string>(RootStr->Text->ToString());
    std::string strna = marshal_as<std::string>(RootN->Text->ToString());
    try {
      stra = pols->at(stoi(strna) - 1)->data.toStr();
    } catch (...) {
    }
    try {
      Polinom a(stra);

      RootRes->Text = gcnew String(
          ("Result: " + a.intRoots()).c_str());
    } catch (...) {
    }
  }
  void updateVal() {

  }
  void pushToBank(string str) {
    auto tmp_pol = Polinom(str);
    if (!tmp_pol.isNull()) {
      pols->pushBack(tmp_pol);
      Polinom sec = tmp_pol + Polinom();
      Bank->Items->Add(gcnew String(
          (std::to_string(pols->size) + ": " + sec.toStr()).c_str()));
      NewStr->Text = "";
    }
    //updateMult();
  }
  System::Void button1_Click(System::Object ^ sender, System::EventArgs ^ e) {
    std::string str = marshal_as<std::string>(NewStr->Text->ToString());
    pushToBank(str);
  }

 private:
  System::Void SumCalc_Click(System::Object ^ sender, System::EventArgs ^ e) {
    updateSum();
  }
  System::Void button2_Click(System::Object ^ sender, System::EventArgs ^ e) {
    updateMult();
  }

 private:
  System::Void MultStrA_TextChanged(System::Object ^ sender,
                                    System::EventArgs ^ e) {
    updateMult();
  }

 private:
  System::Void MultNA_TextChanged(System::Object ^ sender,
                                  System::EventArgs ^ e) {
    updateMult();
  }

 private:
  System::Void MultStrB_TextChanged(System::Object ^ sender,
                                    System::EventArgs ^ e) {
    updateMult();
  }

 private:
  System::Void MultNB_TextChanged(System::Object ^ sender,
                                  System::EventArgs ^ e) {
    updateMult();
  }

 private:
  System::Void SumNA_TextChanged(System::Object ^ sender,
                                 System::EventArgs ^ e) {
    updateSum();
  }

 private:
  System::Void SumStrA_TextChanged(System::Object ^ sender,
                                   System::EventArgs ^ e) {
    updateSum();
  }

 private:
  System::Void SumNB_TextChanged(System::Object ^ sender,
                                 System::EventArgs ^ e) {
    updateSum();
  }

 private:
  System::Void SumStrB_TextChanged(System::Object ^ sender,
                                   System::EventArgs ^ e) {
    updateSum();
  }

 private:
  System::Void DerN_TextChanged(System::Object ^ sender,
                                System::EventArgs ^ e) {
    updateDer();
  }

 private:
  System::Void DerStr_TextChanged(System::Object ^ sender,
                                  System::EventArgs ^ e) {
    updateDer();
  }

 private:
  System::Void DerVar_TextChanged(System::Object ^ sender,
                                  System::EventArgs ^ e) {
    updateDer();
  }

 private:
  System::Void numericUpDown1_ValueChanged(System::Object ^ sender,
                                           System::EventArgs ^ e) {
    updateDer();
  }

 private:
  System::Void DerTimes_TextChanged(System::Object ^ sender,
                                    System::EventArgs ^ e) {
    updateDer();
  }

 private:
  System::Void RootStr_TextChanged(System::Object ^ sender,
                                   System::EventArgs ^ e) {
    uptateRoots();
  }

 private:
  System::Void RootN_TextChanged(System::Object ^ sender,
                                 System::EventArgs ^ e) {
    uptateRoots();
  }

 private:
  System::Void FromFile_Click(System::Object ^ sender, System::EventArgs ^ e) {
    Stream ^ myStream;
    OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog;

    openFileDialog1->InitialDirectory = "c:\\";
    openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
    openFileDialog1->FilterIndex = 2;
    openFileDialog1->RestoreDirectory = true;
    try {
      if (openFileDialog1->ShowDialog() ==
          System::Windows::Forms::DialogResult::OK) {
        if ((myStream = openFileDialog1->OpenFile()) != nullptr) {
          try {
            //pols->clear();
            auto str = marshal_as<std::string>(StreamReader(myStream).ReadToEnd());
            for (auto i : split_string(str, "\n")) {
              try {
                std::cout << i;
                pushToBank(i);
                //pols->pushBack(Polinom(i));
              } catch (...) {
              }
            }
            myStream->Close();
          } catch (...) {
          }
        }
      }
    } catch (...) {
    }
  }

 private:
  System::Void ValVars_TextChanged(System::Object ^ sender,
                                   System::EventArgs ^ e) {}

 private:
  System::Void SumPush_Click(System::Object ^ sender, System::EventArgs ^ e) {
    pushToBank(updateSum());
  }

 private:
  System::Void DerPush_Click(System::Object ^ sender, System::EventArgs ^ e) {
    pushToBank(updateDer());
  }

 private:
  System::Void MultPush_Click(System::Object ^ sender, System::EventArgs ^ e) {
    pushToBank(updateMult());
  }
};
}  // namespace PolynomialsFrontend
