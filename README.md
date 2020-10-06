# Gammy
is a GUI tool for adjusting pixel brightness/temperature automatically or manually.

It can dim the screen if its content is too bright, or brighten it otherwise. This can help your eyes adjust when switching between dark and light windows, especially at night or in suboptimal lighting conditions.

Screenshots available on its [website](https://getgammy.com).
## Installation

### Windows
#### Requirements
[Visual C++ 2017](https://aka.ms/vs/16/release/vc_redist.x64.exe)

#### Run
The latest Windows release can be found [here](https://getgammy.com/downloads.html). Unpack and run it, no installation required.

### Linux
#### Requirements
- X11
- g++ compiler with C++17 support
##### Packages

- git
- build-essential 
- libgl1-mesa-dev
- qt5-default (5.12+)

On Debian-based distros:
```
sudo apt install git build-essential libgl1-mesa-dev qt5-default libxxf86vm-dev
```

Additionally, the "qt5ct" plugin is recommended if you are running a DE/WM without Qt integration (e.g. GNOME):

```
sudo apt install qt5ct
```

#### Build and run
```
git clone https://github.com/Fushko/gammy.git
cd gammy
qmake Gammy.pro
make
./gammy
```
NOTE: If make fails with ```PlaceholderText is not a member of QPalette``` errors in ui_mainwindow.h, your Qt version is older than 5.12.
Updating Qt is recommended, but as a workaround you can delete the offending lines in ui_mainwindow.h, then run make again.

#### Gentoo

On Gentoo-based distros:
```bash
# Gammy is included in GURU Gentoo overlay, so let's emerge the tool to enable the overlay
sudo emerge -av app-eselect/eselect-repository
# Setup the GURU overlay
sudo eselect repository enable guru
sudo emaint sync -r guru
# Finally emerge gammy
sudo emerge -av --autounmask x11-misc/gammy
```

## Usage
Gammy starts minimized in the system tray (or maximized if the tray is absent). Click on the icon to open the settings window. 

- The padlock icon allows the brightness range to go up to 200%. (Linux only)
- The "Range" slider determines the minimum and maximum brightness.
- The "Offset" slider adds to the screen brightness calculation. Higher = brighter image.
- Clicking on the first "..." button shows additional options related to adaptive brightness:
  - "Adaptation speed" controls how quickly the brightness adapts when a change is detected.
  - "Threshold" controls how much the screen has to change in order to trigger adaptation.
  - "Screenshot rate" determines the interval between each screenshot. Lowering this value detects brightness changes faster, but also results in higher CPU usage. Increasing this value on older PCs is recommended.
- "The second "..." button opens a window to control the time schedule for adaptive temperature, as well as the adaptation speed.

## Troubleshooting
If you are experiencing an "Invalid gamma ramp size" fatal error, refer to [this post.](https://github.com/Fushko/gammy/issues/20#issuecomment-584473270)

## Third party
- Qt 5 ([LGPL](https://doc.qt.io/qt-5/lgpl.html))
- Plog ([MPL](https://github.com/SergiusTheBest/plog/blob/master/LICENSE))
- JSON for Modern C++ ([MIT](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT))
- Qt-RangeSlider ([MIT](https://github.com/ThisIsClark/Qt-RangeSlider/blob/master/LICENSE))

## License
Copyright (C) Francesco Fusco.

[GPLv3](https://github.com/Fushko/gammy/blob/master/LICENSE)
