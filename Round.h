#pragma once

namespace handicap {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Round
	/// </summary>
	public ref class Round : public System::Windows::Forms::Form
	{
	public:
		Round(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			m_strLastDate = "";
			m_strCourseName = "";
			m_strCoursePar = "";
			m_strRound = "";
			m_strGolfer = "";

			m_strErr = "";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Round()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  labelDate;
	private: System::Windows::Forms::TextBox^  textBoxDate;
	protected: 

	private: System::Windows::Forms::Label^  labelCourse;
	private: System::Windows::Forms::TextBox^  textBoxCourseName;
	private: System::Windows::Forms::Label^  labelPar;
	private: System::Windows::Forms::TextBox^  textBoxCoursePar;
	private: System::Windows::Forms::Label^  labelRound;
	private: System::Windows::Forms::TextBox^  textBoxRound;
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::Label^  labelGolfer;
	private: System::Windows::Forms::TextBox^  textBoxGolfer;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labelDate = (gcnew System::Windows::Forms::Label());
			this->textBoxDate = (gcnew System::Windows::Forms::TextBox());
			this->labelCourse = (gcnew System::Windows::Forms::Label());
			this->textBoxCourseName = (gcnew System::Windows::Forms::TextBox());
			this->labelPar = (gcnew System::Windows::Forms::Label());
			this->textBoxCoursePar = (gcnew System::Windows::Forms::TextBox());
			this->labelRound = (gcnew System::Windows::Forms::Label());
			this->textBoxRound = (gcnew System::Windows::Forms::TextBox());
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->labelGolfer = (gcnew System::Windows::Forms::Label());
			this->textBoxGolfer = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// labelDate
			// 
			this->labelDate->AutoSize = true;
			this->labelDate->Location = System::Drawing::Point(29, 23);
			this->labelDate->Name = L"labelDate";
			this->labelDate->Size = System::Drawing::Size(119, 18);
			this->labelDate->TabIndex = 0;
			this->labelDate->Text = L"Date (YYMMDD)";
			// 
			// textBoxDate
			// 
			this->textBoxDate->Location = System::Drawing::Point(32, 44);
			this->textBoxDate->Name = L"textBoxDate";
			this->textBoxDate->Size = System::Drawing::Size(148, 24);
			this->textBoxDate->TabIndex = 1;
			this->textBoxDate->Text = L"220705";
			// 
			// labelCourse
			// 
			this->labelCourse->AutoSize = true;
			this->labelCourse->Location = System::Drawing::Point(29, 97);
			this->labelCourse->Name = L"labelCourse";
			this->labelCourse->Size = System::Drawing::Size(57, 18);
			this->labelCourse->TabIndex = 2;
			this->labelCourse->Text = L"Course";
			// 
			// textBoxCourseName
			// 
			this->textBoxCourseName->Location = System::Drawing::Point(92, 94);
			this->textBoxCourseName->Name = L"textBoxCourseName";
			this->textBoxCourseName->ReadOnly = true;
			this->textBoxCourseName->Size = System::Drawing::Size(318, 24);
			this->textBoxCourseName->TabIndex = 3;
			// 
			// labelPar
			// 
			this->labelPar->AutoSize = true;
			this->labelPar->Location = System::Drawing::Point(29, 138);
			this->labelPar->Name = L"labelPar";
			this->labelPar->Size = System::Drawing::Size(31, 18);
			this->labelPar->TabIndex = 4;
			this->labelPar->Text = L"Par";
			// 
			// textBoxCoursePar
			// 
			this->textBoxCoursePar->Location = System::Drawing::Point(32, 159);
			this->textBoxCoursePar->Name = L"textBoxCoursePar";
			this->textBoxCoursePar->ReadOnly = true;
			this->textBoxCoursePar->Size = System::Drawing::Size(378, 24);
			this->textBoxCoursePar->TabIndex = 5;
			// 
			// labelRound
			// 
			this->labelRound->AutoSize = true;
			this->labelRound->Location = System::Drawing::Point(29, 211);
			this->labelRound->Name = L"labelRound";
			this->labelRound->Size = System::Drawing::Size(52, 18);
			this->labelRound->TabIndex = 6;
			this->labelRound->Text = L"Round";
			// 
			// textBoxRound
			// 
			this->textBoxRound->Location = System::Drawing::Point(32, 234);
			this->textBoxRound->Name = L"textBoxRound";
			this->textBoxRound->Size = System::Drawing::Size(378, 24);
			this->textBoxRound->TabIndex = 7;
			// 
			// buttonOk
			// 
			this->buttonOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonOk->Location = System::Drawing::Point(360, 44);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(75, 34);
			this->buttonOk->TabIndex = 8;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &Round::buttonOk_Click);
			// 
			// labelGolfer
			// 
			this->labelGolfer->AutoSize = true;
			this->labelGolfer->Location = System::Drawing::Point(29, 280);
			this->labelGolfer->Name = L"labelGolfer";
			this->labelGolfer->Size = System::Drawing::Size(49, 18);
			this->labelGolfer->TabIndex = 9;
			this->labelGolfer->Text = L"Golfer";
			// 
			// textBoxGolfer
			// 
			this->textBoxGolfer->Location = System::Drawing::Point(32, 301);
			this->textBoxGolfer->Name = L"textBoxGolfer";
			this->textBoxGolfer->ReadOnly = true;
			this->textBoxGolfer->Size = System::Drawing::Size(378, 24);
			this->textBoxGolfer->TabIndex = 10;
			// 
			// Round
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(486, 370);
			this->Controls->Add(this->textBoxGolfer);
			this->Controls->Add(this->labelGolfer);
			this->Controls->Add(this->buttonOk);
			this->Controls->Add(this->textBoxRound);
			this->Controls->Add(this->labelRound);
			this->Controls->Add(this->textBoxCoursePar);
			this->Controls->Add(this->labelPar);
			this->Controls->Add(this->textBoxCourseName);
			this->Controls->Add(this->labelCourse);
			this->Controls->Add(this->textBoxDate);
			this->Controls->Add(this->labelDate);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Round";
			this->Text = L"Add Round ..";
			this->Load += gcnew System::EventHandler(this, &Round::Round_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Round_Load(System::Object^  sender, System::EventArgs^  e);

	public:
		String^ m_strLastDate;

		String^ m_strCourseName;
		String^ m_strCoursePar;
		
		String^ m_strRound;

		String^ m_strGolfer;

		String^ m_strErr;
};
}
