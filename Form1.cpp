#using <System.dll>

#include "stdafx.h"
#include "Form1.h"
#include "CMyFile.h"

#include "Round.h"

using namespace System;
using namespace System::Collections::Generic;

using namespace handicap;

String^ getListEntry(List<String^>^ list, int entry)
{
	if (entry >= list->Count)
		return "";
	return dynamic_cast<String^>(list[entry]);
}

String^ getCsvIdx(String^ str, int idx)
{
	array<Char>^ comma = gcnew array<Char>{','};
	array<String^>^ result = str->Split(comma, StringSplitOptions::None);

	if (idx >= result->Length)
		return "";
	return result[idx];
}

String^ getSpaceSeparatedIdx(String^ str, int idx)
{
	array<Char>^ space = gcnew array<Char>{' '};
	array<String^>^ result = str->Split(space, StringSplitOptions::None);

	if (idx >= result->Length)
		return "";
	return result[idx];
}

String^ getListBoxEntry(ListBox^ listBox, int entry)
{
	if (entry >= listBox->Items->Count)
		return "";
	return dynamic_cast<String^>(listBox->Items[entry]);
}

int str2int(String^ str)
{
	if (str->Length < 1)
		return 0;
	return Int32::Parse(str);
}

double str2float(String^ str)
{
	if (str->Length < 1)
		return 0;
	return Double::Parse(str);
}

double calculateAgs(double handicap, String^ scores, String^ pars)
{
	double ags = 0;

    for (int i = 0; i<9; i++) {

		int score = str2int(getSpaceSeparatedIdx(scores, i));
		int par = str2int(getSpaceSeparatedIdx(pars, i));

        int delta = score - par;
        if (handicap < 10) {
            if (delta > 2)
                score = par + 2;
        } else if (handicap < 20) {
            if (score > 7)
                score = 7;
        } else if (handicap < 30) {
            if (score > 8)
                score = 8;
        } else if (handicap < 40) {
            if (score > 9)
                score = 9;
        } else { // 40+
            if (score > 10)
                score = 10;
        }
        ags += (double)score;
    }

	return ags;
}

int howMany(int count)
{
	int qty = 10;
	if (count < 7) {
        qty = 1;
    } else if (count < 9) {
        qty = 2;
    } else if (count < 11) {
        qty = 3;
    } else if (count < 13) {
        qty = 4;
    } else if (count < 15) {
        qty = 5;
    } else if (count < 17) {
        qty = 6;
    } else if (count < 18) {
        qty = 7;
    } else if (count < 19) {
        qty = 8;
    } else if (count < 20) {
        qty = 9;
    } /* else {
        qty = 10;
    } */
	return qty;
}

System::Void Form1::btnConvert_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ strCwd = Directory::GetCurrentDirectory();

	CMyFile^ myFile = gcnew CMyFile( strCwd + "\\" + "handicaps.csv", true );
	if ( nullptr != myFile ) {
		if ( myFile->open( (UInt8)CMyFile::OpenMode::FILE_WRITE | (UInt8)CMyFile::OpenMode::FILE_TRUNCATE ) ) {

			for (int golfer = 0; golfer<this->listBoxGolfers->Items->Count; golfer++)
			{
				String^ strGolferIdx = getGolferIdx(golfer);
				String^ strGolferName = getGolferName(golfer);
				String^ strGolferInit = getGolferInit(golfer);

				List<String^>^ list = gcnew List<String^>();

				for (int i = 0; i<this->listBoxRounds->Items->Count; i++)
				{
					String^ str = dynamic_cast<String^>(this->listBoxRounds->Items[i]);
					if (str->Length < 1) continue;

					array<Char>^ comma = gcnew array<Char>{','};
					array<String^>^ result = str->Split(comma, StringSplitOptions::None);

					if (0 != result[0]->Trim()->CompareTo(strGolferIdx))
						continue;

					// sort
					if (list->Count < 1)
						list->Add(str);
					else
					{
						for (int j = 0; j<list->Count; j++)
						{
							String^ strExisting = dynamic_cast<String^>(list[j]);
							if (str->CompareTo(strExisting) <= 0) // the new value is less than current index
							{
								list->Insert(j, str);
								break; // done!
							}
							if (j >= list->Count - 1) // not found!
							{
								list->Add(str);
								break;
							}
						}
					}
				}

				// delete old entries until the total is less than: 11
				for (; list->Count > 11;)
				{
					list->RemoveAt(0); // remove oldest!
				}

				// figure out: diff for each round, then insert it (sorted) into: diffs
				int qty = 0;
				List<double>^ diffs = gcnew List<double>();

				for (int j = 0; j<list->Count; j++)
				{
					String^ scores = getCsvIdx(getListEntry(list, j), 3);
					String^ strCourseIdx = getCsvIdx(getListEntry(list, j), 2);
					String^ strPar = "";
					for (int k = 0; k<this->listBoxCourses->Items->Count; k++)
					{
						String^ strLbCourse = getListBoxEntry(this->listBoxCourses, k);
						if (0 != strCourseIdx->CompareTo(getCsvIdx(strLbCourse, 0)))
							continue;
						double slope = str2float(getCsvIdx(strLbCourse, 1));
						double rating = str2float(getCsvIdx(strLbCourse, 2));
						String^ pars = getCsvIdx(strLbCourse, 3);
						double ags = calculateAgs(str2float(strGolferInit)*2, scores, pars);
						if (slope < 1) continue; // error check!
						double val = ((ags - (rating / 2)) * 113) / slope; // diff

						// sort
						if (diffs->Count < 1)
							diffs->Add(val);
						else
						{
							for (int x = 0; x<diffs->Count; x++)
							{
								if (val < diffs[x]) // the new value is less than current index
								{
									diffs->Insert(x, val);
									break; // done!
								}
								if (x >= diffs->Count - 1) // not found!
								{
									diffs->Add(val);
									break;
								}
							}
						}
						qty++;
						break;
					}
				}

				if (!qty) continue; // not an error check!

				qty = howMany(qty);

				double average = 0; // scroll through and pick the lowest, and compute the average!
				for (int x = 0; x<qty; x++)
				{
					average += diffs[x];
				}
				average = (average / qty) * 0.96;

				int hdcp10X = (int)((double)10 * average);
				int hdcp = hdcp10X / 10;
				int remainder = hdcp10X % 10;
				String^ specifier = "G";

				myFile->write( "\r\n" + strGolferName + " " + hdcp.ToString(specifier) + "." + remainder.ToString(specifier) );
			}

			myFile->close();

			delete myFile;
			myFile = nullptr;
		}
	}
}

