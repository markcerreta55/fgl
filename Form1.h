#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace System::IO;

namespace handicap {

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

			m_form1 = this;

			setOpen( false );
			
			setOpen( true );

			m_strLastDate = "";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			m_form1 = nullptr;

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnConvert;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;


	private: System::Windows::Forms::Label^  labelCourses;
	private: System::Windows::Forms::ListBox^  listBoxCourses;
	private: System::Windows::Forms::Label^  labelGolfers;
	private: System::Windows::Forms::ListBox^  listBoxGolfers;
	private: System::Windows::Forms::Label^  labelRounds;
	private: System::Windows::Forms::ListBox^  listBoxRounds;
	private: System::Windows::Forms::Button^  buttonAddRound;
	private: System::Windows::Forms::Label^  labelGolferRounds;
	private: System::Windows::Forms::ListBox^  listBoxGolferRounds;
	protected: 

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
			this->btnConvert = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->labelCourses = (gcnew System::Windows::Forms::Label());
			this->listBoxCourses = (gcnew System::Windows::Forms::ListBox());
			this->labelGolfers = (gcnew System::Windows::Forms::Label());
			this->listBoxGolfers = (gcnew System::Windows::Forms::ListBox());
			this->labelRounds = (gcnew System::Windows::Forms::Label());
			this->listBoxRounds = (gcnew System::Windows::Forms::ListBox());
			this->buttonAddRound = (gcnew System::Windows::Forms::Button());
			this->labelGolferRounds = (gcnew System::Windows::Forms::Label());
			this->listBoxGolferRounds = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// btnConvert
			// 
			this->btnConvert->Location = System::Drawing::Point(23, 17);
			this->btnConvert->Margin = System::Windows::Forms::Padding(4);
			this->btnConvert->Name = L"btnConvert";
			this->btnConvert->Size = System::Drawing::Size(250, 32);
			this->btnConvert->TabIndex = 0;
			this->btnConvert->Text = L"Generate handicaps ..";
			this->btnConvert->UseVisualStyleBackColor = true;
			this->btnConvert->Click += gcnew System::EventHandler(this, &Form1::btnConvert_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->AddExtension = false;
			this->openFileDialog1->DefaultExt = L"smk";
			this->openFileDialog1->FileName = L"*.smk";
			this->openFileDialog1->Filter = L"Smk files|*.smk|All files|*.*";
			this->openFileDialog1->Title = L"Open file ..";
			// 
			// labelCourses
			// 
			this->labelCourses->AutoSize = true;
			this->labelCourses->Location = System::Drawing::Point(20, 84);
			this->labelCourses->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelCourses->Name = L"labelCourses";
			this->labelCourses->Size = System::Drawing::Size(247, 18);
			this->labelCourses->TabIndex = 2;
			this->labelCourses->Text = L"Courses [Id,Slope,Rating,Par,Name]";
			// 
			// listBoxCourses
			// 
			this->listBoxCourses->FormattingEnabled = true;
			this->listBoxCourses->ItemHeight = 18;
			this->listBoxCourses->Location = System::Drawing::Point(23, 105);
			this->listBoxCourses->Name = L"listBoxCourses";
			this->listBoxCourses->Size = System::Drawing::Size(673, 112);
			this->listBoxCourses->TabIndex = 3;
			// 
			// labelGolfers
			// 
			this->labelGolfers->AutoSize = true;
			this->labelGolfers->Location = System::Drawing::Point(20, 251);
			this->labelGolfers->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelGolfers->Name = L"labelGolfers";
			this->labelGolfers->Size = System::Drawing::Size(124, 18);
			this->labelGolfers->TabIndex = 4;
			this->labelGolfers->Text = L"Golfers [Id,Name]";
			// 
			// listBoxGolfers
			// 
			this->listBoxGolfers->FormattingEnabled = true;
			this->listBoxGolfers->ItemHeight = 18;
			this->listBoxGolfers->Location = System::Drawing::Point(22, 275);
			this->listBoxGolfers->Name = L"listBoxGolfers";
			this->listBoxGolfers->Size = System::Drawing::Size(673, 166);
			this->listBoxGolfers->TabIndex = 5;
			this->listBoxGolfers->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBoxGolfers_SelectedIndexChanged);
			// 
			// labelRounds
			// 
			this->labelRounds->AutoSize = true;
			this->labelRounds->Location = System::Drawing::Point(20, 748);
			this->labelRounds->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelRounds->Name = L"labelRounds";
			this->labelRounds->Size = System::Drawing::Size(346, 18);
			this->labelRounds->TabIndex = 6;
			this->labelRounds->Text = L"Rounds [Golfer,Date,Course,Scorecard] (unsorted)";
			// 
			// listBoxRounds
			// 
			this->listBoxRounds->FormattingEnabled = true;
			this->listBoxRounds->ItemHeight = 18;
			this->listBoxRounds->Location = System::Drawing::Point(18, 769);
			this->listBoxRounds->Name = L"listBoxRounds";
			this->listBoxRounds->Size = System::Drawing::Size(673, 112);
			this->listBoxRounds->TabIndex = 7;
			// 
			// buttonAddRound
			// 
			this->buttonAddRound->Location = System::Drawing::Point(441, 17);
			this->buttonAddRound->Margin = System::Windows::Forms::Padding(4);
			this->buttonAddRound->Name = L"buttonAddRound";
			this->buttonAddRound->Size = System::Drawing::Size(250, 32);
			this->buttonAddRound->TabIndex = 8;
			this->buttonAddRound->Text = L"Add Round ..";
			this->buttonAddRound->UseVisualStyleBackColor = true;
			this->buttonAddRound->Click += gcnew System::EventHandler(this, &Form1::buttonAddRound_Click);
			// 
			// labelGolferRounds
			// 
			this->labelGolferRounds->AutoSize = true;
			this->labelGolferRounds->Location = System::Drawing::Point(20, 475);
			this->labelGolferRounds->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelGolferRounds->Name = L"labelGolferRounds";
			this->labelGolferRounds->Size = System::Drawing::Size(458, 18);
			this->labelGolferRounds->TabIndex = 9;
			this->labelGolferRounds->Text = L"Rounds for Selected Golfer [Golfer,Date,Course,Scorecard] (sorted)";
			// 
			// listBoxGolferRounds
			// 
			this->listBoxGolferRounds->FormattingEnabled = true;
			this->listBoxGolferRounds->ItemHeight = 18;
			this->listBoxGolferRounds->Location = System::Drawing::Point(22, 496);
			this->listBoxGolferRounds->Name = L"listBoxGolferRounds";
			this->listBoxGolferRounds->Size = System::Drawing::Size(673, 220);
			this->listBoxGolferRounds->TabIndex = 10;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(716, 909);
			this->Controls->Add(this->listBoxGolferRounds);
			this->Controls->Add(this->labelGolferRounds);
			this->Controls->Add(this->buttonAddRound);
			this->Controls->Add(this->listBoxRounds);
			this->Controls->Add(this->labelRounds);
			this->Controls->Add(this->listBoxGolfers);
			this->Controls->Add(this->labelGolfers);
			this->Controls->Add(this->listBoxCourses);
			this->Controls->Add(this->labelCourses);
			this->Controls->Add(this->btnConvert);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Form1";
			this->Text = L"151 League ..";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	// Internal.
	protected:
		static Form1^ m_form1;
	// External.
	public:
		static Form1^ getForm() {
			return m_form1;
		}

