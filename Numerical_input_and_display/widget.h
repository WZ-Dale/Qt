#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_SliderRed_valueChanged(int value);
    void on_dial_valueChanged(int value);
    void on_radioBtnDec_clicked();
    void on_radioBtnBin_clicked();
    void on_radioBtnOct_clicked();
    void on_radioBtnHex_clicked();

    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
