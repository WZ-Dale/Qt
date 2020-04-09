#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QLabel>
#include <QCloseEvent>

#include "qwdialogsize.h"
#include "qwdialogheaders.h"
#include "qwdialoglocate.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setACellText(int row, int column, QString text);
    void setActLocateEnable(bool enable);
    void setDlgLocateNull();
    void closeEvent(QCloseEvent *event);

private:
    QLabel *LabCellPos;    //当前单元格行列号
    QLabel *LabCellText;    //当前单元格内容

    QStandardItemModel *theModel; //数据模型
    QItemSelectionModel *theSelection; //选择模型

    QWDialogHeaders *dlgSetHeaders=NULL;

    QWDialogLocate *dlgLocate=NULL;



private slots:
    //当前选择单元格发生变化
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    //设置表格行列数
    void on_actTab_SetSize_triggered();
    //设置表头标题
    void on_actTab_SetHeader_triggered();
    //定制单元格
    void on_actTab_Locate_triggered();
    //主窗口中操作对话框
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
