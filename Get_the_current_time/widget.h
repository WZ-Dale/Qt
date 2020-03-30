#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    QTimer *fTimer; //定时器
    QTime fTimeCounter;//计时器
private slots:
    void on_timer_timeout () ; //定时溢出处理槽函数
private slots:
    void on_btnGetTime_clicked();

    void on_btnSetDateTime_clicked();

    void on_btnSetDate_clicked();

    void on_btnSetTime_clicked();

    void on_calendarWidget_selectionChanged();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnSetIntv_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H