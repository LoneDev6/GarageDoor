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