#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool openTextByIODevice(const QString &aFileName);

    bool saveTextByIODevice(const QString &aFileName);


    bool openTextByStream(const QString &aFileName);

    bool saveTextByStream(const QString &aFileName);

private slots:
    void on_actOpen_IODevice_triggered();

    void on_actSave_IODevice_triggered();


    void on_actOpen_QTextStream_triggered();

    void on_actSave_QTextStream_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
