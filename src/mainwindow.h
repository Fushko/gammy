/**
 * Copyright (C) 2019 Francesco Fusco. All rights reserved.
 * License: https://github.com/Fushko/gammy#license
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHelpEvent>
#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class GammaCtl;
class ScreenCtl;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	explicit MainWindow(GammaCtl *gammactl);

	~MainWindow();

	bool prev_gamma = true;
	bool ignore_closeEvent  = true;

	void setTempSlider(int);
	void setBrtSlider(int);
	void updateBrLabel();
	void setPollingRange(int, int);
	void quit(bool prev_gamma);

private slots:
	void init();
	void iconActivated(QSystemTrayIcon::ActivationReason reason);

	void on_brRange_lowerValueChanged(int val);
	void on_brRange_upperValueChanged(int val);
	void on_offsetSlider_valueChanged(int val);
	void on_speedSlider_valueChanged(int val);
	void on_tempSlider_valueChanged(int val);
	void on_thresholdSlider_valueChanged(int val);
	void on_pollingSlider_valueChanged(int val);
	void on_manBrSlider_valueChanged(int value);
	void on_extendBr_clicked(bool checked);
	void on_autoCheck_toggled(bool checked);
	void on_autoTempCheck_toggled(bool checked);
	void on_pushButton_clicked();
	void on_tempSlider_sliderPressed();
	void on_advBrSettingsBtn_toggled(bool checked);
	void on_manBrSlider_sliderPressed();
	void wakeupSlot(bool);

private:
	Ui::MainWindow  *ui;
	QSystemTrayIcon *tray_icon;
	QMenu           *createMenu();
	GammaCtl        *gammactl;

	void toggleMainBrSliders(bool show);
	void toggleBrtSlidersRange(bool);
	void closeEvent(QCloseEvent *);
	bool listenWakeupSignal();
	void showOnTop();

	void checkTray();
	void createTrayIcon(QIcon &icon);
	bool systray_available = false;

	int wnd_offset_x = 17;
	int wnd_offset_y = 35;
	int wnd_height   = 300;

};

#endif // MAINWINDOW_H
