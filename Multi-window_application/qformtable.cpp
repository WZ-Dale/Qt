#include "qformtable.h"
#include "ui_qformtable.h"

QFormTable::QFormTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFormTable)
{
    ui->setupUi(this);
}

QFormTable::~QFormTable()
{
    QMessageBox::information(this, "消息","FormTable 窗口被删除和释放");
    delete ui;
}
