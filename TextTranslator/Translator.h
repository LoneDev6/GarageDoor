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
#include <cstring>
#include <vector>
#include <algorithm>

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

struct PartialPattern
{
	std::string key;
	std::string value;
	int keyLen;
	
	bool operator<(const PartialPattern& other) const
	{
		return keyLen > other.keyLen; // Sort descending by length
	}
};

class Translator
{
	LPCTSTR path;
	TCHAR originalWorkingDirectory[MAX_PATH];

	std::wregex regex_ignorable_1;
	std::vector<PartialPattern> partialsCache;
	bool partialsCacheLoaded = false;

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

	void loadAndSortPartials()
	{
		if (partialsCacheLoaded) return;
		
		fixObscureBug();
		
		char keyBuffer[256];
		char valueBuffer[256];
		char profileBuffer[65536];
		
		DWORD bytesRead = GetPrivateProfileSectionA("Partials", profileBuffer, sizeof(profileBuffer), path);
		if (bytesRead == 0)
		{
			partialsCacheLoaded = true;
			return;
		}
		
		// Parse and store all patterns
		for (const char* p = profileBuffer; *p; p += strlen(p) + 1)
		{
			const char* equals = strchr(p, '=');
			if (!equals) continue;
			
			int keyLen = (int)(equals - p);
			memcpy(keyBuffer, p, keyLen);
			keyBuffer[keyLen] = '\0';
			strcpy(valueBuffer, equals + 1);
			
			PartialPattern pattern;
			pattern.key = std::string(keyBuffer);
			pattern.value = std::string(valueBuffer);
			pattern.keyLen = keyLen;
			
			partialsCache.push_back(pattern);
		}
		
		// Sort by length descending (longest first)
		std::sort(partialsCache.begin(), partialsCache.end());
		
		partialsCacheLoaded = true;
		std::cout << "[OK] Loaded and sorted " << partialsCache.size() << " patterns from Partials\n";
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

		std::string translated = getTranslation(key);
		return !translated.empty() && translated.compare("NOT_TRANSLATED_TEXT") != 0;
	}

	std::string getTranslation(LPCSTR key)
	{
		fixObscureBug();

		char result[255];
		GetPrivateProfileStringA("Phrases", key, "", result, 255, path);
		std::string tmp = std::string(result);

		// Not found in Phrases section, in case some items names are found
		if (strcmp(result, "") == 0)
		{
			GetPrivateProfileStringA("Partials", key, "", result, 255, path);
			tmp = std::string(result);
		}

		// If not found in Phrases, search for patterns in Partials section and replace
		if (strcmp(result, "") == 0)
		{
			// Load partials cache on first call
			if (!partialsCacheLoaded)
			{
				loadAndSortPartials();
			}
			
			if (!partialsCache.empty())
			{
				tmp = std::string(key); // Start with original text
				
				// Iterate through sorted patterns (longest first)
				for (const auto& pattern : partialsCache)
				{
					// If the pattern is found in the text, replace it
					if (strstr(tmp.c_str(), pattern.key.c_str()) != nullptr)
					{
						findAndReplaceAll(tmp, pattern.key, pattern.value);
					}
				}
			}
		}
		
		std::string s(1, '\u000A'); // Replace newline markers
		findAndReplaceAll(tmp, "%n", s);
		return tmp.c_str();
	}	
	
	void saveUnknownText(LPCSTR key, LPCSTR str)
	{
		fixObscureBug();

		WritePrivateProfileStringA("Phrases", key, str, path);
	}
};