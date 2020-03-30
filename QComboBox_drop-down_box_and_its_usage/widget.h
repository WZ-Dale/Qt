#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBlock>
#include <QMenu>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnIniItems_clicked();

    void on_btnIni2_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_btnToComboBox_clicked();

    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
