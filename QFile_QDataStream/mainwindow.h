#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>     //很重要的头文件，不包含的话编译不报错，运行时报错

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //当前选择单元格发生变化
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actSave_triggered();

    void on_actOpen_triggered();

    void on_actSaveBin_triggered();

    void on_actOpenBin_triggered();

private:
    QLabel *LabCurFile;    //当前文件
    QLabel *LabCellPos;    //当前单元格行列号
    QLabel *LabCellText; //当前单元格内容
    //QWIntSpinDelegate intSpinDelegate; //整型数，代理组件
    //QWFloatSpinDelegate floatSpinDelegate; //浮点数，代理组件
    //QWComboBoxDelegate comboBoxDelegate; //列表选择，代理组件
    QStandardItemModel *theModel; //数据模型
    QItemSelectionModel *theSelection; //选择模型
    void resetTable (int aRowCount) ; //表格复位，设定行数 bool
    bool saveDataAsStream (QString& aFileName) ;//保存为 stm 文件 bool
    bool openDataAsStream (QString& aFileName) ;//打开 stm 文件
    bool saveBinaryFile (QString& aFileName) ; //保存为 dat 文件
    bool openBinaryFile (QString& aFileName) ; //打开 dat 文件

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
