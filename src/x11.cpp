#ifndef _WIN32
#include "x11.h"
#include "main.h"
#include <iostream>
#include <thread>
#include <X11/Xutil.h>
#include <cstring>
#include <X11/extensions/xf86vmode.h>

/*
 * This method takes a function that returns a resource,a function that deletes
 * the resource and arguments that are to be passed to the function that returns a
 * resource.
 *
 * example usecase of a function:
 *
 * auto woof = utility2::unique_rsc( ::fopen,::fclose,"/woof/foo/bar","r" ) ;
 */
template< typename Function,typename Deleter,typename ... Arguments >
static auto unique_rsc(Function&& function, Deleter&& deleter, Arguments&& ... args)
{
    using A = std::remove_pointer_t<std::result_of_t<Function(Arguments&&...)>>;
    using B = std::decay_t<Deleter>;
    return std::unique_ptr<A,B>(function(std::forward<Arguments>(args)...),std::forward<Deleter>(deleter));
}

X11::X11()
{
    #ifdef dbg
    std::cout << "Initializing X11... ";
    #endif

    //Seems to be the only thing needed to avoid a XIO fatal error so far.
    //More testing needed.
    XInitThreads();

    dsp = XOpenDisplay(nullptr);

    scr = DefaultScreenOfDisplay(dsp);
    scr_num = DefaultScreen(dsp);
    root = DefaultRootWindow(dsp);
    w = unsigned(scr->width);
    h = unsigned(scr->height);

    /**Query XF86Vidmode extension */
    {
        XInitExtension(dsp, "XF86VidMode");

        int ev_base, err_base;

        if (!XF86VidModeQueryExtension(dsp, &ev_base, &err_base))
        {
            #ifdef dbg
            std::cout << "Failed to query XF86VidMode extension.\n";
            #endif
            return;
        }

        int major_ver, minor_ver;
        if (!XF86VidModeQueryVersion(dsp, &major_ver, &minor_ver))
        {
            std::cout << "Failed to query XF86VidMode version.\n";
            return;
        }

        #ifdef dbg
        std::cout << "XF86 Major ver: " << major_ver << " Minor ver: " << minor_ver << "\n";
        #endif
   }

    /**Get initial gamma ramp and size */
    {
        if (!XF86VidModeGetGammaRampSize(dsp, scr_num, &ramp_sz))
        {
            #ifdef dbg
            std::cout << "Failed to get XF86 gamma ramp size.\n";
            #endif
            return;
        }

        init_ramp.resize(3 * size_t(ramp_sz) * sizeof(uint16_t));

        uint16_t* d = init_ramp.data();
        uint16_t* r = &d[0 * ramp_sz];
        uint16_t* g = &d[1 * ramp_sz];
        uint16_t* b = &d[2 * ramp_sz];

        if (!XF86VidModeGetGammaRamp(dsp, scr_num, ramp_sz, r, g, b))
        {
            #ifdef dbg
            std::cout << "Failed to get XF86 gamma ramp.\n";
            #endif
            return;
        }
    }
}

unsigned X11::getWidth() {
    return w;
}

unsigned X11::getHeight() {
    return h;
}

void X11::getX11Snapshot(uint8_t* buf)
{
    //XLockDisplay(dsp);
    XImage* img = XGetImage(dsp, root, 0, 0, w, h, AllPlanes, ZPixmap);
    //XUnlockDisplay(dsp);

    size_t len = size_t(img->bytes_per_line * img->height);
    memcpy(buf, img->data, len);
}

void X11::fillRamp(uint16_t*& ramp, int amount, int temp)
{
    uint16_t* r = &ramp[0 * ramp_sz];
    uint16_t* g = &ramp[1 * ramp_sz];
    uint16_t* b = &ramp[2 * ramp_sz];

    double slope = 1. * 32 / 255;

    double gdiv = 1.;
    double bdiv = 1.;
    double tval = temp;

    double output = slope * amount;

    if(temp > 1)
    {
        bdiv += (tval / 100);
        gdiv += (tval / 270);
    }

    for (uint16_t i = 0; i < ramp_sz; i++)
    {
        double val = i * output;

        r[i] = uint16_t(val);
        g[i] = uint16_t(val / gdiv);
        b[i] = uint16_t(val / bdiv);
    }
}

void X11::setXF86Brightness(int scrBr, int temp)
{
    if (scrBr > default_brightness) {
        return;
    }

    std::vector<uint16_t> ramp_v(3 * size_t(ramp_sz) * sizeof(uint16_t));

    uint16_t* ramp = ramp_v.data();
    fillRamp(ramp, scrBr, temp);

    bool r = XF86VidModeSetGammaRamp(dsp, 0, ramp_sz, &ramp[0*ramp_sz], &ramp[1*ramp_sz], &ramp[2*ramp_sz]);

#ifdef dbg
    if(!r)
    {
       std::cout << "setXF86Brightness failed.\n";
    }
#endif
}

void X11::setInitialGamma(bool set_previous)
{
#ifdef dbg
    std::cout << "Setting initial gamma\n";
#endif

    Display* d = XOpenDisplay(nullptr);

    if(set_previous)
    {
        //Sets the gamma to how it was before the program started
        XF86VidModeSetGammaRamp(d, scr_num, ramp_sz, &init_ramp[0*ramp_sz], &init_ramp[1*ramp_sz], &init_ramp[2*ramp_sz]);
    }
    else
    {
        X11::setXF86Brightness(default_brightness, 1);
    }
  
    XCloseDisplay(d);
}

X11::~X11()
{
    if(dsp) XCloseDisplay(dsp);
}

#endif
