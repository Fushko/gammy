#ifndef TEMPSCHEDULER_H
#define TEMPSCHEDULER_H

#include <QDialog>
#include "utils.h"
#include "defs.h"
#include "gammactl.h"

namespace Ui {
class TempScheduler;
}

class TempScheduler : public QDialog
{
	Q_OBJECT

public:
	explicit TempScheduler(QWidget *parent = nullptr);
	explicit TempScheduler(QWidget *parent = nullptr, GammaCtl* gammactl = nullptr);
	~TempScheduler();

private slots:
	void on_buttonBox_accepted();

	void on_tempStartBox_valueChanged(int);

	void on_tempEndBox_valueChanged(int);

	void on_timeStartBox_timeChanged(const QTime &time);

	void on_timeEndBox_timeChanged(const QTime &time);

	void on_doubleSpinBox_valueChanged(double arg1);

private:
	Ui::TempScheduler *ui;

	int start_hr, start_min;
	int end_hr, end_min;

	int high_temp;
	int low_temp;
	double temp_speed_min;

	GammaCtl *gammactl;

	void setDates();
};

#endif // TEMPSCHEDULER_H
