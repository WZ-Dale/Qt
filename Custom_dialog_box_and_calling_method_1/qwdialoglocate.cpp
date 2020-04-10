#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"

//#include "mainwindow.h"

QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    QMessageBox::information(this,"提示","定制单元格对话框被删除");
    delete ui;
}


//void QWDialogLocate::on_btnSetText_clicked()
//{   //定位到单元格，并设置字符串
//    int row=ui->spinBoxRow->value(); //行号
//    int col=ui->spinBoxColumn->value();//列号
//    MainWindow *parWind = (MainWindow*)parentWidget(); //获取主窗口
//    parWind->setACellText(row,col,ui->edtCaption->text()); //设置单元格文字
//    if (ui->chkBoxRow->isChecked()) //行增
//        ui->spinBoxRow->setValue(1+ui->spinBoxRow->value());
//    if (ui->chkBoxColumn->isChecked()) //列增
//        ui->spinBoxColumn->setValue(1+ui->spinBoxColumn->value());
//}
void QWDialogLocate::on_btnSetText_clicked()
{   //发射信号，定位到单元格并运置字符串
    int row=ui->spinBoxRow->value() ; //行号
    int col=ui->spinBoxColumn->value() ;//列号
    QString text=ui->edtCaption->text() ;//文字
    emit changeCellText (row, col, text) ; //发射信号
    if (ui->chkBoxRow->isChecked ()) //行增
        ui->spinBoxRow->setValue(1+ui->spinBoxRow->value());
    if (ui->chkBoxColumn->isChecked()) //列增
        ui->spinBoxColumn->setValue(1+ui->spinBoxColumn->value());
}

void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{   //设置SpinBox范围
    ui->spinBoxRow->setMinimum(0);
    ui->spinBoxColumn->setMinimum(0);
    ui->spinBoxRow->setMaximum(rowCount-1);
    ui->spinBoxColumn->setMaximum(colCount-1);
}
void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{   //设置SpinBox初始数值
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}

//void QWDialogLocate::closeEvent(QCloseEvent *event)
//{
//    //窗口关闭事件，关闭时释放本窗口
//    MainWindow *parWind = (MainWindow*)parentWidget(); //获取父窗口指针
//    parWind->setActLocateEnable(true);//使能 actTab_Locate
//    parWind->setDlgLocateNull(); //将窗口指针设置为NULL
//}
//void QWDialogLocate::closeEvent(QCloseEvent *event)
//{
//    //窗口关闭时询问是否退出
//    QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确定要退出本对话框吗？",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,QMessageBox::No);
//    if (result==QMessageBox::Yes){
//        event->accept();

//        //窗口关闭事件，关闭时释放本窗口
//        MainWindow *parWind = (MainWindow*)parentWidget(); //获取父窗口指针
//        parWind->setActLocateEnable(true);//使能 actTab_Locate
//        parWind->setDlgLocateNull(); //将窗口指针设置为NULL
//    }
//    else
//        event->ignore();
//}
void QWDialogLocate::closeEvent(QCloseEvent *event)
{   //窗口关闭事件，发射信号使actTab_Locate能用
    emit changeActionEnable(true);
}
void QWDialogLocate::showEvent(QShowEvent *event)
{   //窗口显示事件，发射信号使actTab_Locate不能用
    emit changeActionEnable(false);
}

