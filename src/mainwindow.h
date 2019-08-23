#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool quit;

    void updateBrLabel();
    void updatePollingSlider(int, int);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_minBrSlider_valueChanged(int val);
    void on_maxBrSlider_valueChanged(int val);
    void on_offsetSlider_valueChanged(int val);
    void on_speedSlider_valueChanged(int val);
    void on_tempSlider_valueChanged(int val);
    void on_thresholdSlider_valueChanged(int val);
    void on_pollingSlider_valueChanged(int val);

    void on_closeButton_clicked();
    void on_hideButton_clicked();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu {};
    QMenu* createMenu();

    QPoint mouse;
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    bool windowPressed = false;

    void closeEvent(QCloseEvent *);

    /*void mouseDoubleClickEvent(QMouseEvent*);
    **bool eventFilter(QObject *object, QEvent *event);*/
};

#endif // MAINWINDOW_H
