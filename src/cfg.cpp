/**
 * Copyright (C) 2019 Francesco Fusco. All rights reserved.
 * License: https://github.com/Fushko/gammy#license
 */

#include "cfg.h"
#include "utils.h"
#include "defs.h"
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <Windows.h> // GetModuleFileNameW
#endif

json setDefault()
{
	return
	{
		{"brt_fps", 60},
		{"temp_fps", 45},
		{"brightness", brt_slider_steps},
		{"min_br", brt_slider_steps / 2 },
		{"max_br", brt_slider_steps },
		{"offset", brt_slider_steps / 3 },
		{"speed", 5 },
		{"temp_speed", 30.0 },
		{"threshold", 36 },
		{"polling_rate", 100 },
		{"temp_step", 0 },
		{"temp_high", max_temp_kelvin },
		{"temp_low", 3400 },
		{"temp_state", 0 },
		{"time_start", "17:00:00" },
		{"time_end", "06:00:00" },
		{"auto_br", true },
		{"auto_temp", false },
		{"extend_br", false },
		{"log_lvl", plog::warning }
	};
}

json cfg = setDefault();

void read()
{
#ifdef _WIN32
	const std::wstring path = getExecutablePath();
#else
	const std::string path = getConfigPath();
#endif

	std::ifstream file(path, std::fstream::in | std::fstream::app);

	if(!file.good() || !file.is_open()) {
		LOGE << "Unable to open config at path: " << path;
		return;
	}

	// Seek file end
	file.seekg(0, std::ios::end);

	// If end position is 0, create the file
	if(file.tellg() == 0) {
		write();
		return;
	}

	// Seek file start
	file.seekg(0);

	json tmp;

	try {
		file >> tmp;
	}
	catch (json::exception &e) {

		LOGE << e.what() << " - Resetting config...";

		cfg = setDefault();
		write();

		return;
	}

	cfg.update(tmp);

	LOGV << "Config parsed";
}

void write()
{
#ifdef _WIN32
	const std::wstring path = getExecutablePath();
#else
	const std::string path = getConfigPath();
#endif

	std::ofstream file(path, std::ofstream::out);

	if(!file.good() || !file.is_open()) {
		LOGE << "Unable to open config file";
		return;
	}

	try {
		file << std::setw(4) << cfg;
	}
	catch (json::exception &e) {
		LOGE << e.what() << " id: " << e.id;
		return;
	}

	LOGV << "Config set";
}

#ifndef _WIN32
std::string getConfigPath()
{
	constexpr const char *cfg_name = "gammy";

	char buf[4096];

	const char *home   = getenv("XDG_CONFIG_HOME");
	const char *format = home ? "%s/%s" : "%s/.config/%s";

	if(!home) home = getenv("HOME");

	sprintf(buf, format, home, cfg_name);

	return std::string(buf);
}

#else
std::wstring getExecutablePath()
{
	wchar_t buf[FILENAME_MAX] {};
	GetModuleFileNameW(nullptr, buf, FILENAME_MAX);
	std::wstring path(buf);

	std::wstring appname = L"gammy.exe";
	path.erase(path.find(appname), appname.length());

	path += L"gammysettings.cfg";

	return path;
}
#endif