// get the ASCII 'course id' in: courses.csv

String^ Form1::getCourseIdx(int idx)
{
	String^ str = dynamic_cast<String^>(this->listBoxCourses->Items[idx]);

	array<Char>^ sep = gcnew array<Char>{','};
	array<String^>^ result = str->Split(sep, StringSplitOptions::None);

	return result[0];
}

// get the ASCII 'slope' in: courses.csv

String^ Form1::getCourseSlope(int idx)
{
	String^ str = dynamic_cast<String^>(this->listBoxCourses->Items[idx]);

	array<Char>^ sep = gcnew array<Char>{','};
	array<String^>^ result = str->Split(sep, StringSplitOptions::None);

	return result[1];
}

// get the ASCII 'rating' in: courses.csv

String^ Form1::getCourseRating(int idx)
{
	String^ str = dynamic_cast<String^>(this->listBoxCourses->Items[idx]);

	array<Char>^ sep = gcnew array<Char>{','};
	array<String^>^ result = str->Split(sep, StringSplitOptions::None);

	return result[2];
}

// get the ASCII 'par for each hole' in: courses.csv

String^ Form1::getCoursePar(int idx)
{
	String^ str = dynamic_cast<String^>(this->listBoxCourses->Items[idx]);

	array<Char>^ sep = gcnew array<Char>{','};
	array<String^>^ result = str->Split(sep, StringSplitOptions::None);

	return result[3];
}

// get the ASCII 'course name' in: courses.csv

String^ Form1::getCourseName(int idx)
{
	String^ str = dynamic_cast<String^>(this->listBoxCourses->Items[idx]);

	array<Char>^ sep = gcnew array<Char>{','};
	array<String^>^ result = str->Split(sep, StringSplitOptions::None);

	return result[4];
}

// get the ASCII 'golfer id' in: golfers.csv

String^ Form1::getGolferIdx(int idx)
{
	String^ str = dynamic_cast<String^>(this->listBoxGolfers->Items[idx]);

	array<Char>^ sep = gcnew array<Char>{','};
	array<String^>^ result = str->Split(sep, StringSplitOptions::None);

	return result[0];
}

// get the ASCII 'golfer name' in: golfers.csv

String^ Form1::getGolferName(int idx)
{
	String^ str = dynamic_cast<String^>(this->listBoxGolfers->Items[idx]);

	array<Char>^ sep = gcnew array<Char>{','};
	array<String^>^ result = str->Split(sep, StringSplitOptions::None);

	str = result[1]->Trim();
	if (str->Length < 1)
		str = "Error";
	return str;
}

// get the ASCII 'golfer initial handicap' in: golfers.csv

