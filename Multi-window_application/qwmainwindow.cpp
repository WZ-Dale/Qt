#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"


QWMainWindow::QWMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();//清除所有页面
    ui->tabWidget->setTabsClosable(true);//设置关闭按钮
    //ui->tabWidget->tabsClosable(); //Page有关闭按钮，可被关闭

    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
    this->setAutoFillBackground(true);
}

QWMainWindow::~QWMainWindow()
{
    delete ui;
}

void QWMainWindow::paintEvent(QPaintEvent *event)
{   //绘制窗口背景图片
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,ui->mainToolBar->height(),this->width(),this->height()-ui->mainToolBar->height()-ui->statusBar->height(),QPixmap("favicon3.ico"));
}

void QWMainWindow::on_actWidgetInsite_triggered()
{
    //创建QFormDoc窗体，并在tabWidget中显示
    QFormDoc *formDoc = new QFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    int cur=ui->tabWidget->addTab(formDoc,QString::asprintf("Doc %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void QWMainWindow::on_actWidget_triggered()
{
    QFormDoc *formDoc = new QFormDoc(); //不指定父窗口，用show()显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    formDoc->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");
    formDoc->setWindowFlag(Qt::Window,true);
    //formDoc->setWindowFlag(Qt::CustomizeWindowHint,true);
    //formDoc->setWindowFlag(Qt::WindowMinMaxButtonsHint,true);
    //formDoc->setWindowFlag(Qt::WindowCloseButtonHint,true);
    //formDoc->setWindowFlag(Qt::WindowStaysOnTopHint,true);
    //formDoc->setWindowState(Qt::WindowMaximized);
    formDoc->setWindowOpacity(0.9);
    //formDoc->setWindowModality(Qt::WindowModal);
    formDoc->show(); //在单独的窗口中显示
}


void QWMainWindow::on_actWindowInsite_triggered()
{
    QFormTable *formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    int cur=ui->tabWidget->addTab(formTable,QString::asprintf("Table %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void QWMainWindow::on_actWindow_triggered()
{
    QFormTable* formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("基于 QMainWindow 的窗口，指定父窗口，关闭时删除");
    formTable->show();
}

void QWMainWindow::on_tabWidget_tabCloseRequested(int index)
{   //关闭Tab
    if (index<0)
        return;
    QWidget* aForm=ui->tabWidget->widget(index);
    aForm->close();
}

void QWMainWindow::on_tabWidget_currentChanged(int index)
{
    bool en=ui->tabWidget->count()>0; //在无页面时，设置tab不可见
    ui->tabWidget->setVisible(en);
}
