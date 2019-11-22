#pragma once

#include <string>


class StringConverter
{
public:
    static std::string wcharPtr2string(const wchar_t* str)
    {
        std::wstring wstr(str);
        std::string resultStr;
        resultStr.assign(wstr.begin(), wstr.end());
        return resultStr;
    }

    static std::string wstring2string(const std::wstring& str)
    {
        std::string resultStr;
        resultStr.assign(str.begin(), str.end());
        return resultStr;
    }

    static std::wstring string2wstring(const std::string& str)
    {
        std::wstring resultStr;
        resultStr.assign(str.begin(), str.end());
        return resultStr;
    }

    static std::wstring charPtr2wstring(const char* str)
    {
        std::string tempString(str);
        std::wstring resultStr;
        resultStr.assign(tempString.begin(), tempString.end());
        return resultStr;
    }
};
