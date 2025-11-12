/*
LoneDev super professional License


Copyright (c) 2020 LoneDev


Permissions:
- You can edit this source and use it in any free project you want

Limitations:
- You cannot use this source or edited versions in commercial projects
- You cannot use this code in projects that earn using advertisements or that take donations
- You cannot resell this code
- You cannot state that this is your code
- You must include LoneDev in the credits of your project
- You must share the edited source code
- You must include this license file
*/

#pragma once

#include <iostream>
#include <regex>

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

class Translator
{
	LPCTSTR path;
	TCHAR originalWorkingDirectory[MAX_PATH];

	std::wregex regex_ignorable_1;

public:
	Translator()
	{
		// Set locale to Shift JIS (Japanese) - code 932
		setlocale(LC_ALL, ".932");
		path = ".\\translation.ini";
		std::cout << "[OK] Loaded translation.ini file: " << std::string(path) << "\n";

		GetCurrentDirectory(MAX_PATH, originalWorkingDirectory);

		regex_ignorable_1 = std::wregex(L"[0-9,０-９]+");
	}

	void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
	{
		// Get the first occurrence
		size_t pos = data.find(toSearch);
		// Repeat till end is reached
		while (pos != std::string::npos)
		{
			// Replace this occurrence of Sub String
			data.replace(pos, toSearch.size(), replaceStr);
			// Get the next occurrence from the current position
			pos = data.find(toSearch, pos + replaceStr.size());
		}
	}

	inline std::string GetExeDirectory()
	{
		char path[_MAX_PATH] = "";
		GetModuleFileNameA(NULL, path, sizeof(path));
		PathRemoveFileSpecA(path);
		PathAddBackslashA(path); // another path function!
		return path;
	}

	void fixObscureBug()
	{
		SetCurrentDirectory(originalWorkingDirectory);
	}

	bool isIgnorable(LPCSTR key)
	{
		std::string s1(key);
		std::wstring s(s1.begin(), s1.end());
		std::cout << "1: " << std::regex_match(s, regex_ignorable_1) << std::endl;

		if(std::regex_match(s, regex_ignorable_1))
			return true;
		return false;
	}
	bool hasTranslation(LPCSTR key)
	{
		fixObscureBug();

		char result[255] = "";
		DWORD success = GetPrivateProfileStringA("Phrases", key, "", result, 255, path);
		std::cout << "has translation success: " << success << std::endl;
		return strcmp(result, "") != 0;
	}

	std::string getTranslation(LPCSTR key)
	{
		fixObscureBug();

		char result[255];
		GetPrivateProfileStringA("Phrases", key, "", result, 255, path);
		std::string tmp = std::string(result);
		std::string s(1, '\u000A');//magic stuff here
		findAndReplaceAll(tmp, "%n", s);
		return tmp.c_str();
	}

	void saveUnknownText(LPCSTR key, LPCSTR str)
	{
		fixObscureBug();

		WritePrivateProfileStringA("Phrases", key, str, path);
	}
};