String^ Form1::getGolferInit(int idx)
{
	String^ str = dynamic_cast<String^>(this->listBoxGolfers->Items[idx]);

	array<Char>^ sep = gcnew array<Char>{','};
	array<String^>^ result = str->Split(sep, StringSplitOptions::None);

	str = result[2]->Trim();
	if (str->Length < 1)
		str = "0";
	return str;
}

System::Void Form1::buttonAddRound_Click(System::Object^  sender, System::EventArgs^  e) {

	int course = this->listBoxCourses->SelectedIndex;
	if (course < 0)
	{
		ShowMessageBox("Select a course!");
		return;
	}

	int golfer = this->listBoxGolfers->SelectedIndex;
	if (golfer < 0)
	{
		ShowMessageBox("Select a golfer!");
		return;
	}

	Round^ roundDialog = gcnew Round;

	if (this->m_strLastDate->Length > 0)
		roundDialog->m_strLastDate = this->m_strLastDate;

	roundDialog->m_strCourseName = getCourseName(course);
	roundDialog->m_strCoursePar = getCoursePar(course);
	
	roundDialog->m_strRound = "";

	roundDialog->m_strGolfer = getGolferName(golfer);

	if ( System::Windows::Forms::DialogResult::OK != roundDialog->ShowDialog() ) { // OK
		if (roundDialog->m_strErr->Length > 0)
			ShowMessageBox("Error: " + roundDialog->m_strErr);
		return;
	}

	String^ strGolferIdx = getGolferIdx(golfer);
	this->m_strLastDate = roundDialog->m_strLastDate;
	String^ strCourseIdx = getCourseIdx(course);
	String^ strRound = roundDialog->m_strRound->Trim();

	String^ line = strGolferIdx + "," + this->m_strLastDate + "," + strCourseIdx + "," + strRound; //ShowMessageBox(line);

	String^ strCwd = Directory::GetCurrentDirectory();

	CMyFile^ myFile = gcnew CMyFile( strCwd + "\\" + "rounds.csv", true );
	if ( nullptr != myFile ) {
		if ( myFile->open( (UInt8)CMyFile::OpenMode::FILE_WRITE | (UInt8)CMyFile::OpenMode::FILE_APPEND ) ) {
			
			myFile->write( "\r\n" + line );

			myFile->close();
		}

		delete myFile;
		//myFile = nullptr;
	}

	reload_GolferRounds();
	reload_Rounds();
}

System::Void Form1::listBoxGolfers_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	reload_GolferRounds();
}

System::Void Form1::reload_Courses()
{
	String^ strCwd = Directory::GetCurrentDirectory();

	this->listBoxCourses->Items->Clear();

	String^ strCourses = strCwd + "\\" + "courses.csv";
	if ( CMyFileHelper::exists(strCourses, true) ) { // quiet!

		CMyFile^ myFile = gcnew CMyFile( strCourses, true );
		if ( nullptr != myFile ) {
			if ( myFile->open( (UInt8)CMyFile::OpenMode::FILE_READ ) ) {

				strCourses = ""; // = String::Format("len = {0}", len);

				long len = myFile->getLength();
				if (len > 0)
				{
					array<UInt8>^ cArr = gcnew array<UInt8>( len );
					if (nullptr != cArr) {
						Int32 res = myFile->read( cArr, len ); // total number of bytes read into the buffer
						if (res > 0)
							strCourses = System::Text::Encoding::Default->GetString(cArr);

						if (strCourses->Length > 0)
						{
							array<Char>^ sep = gcnew array<Char>{'\r'};
							array<String^>^ result = strCourses->Split(sep, StringSplitOptions::None);

							for (int i = 0; i<result->Length; i++)
							{
								this->listBoxCourses->Items->Add(result[i]->Trim());
							}
						}
					}
				}

				myFile->close();
			}

			delete myFile;
			myFile = nullptr;
		}
	}
}

System::Void Form1::reload_Golfers()
{
	String^ strCwd = Directory::GetCurrentDirectory();

	this->listBoxGolfers->Items->Clear();

	String^ strGolfers = strCwd + "\\" + "golfers.csv";
	if ( CMyFileHelper::exists(strGolfers, true) ) { // quiet!

		CMyFile^ myFile = gcnew CMyFile( strGolfers, true );
		if ( nullptr != myFile ) {
			if ( myFile->open( (UInt8)CMyFile::OpenMode::FILE_READ ) ) {

				strGolfers = "";

				long len = myFile->getLength();
				if (len > 0)
				{
					array<UInt8>^ cArr = gcnew array<UInt8>( len );
					if (nullptr != cArr) {
						Int32 res = myFile->read( cArr, len ); // total number of bytes read into the buffer
						if (res > 0)
							strGolfers = System::Text::Encoding::Default->GetString(cArr);

						if (strGolfers->Length > 0)
						{
							array<Char>^ sep = gcnew array<Char>{'\r'};
							array<String^>^ result = strGolfers->Split(sep, StringSplitOptions::None);

							for (int i = 0; i<result->Length; i++)
							{
								this->listBoxGolfers->Items->Add(result[i]->Trim());
							}
						}
					}
				}

				myFile->close();
			}

			delete myFile;
			myFile = nullptr;
		}
	}
}

