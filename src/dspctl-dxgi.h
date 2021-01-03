/**
 * Copyright (C) Francesco Fusco. All rights reserved.
 * License: https://github.com/Fushko/gammy#license
 */

#ifndef DXGIDUPL_H
#define DXGIDUPL_H

#include <Windows.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d11.h>
#include <stdint.h>
#include <vector>
#include <string>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "Advapi32.lib")

namespace GDI {
static std::vector<HDC>     hdcs;
static std::vector<uint8_t> buf;
extern int64_t              width;
extern int64_t              height;
extern int                  primary_dc_idx;
int  numDisplays();
int  getScreenBrightness();
void createDCs(std::wstring &primary_screen_name);
void setGamma(int, int);
}

class DspCtl
{
public:
	DspCtl();
	~DspCtl();

	int  getScreenBrightness() noexcept;
	void setGamma(int brt, int temp);
	void setInitialGamma(bool set_previous);
private:
	ID3D11Device*           d3d_device;
	ID3D11DeviceContext*    d3d_context;
	IDXGIOutput1*           output1;
	IDXGIOutputDuplication* duplication;
	D3D11_TEXTURE2D_DESC    tex_desc;
	std::wstring            primary_screen_name;

	bool useDXGI;
	bool init();
	void restart();
};

#endif // DXGIDUPL_H

