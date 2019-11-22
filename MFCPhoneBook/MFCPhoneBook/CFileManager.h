#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

using namespace std;

class CFileManager : public CSingleton<CFileManager>{

public:
    CFileManager(void);
    ~CFileManager(void);

	vector<vector<CString>> CsvTo2dVectorCString(const CString& fileName);
    vector<CString> CsvReadRow(istream &file);
	
	void TwoDVectorCStringToCsv(const vector<vector<CString>>& listControlVector, const CString& fileName);

};