#ifndef QFORMTABLE_H
#define QFORMTABLE_H

#include <QMainWindow>
#include <QMessageBox>


namespace Ui {
class QFormTable;
}

class QFormTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit QFormTable(QWidget *parent = 0);
    ~QFormTable();

private:
    Ui::QFormTable *ui;
};

#endif // QFORMTABLE_H