System::Void Form1::reload_GolferRounds()
{
	this->listBoxGolferRounds->Items->Clear();

	int golfer = this->listBoxGolfers->SelectedIndex;
	if (golfer < 0)
	{
		return;
	}
	String^ strGolferIdx = getGolferIdx(golfer);

	String^ strCwd = Directory::GetCurrentDirectory();

	String^ strRounds = strCwd + "\\" + "rounds.csv";
	if ( CMyFileHelper::exists(strRounds, true) ) { // quiet!

		CMyFile^ myFile = gcnew CMyFile( strRounds, true );
		if ( nullptr != myFile ) {
			if ( myFile->open( (UInt8)CMyFile::OpenMode::FILE_READ ) ) {

				strRounds = "";

				long len = myFile->getLength();
				if (len > 0)
				{
					array<UInt8>^ cArr = gcnew array<UInt8>( len );
					if (nullptr != cArr) {
						Int32 res = myFile->read( cArr, len ); // total number of bytes read into the buffer
						if (res > 0)
							strRounds = System::Text::Encoding::Default->GetString(cArr);

						if (strRounds->Length > 0)
						{
							array<Char>^ sep = gcnew array<Char>{'\r'};
							array<String^>^ result = strRounds->Split(sep, StringSplitOptions::None);

							for (int i = 0; i<result->Length; i++)
							{
								String^ str = result[i]->Trim();
								if (str->Length < 1) continue;

								array<Char>^ comma = gcnew array<Char>{','};
								array<String^>^ result2 = str->Split(comma, StringSplitOptions::None);

								if (0 != result2[0]->Trim()->CompareTo(strGolferIdx))
									continue;
								
								// sort
								if (this->listBoxGolferRounds->Items->Count < 1)
									this->listBoxGolferRounds->Items->Add(str);
								else
								{
									for (int j = 0; j<this->listBoxGolferRounds->Items->Count; j++)
									{
										String^ strExisting = dynamic_cast<String^>(this->listBoxGolferRounds->Items[j]);
										if (str->CompareTo(strExisting) <= 0) // the new value is less than current index
										{
											this->listBoxGolferRounds->Items->Insert(j, str);
											break; // done!
										}
										if (j >= this->listBoxGolferRounds->Items->Count - 1) // not found!
										{
											this->listBoxGolferRounds->Items->Add(str);
											break;
										}
									}
								}

								// delete old entries until the total is less than: 11
								for (; this->listBoxGolferRounds->Items->Count > 11;)
								{
									this->listBoxGolferRounds->Items->RemoveAt(0); // remove oldest!
								}
							}
						}
					}
				}

				myFile->close();
			}

			delete myFile;
			myFile = nullptr;
		}
	}
}

System::Void Form1::reload_Rounds()
{
	String^ strCwd = Directory::GetCurrentDirectory();

	this->listBoxRounds->Items->Clear();

	String^ strRounds = strCwd + "\\" + "rounds.csv";
	if ( CMyFileHelper::exists(strRounds, true) ) { // quiet!

		CMyFile^ myFile = gcnew CMyFile( strRounds, true );
		if ( nullptr != myFile ) {
			if ( myFile->open( (UInt8)CMyFile::OpenMode::FILE_READ ) ) {

				strRounds = "";

				long len = myFile->getLength();
				if (len > 0)
				{
					array<UInt8>^ cArr = gcnew array<UInt8>( len );
					if (nullptr != cArr) {
						Int32 res = myFile->read( cArr, len ); // total number of bytes read into the buffer
						if (res > 0)
							strRounds = System::Text::Encoding::Default->GetString(cArr);

						if (strRounds->Length > 0)
						{
							array<Char>^ sep = gcnew array<Char>{'\r'};
							array<String^>^ result = strRounds->Split(sep, StringSplitOptions::None);

							for (int i = 0; i<result->Length; i++)
							{
								this->listBoxRounds->Items->Add(result[i]->Trim());
							}
						}
					}
				}

				myFile->close();
			}

			delete myFile;
			myFile = nullptr;
		}
	}
}

System::Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	
	// Courses

	reload_Courses();

	// Golfers

	reload_Golfers();

	// Rounds

	reload_Rounds();
}



