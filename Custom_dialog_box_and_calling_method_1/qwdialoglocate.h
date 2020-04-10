#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = 0);
    ~QWDialogLocate();
    void setSpinRange(int rowCount, int colCount); //设置最大值
    //void setSpinValue(int rowNo, int colNo);//设置初始值


public slots:
    void setSpinValue(int rowNo, int colNo);
signals:
    void changeCellText(int row, int column, QString &text);
    void changeActionEnable(bool en);


private:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

private slots:
    void on_btnSetText_clicked();

private:
    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE_H