	// Internal.
	protected:
		static void ShowMessageBox(IWin32Window^ owner, String^ message, String^ caption) {
			MessageBox::Show( owner, message, caption, MessageBoxButtons::OK );
		}
		void ShowMessageBox(String^ message, String^ caption) {
			if ( !getOpen() ) { // the window is not open!
				return;
			}
			ShowMessageBox(this, message, caption);
		}
		void ShowMessageBox(String^ message) {
			ShowMessageBox(message, "");
		}

	private: System::Void btnConvert_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void buttonAddRound_Click(System::Object^  sender, System::EventArgs^  e);

	// Window state.
	protected:
		bool m_open;
	public:
		bool getOpen() {
			return m_open;
		}
		void setOpen(const bool open) {
			m_open = open;
		}
	
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void listBoxGolfers_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);

	// External.
	public:
		String^ m_strLastDate;

		String^ getCourseIdx(int idx);
		String^ getCourseSlope(int idx);
		String^ getCourseRating(int idx);
		String^ getCoursePar(int idx);
		String^ getCourseName(int idx);

		String^ getGolferIdx(int idx);
		String^ getGolferName(int idx);
		String^ getGolferInit(int idx);

		System::Void reload_Courses();
		System::Void reload_Golfers();
		System::Void reload_GolferRounds(); // sorted
		System::Void reload_Rounds();
};
}

