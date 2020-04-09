#ifndef QWDIALOGHEADERS_H
#define QWDIALOGHEADERS_H

#include <QDialog>
#include <QStringListModel>
#include <QMessageBox>

namespace Ui {
class QWDialogHeaders;
}

class QWDialogHeaders : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogHeaders(QWidget *parent = 0);
    ~QWDialogHeaders();
    void setHeaderList(QStringList& headers);
    QStringList headerList();

private:
    QStringListModel  *model;

private:
    Ui::QWDialogHeaders *ui;
};

#endif // QWDIALOGHEADERS_H
