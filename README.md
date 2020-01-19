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

### Linux/X11

#### Requirements

##### sudo apt install (or other package manager equivalent): 
- git 
- build-essential 
- libgl1-mesa-dev 
- qt5-default

In a single command:
```
sudo apt install git build-essential libgl1-mesa-dev qt5-default
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

## Usage

Gammy starts minimized in the system tray (or maximized if the tray is absent). Click on the icon open the settings window. 

Unticking the "Auto" checkbox allows manual brightness adjustment.

The padlock button next to "Max brightness" can extend the brightness range to a max. of 200%. (Linux only)

Color temperature can be set manually, or handled automatically based on a time period. The latter can be set by clicking on the '...' button, next to the second 'Auto' checkbox.

Dragging the bottom of the window will reveal additional settings:

- "Adaption speed" controls how quickly the brightness adapts when a change is detected.
- "Threshold" controls how much the screen has to change in order to trigger adaptation.
- "Screenshot rate" determines the interval between each screenshot. Lowering this value detects brightness changes faster, but also results in higher CPU usage. Increasing this value on older PCs is recommended.

## Third party

- Qt 5 ([LGPL](https://doc.qt.io/qt-5/lgpl.html))
- Plog ([MPL](https://github.com/SergiusTheBest/plog/blob/master/LICENSE))
- JSON for Modern C++ ([MIT](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT))

## License

[GPLv3](https://github.com/Fushko/gammy/blob/master/LICENSE)
