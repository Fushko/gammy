/**
 * Copyright (C) Francesco Fusco. All rights reserved.
 * License: https://github.com/Fushko/gammy#license
 */

#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <cstdint>

int    calcBrightness(uint8_t *buf, uint64_t buf_sz, int bytes_per_pixel, int stride);
double lerp(double x, double a, double b);
double normalize(double x, double a, double b);
double remap(double x, double a, double b, double ay, double by);
double interpTemp(int step, size_t color_ch);
double easeOutExpo(double t, double b , double c, double d);
double easeInOutQuad(double t, double b, double c, double d);

bool alreadyRunning();

// Windows functions
void checkGammaRange();
void toggleRegkey(bool);

#endif // UTILS_H
