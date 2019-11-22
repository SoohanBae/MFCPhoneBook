#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

using namespace std;

class CFileReadManager : public CSingleton<CFileReadManager>{

public:
    CFileReadManager(void);
    ~CFileReadManager(void);

	vector<vector<CString>> CsvTo2dVectorCString(const CString& fileName);
    vector<CString> CsvReadRow(istream &file);
	

};