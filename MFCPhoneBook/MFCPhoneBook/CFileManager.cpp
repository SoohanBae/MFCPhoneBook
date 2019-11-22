#include "stdafx.h"
#include "CFileManager.h"

CFileManager::CFileManager(void)
{

}


CFileManager::~CFileManager(void)
{

}

vector<vector<CString>> CFileManager::CsvTo2dVectorCString(const CString & fileName)
{
	vector<vector<CString>> csvVector;

	ifstream file(fileName);
	if (file.fail()) {
		ASSERT(0);
	}

	while (file.good()) {
		
		vector<CString> row = CsvReadRow(file);
		csvVector.push_back(row);
	}

	return csvVector;
}

vector<CString> CFileManager::CsvReadRow(istream &file)
{

	stringstream ss;
	bool inquotes = false;
	vector<CString> row;//relying on RVO
	char delimiter = ',';

	while (file.good())
	{
		char c = file.get();
		if (!inquotes && c == '"')
		{
			inquotes = true;
		}
		else if (inquotes && c == '"')
		{
			if (file.peek() == '"')
			{
				ss << (char)file.get();
			}
			else
			{
				inquotes = false;
			}
		}
		else if (!inquotes && c == delimiter)
		{
			std::string tmpS = ss.str();
			CString cs(tmpS.c_str());
			
			row.push_back(cs);
			ss.str("");
		}
		else if (!inquotes && (c == '\r' || c == '\n'))
		{
			if (file.peek() == '\n') { file.get(); }
			std::string tmpS = ss.str();
			CString cs(tmpS.c_str());
			row.push_back(cs);
			return row;
		}
		else
		{
			ss << c;
		}
	}

	return row;
}


void CFileManager::TwoDVectorCStringToCsv(const vector<vector<CString>>& listControlVector, const CString& fileName) {

	std::wofstream fstream_locale_before;
	std::locale::global(std::locale("Korean"));
	std::wofstream fstream_locale_after;

	std::wofstream outputFileText(fileName);

	if (!outputFileText.is_open()) {
		assert(0);
	}

	for (size_t i = 0; i < listControlVector.size(); i++)
	{
		size_t j = {};
		for (j = 0; j < listControlVector[i].size()-1; j++)
		{
			wstring element = listControlVector[i][j].operator LPCWSTR();

			outputFileText << element << ",";
		}
		wstring element = listControlVector[i][j].operator LPCWSTR();
		outputFileText << element << "\n";

	}

}


