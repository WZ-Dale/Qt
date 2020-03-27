#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

//计算
void Widget::on_pushButton_clicked()
{
    int num=ui->spinNum->value();
    float price=ui->spinPrice->value();
    float total=num*price;
    ui->spinTotal->setValue(total);
}
//读取十进制数，转换为其他进制
void Widget::on_pushButton_2_clicked()
{
    int val=ui->spinDec->value();
    ui->spinBin->setValue(val);
    ui->spinHex->setValue(val);
}
//读取二进制数，转换为其他进制的数
void Widget::on_pushButton_3_clicked()
{
    int val=ui->spinBin->value();
    ui->spinDec->setValue(val);
    ui->spinHex->setValue(val);
}
//读取十六进制数，转换为其他进制
void Widget::on_pushButton_4_clicked()
{
    int val=ui->spinHex->value();
    ui->spinDec->setValue(val);
    ui->spinBin->setValue(val);
}
