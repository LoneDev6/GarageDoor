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
#include <windows.h>

template <typename Enumeration> auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

struct handle_data 
{
	unsigned long process_id;
	HWND window_handle;
};

static BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lparam)
{
	auto& data = *reinterpret_cast<handle_data*>(lparam);

	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);

	if (data.process_id != process_id)
		return TRUE;

	data.window_handle = handle;
	return FALSE;
}

static HWND find_main_window()
{
	handle_data data{};

	data.process_id = GetCurrentProcessId();
	data.window_handle = nullptr;
	EnumWindows(enum_windows_callback, reinterpret_cast<LPARAM>(&data));

	return data.window_handle;
}