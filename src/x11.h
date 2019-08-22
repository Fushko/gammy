#ifndef _WIN32
#ifndef X11_H
#define X11_H

#include <X11/Xlib.h>
#undef None //Needed to avoid build error with qurl.h
#include <cstdint>
#include <memory>
#include <vector>

class X11
{
    std::unique_ptr<Display,int(*)(Display*)> img_dsp = { nullptr,XCloseDisplay };
    std::unique_ptr<Display,int(*)(Display*)> gamma_dsp = { nullptr,XCloseDisplay }; //Need to use two diffent displays to avoid XIO fatal error
    Screen* scr;
    Window root;

    int ramp_sz;
    int scr_num;
    std::vector<uint16_t> init_ramp;

    unsigned w, h;

public:
    X11();

    unsigned getWidth();
    unsigned getHeight();

    void getX11Snapshot(uint8_t* buf);
    void fillRamp(uint16_t*& ramp, int amount, int temp);
    void setXF86Brightness(int scrBr, int temp);
    void setInitialGamma(bool set_previous);

    ~X11();
};

extern X11 x11;

#endif // X11_H
#endif
