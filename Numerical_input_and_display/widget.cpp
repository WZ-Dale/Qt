#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout);
    QObject::connect(ui->SliderGreen,SIGNAL(valueChanged(int)), this,SLOT(on_SliderRed_valueChanged(int)));
    QObject::connect(ui->SliderBlue,SIGNAL(valueChanged(int)), this,SLOT(on_SliderRed_valueChanged(int)));
    QObject::connect(ui->SliderAlpha,SIGNAL(valueChanged(int)), this,SLOT(on_SliderRed_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_SliderRed_valueChanged(int value)
{
    //拖动Red、Green、Blue颜色滑动条时设置textEdit的底色
    Q_UNUSED(value);
    QColor color;
    int R=ui->SliderRed->value();
    int G=ui->SliderGreen->value();
    int B=ui->SliderBlue->value();
    int alpha=ui->SliderAlpha->value();
    color.setRgb (R, G, B, alpha) ; //使用 QColor 的 setRgb ()函数获得颜色
    QPalette pal=ui->textEdit->palette();
    pal.setColor (QPalette::Base, color) ; //设置底色
    ui->textEdit->setPalette (pal);
}
void Widget::on_dial_valueChanged(int value)
{
    //设置LCD的显示值等于Dial的值
    ui->LCDDisplay->display(value);
}
void Widget::on_radioBtnDec_clicked()
{
    //设置LCD显示十进制数
    ui->LCDDisplay->setDigitCount(3) ; //设置位数 ui->LCDDisplay->setDecMode();
}
void Widget::on_radioBtnBin_clicked()
{
    //设置LCD显示二进制数
    ui->LCDDisplay->setDigitCount(8);
    ui->LCDDisplay->setBinMode();
}
void Widget::on_radioBtnOct_clicked()
{
    //设置LCD显示八进制数
    ui->LCDDisplay->setDigitCount(4);
    ui->LCDDisplay->setOctMode();
}
void Widget::on_radioBtnHex_clicked()
{
    //设置LCD显示十六进制数
    ui->LCDDisplay->setDigitCount(3);
    ui->LCDDisplay->setHexMode();
}

void Widget::on_horizontalScrollBar_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}
