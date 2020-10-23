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
		setlocale(LC_ALL, "");//is this useful?
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