#include "StdAfx.h"
#include "Round.h"

using namespace System;
using namespace System::Globalization;

using namespace handicap;

System::Void Round::buttonOk_Click(System::Object^  sender, System::EventArgs^  e) {

	this->DialogResult = ::DialogResult::Cancel;

	if (this->textBoxDate->Text->Length < 1)
	{
		this->DialogResult = ::DialogResult::Cancel;
		this->m_strErr = "No Date Entered!";
		return;
	}
	if (this->textBoxRound->Text->Length < 1)
	{
		this->DialogResult = ::DialogResult::Cancel;
		this->m_strErr = "No Round Entered!";
		return;
	}

	String^ str = this->textBoxRound->Text;

	array<Char>^ space = gcnew array<Char>{' '};
	array<String^>^ result = str->Split(space, StringSplitOptions::None);

	if (9 != result->Length)
	{
		this->DialogResult = ::DialogResult::Cancel;
		this->m_strErr = "Incorrect Round Entered!";
		return;
	}

	for (int i = 0; i<result->Length; i++)
	{
		CultureInfo^ provider;
		NumberStyles styles = NumberStyles::Integer;

		// If currency symbol is allowed, use en-US culture. 
		if (((Int32) (styles & NumberStyles::AllowCurrencySymbol)) > 0)
			provider = gcnew CultureInfo("en-US");
		else
			provider = CultureInfo::InvariantCulture;

		Int32 hole = 0;
		if (!Int32::TryParse(result[i]->Trim(), styles, provider, hole))
		{
			this->DialogResult = ::DialogResult::Cancel;
			this->m_strErr = "Non-number Entered!";
			return;
		}
	}

	this->DialogResult = ::DialogResult::OK;

	this->m_strLastDate = this->textBoxDate->Text;

	this->m_strRound = this->textBoxRound->Text;
}

System::Void Round::Round_Load(System::Object^  sender, System::EventArgs^  e) {

	if (this->m_strLastDate->Length > 0)
		this->textBoxDate->Text = this->m_strLastDate;

	this->textBoxCourseName->Text = this->m_strCourseName;
	this->textBoxCoursePar->Text = this->m_strCoursePar;

	this->textBoxRound->Text = this->m_strRound;

	this->textBoxGolfer->Text = this->m_strGolfer;
}

