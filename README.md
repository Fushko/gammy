# Gammy
is a GUI tool for adjusting pixel brightness/temperature automatically or manually.

It can dim the screen if its content is too bright, or brighten it otherwise. This can help your eyes adjust when switching between dark and light windows, especially at night or in suboptimal lighting conditions.

Screenshots available on its [website](https://getgammy.com).

## Windows
#### Requirements
[Visual C++ 2017](https://aka.ms/vs/16/release/vc_redist.x64.exe)

#### Run
The latest Windows release can be found [here](https://getgammy.com/downloads.html) or [here](https://github.com/Fushko/gammy/releases).
Unpack and run it, no installation required.

### Important!
If the sliders don't work beyond a certain value, start the app in admin mode once, then restart the system. 

This disables a limit that Windows imposes on how much an app can change screen values.

## Linux (X11 only)
### Build
#### Requirements
- g++ or Clang compiler with C++17 support

- Ubuntu/Debian packages:
```
sudo apt install build-essential libgl1-mesa-dev libxxf86vm-dev qt5-default
```
#### Build and run
```
git clone https://github.com/Fushko/gammy.git
cd gammy
qmake Gammy.pro
make
./gammy
```
NOTE: If `make` fails with ```PlaceholderText is not a member of QPalette``` errors in ui_mainwindow.h, the Qt version provided by your distro is older than 5.12.
Updating Qt is recommended, but as a workaround you can delete the offending lines in ui_mainwindow.h, then run `make` again.

Additionally, the `qt5ct` plugin is recommended if you are running a DE/WM without Qt integration (e.g. GNOME):

```
sudo apt install qt5ct
```

### Packages

#### Arch
AUR packages are available:
- Stable: [`gammy`](https://aur.archlinux.org/packages/gammy/)
- Development: [`gammy-git`](https://aur.archlinux.org/packages/gammy-git/)

#### Gentoo

On Gentoo-based distros, Gammy is included in GURU Gentoo overlay.
```bash
# emerge the tool to enable the overlay
sudo emerge -av app-eselect/eselect-repository
# Setup the GURU overlay
sudo eselect repository enable guru
sudo emaint sync -r guru
# Finally emerge gammy
sudo emerge -av --autounmask x11-misc/gammy
```

## FreeBSD

On FreeBSD, Gammy can be installed from `ports`:

```sh
% cd /usr/ports
# update your ports branch to the latest, with your preferred method
% cd accessibility/gammy
% sudo make install-missing-packages
% sudo make package
% pkg install ./work/pkg/gammy*
```

or from `pkg`, as soon as [accessibility/gammy](https://www.freshports.org/accessibility/gammy) hits your (quarterly) repo:

```
% sudo pkg install -y gammy
```

## Usage
Gammy starts minimized in the system tray (or maximized if the tray is absent). Click on the icon to open the settings window.

-  (Linux only) The padlock icon allows the brightness range to go up to 200%.
- The "Range" slider determines the minimum and maximum brightness.
- The "Offset" slider adds to the screen brightness calculation. Higher = brighter image.
- Clicking on the first "..." button shows additional options related to adaptive brightness:
  - "Adaptation speed" controls how quickly the brightness adapts when a change is detected.
  - "Threshold" controls how much the screen has to change in order to trigger adaptation.
  - "Screenshot rate" determines the interval between each screenshot. Lowering this value detects brightness changes faster, but also results in higher CPU usage. Increasing this value on older PCs is recommended.
- "The second "..." button opens a window to control the time schedule for adaptive temperature, as well as the adaptation speed.

## Known issues and limitations
The brightness is adjusted by changing pixel values, instead of the LCD backlight. This has wildly varying results based on the quality of your screen.

Theoretically, this app looks best on OLEDs, since they don't have a backlight. (If you have one, I'd love to know your experience).

Backlight control is planned. However, controlling backlight via software is not supported by most screens.
### Multimonitor
On Windows, the brightness is detected and adjustable only on the monitor that is set as the primary screen. Temperature affects all screens, however.

On Linux, currently every screen is treated as one single screen when calculating brightness. Both brightness and temperature are changed globally. This will be fixed in the future.

## Troubleshooting
### Linux
If you are using a command to run it on startup, and the tray icon does not appear, try [this.](https://github.com/Fushko/gammy/issues/57#issuecomment-751358770)

If you are experiencing an "Invalid gamma ramp size" fatal error, refer to [this post.](https://github.com/Fushko/gammy/issues/20#issuecomment-584473270)

## Third party
- Qt 5 ([LGPL](https://doc.qt.io/qt-5/lgpl.html))
- Plog ([MPL](https://github.com/SergiusTheBest/plog/blob/master/LICENSE))
- JSON for Modern C++ ([MIT](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT))
- Qt-RangeSlider ([MIT](https://github.com/ThisIsClark/Qt-RangeSlider/blob/master/LICENSE))

## License
Copyright (C) Francesco Fusco.

[GPLv3](https://github.com/Fushko/gammy/blob/master/LICENSE)

