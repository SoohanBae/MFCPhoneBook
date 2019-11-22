#include "stdafx.h"
#include "CFileReadManager.h"

CFileReadManager::CFileReadManager(void)
{

}


CFileReadManager::~CFileReadManager(void)
{

}

vector<vector<CString>> CFileReadManager::CsvTo2dVectorCString(const CString & fileName)
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

vector<CString> CFileReadManager::CsvReadRow(istream &file)
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


