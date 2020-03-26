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
// append
void Widget::on_pushButton_clicked()
{
    QString str1=ui->lineEdit->text();
    QString str2=ui->lineEdit_2->text();
    str1.append(str2);
    ui->lineEdit_3->setText(str1);
}
// prepend
void Widget::on_pushButton_2_clicked()
{
    QString str1=ui->lineEdit->text();
    QString str2=ui->lineEdit_2->text();
    str1.prepend(str2);
    ui->lineEdit_3->setText(str1);
}
// toUpper
void Widget::on_pushButton_3_clicked()
{
    QString str1=ui->lineEdit->text();
    str1=str1.toUpper();
    ui->lineEdit_3->setText(str1);
}
// toLower
void Widget::on_pushButton_4_clicked()
{
    QString str1=ui->lineEdit->text();
    str1=str1.toLower();
    ui->lineEdit_3->setText(str1);
}
// count
void Widget::on_pushButton_10_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.count());
    ui->lineEdit_3->setText(ret);
}
// size
void Widget::on_pushButton_11_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.size());
    ui->lineEdit_3->setText(ret);
}
// length
void Widget::on_pushButton_19_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.length());
    ui->lineEdit_3->setText(ret);
}
// trimmed
void Widget::on_pushButton_8_clicked()
{
    QString str1=ui->lineEdit->text();
    str1=str1.trimmed();
    ui->lineEdit_3->setText(str1);
}
// simplified
void Widget::on_pushButton_9_clicked()
{
    QString str1=ui->lineEdit->text();
    str1=str1.simplified();
    ui->lineEdit_3->setText(str1);
}
// indexOf
void Widget::on_pushButton_12_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.indexOf("5.9"));
    ui->lineEdit_3->setText(ret);
}
// lastIndexOf
void Widget::on_pushButton_13_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.lastIndexOf("\\"));
    ui->lineEdit_3->setText(ret);
}
// isNull
void Widget::on_pushButton_17_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.isNull());
    ui->lineEdit_3->setText(ret);
}
// isEmpty
void Widget::on_pushButton_18_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.isEmpty());
    ui->lineEdit_3->setText(ret);
}
// contains
void Widget::on_pushButton_16_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.contains(".cpp", Qt::CaseInsensitive));
    ui->lineEdit_3->setText(ret);
}
// startsWith
void Widget::on_pushButton_15_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.startsWith("g:", Qt::CaseInsensitive));
    ui->lineEdit_3->setText(ret);
}
// endsWith
void Widget::on_pushButton_14_clicked()
{
    QString str1=ui->lineEdit->text();
    QString ret=QString::number(str1.endsWith(".cpp", Qt::CaseInsensitive));
    ui->lineEdit_3->setText(ret);
}
// left
void Widget::on_pushButton_5_clicked()
{
    QString str1=ui->lineEdit->text();
    int N=str1.indexOf("Book");
    str1=str1.left(N) ;
    ui->lineEdit_3->setText(str1);
}
// right
void Widget::on_pushButton_6_clicked()
{
    QString str1=ui->lineEdit->text();
    int N=str1.lastIndexOf ("Book") ;
    str1=str1.right(str1.size()-N-4);
    ui->lineEdit_3->setText(str1);
}
// section
void Widget::on_pushButton_7_clicked()
{
    QString str1=ui->lineEdit->text();
    str1=str1.section("\\",1,2);
    ui->lineEdit_3->setText(str1);
}
