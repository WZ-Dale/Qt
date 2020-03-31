#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);//使splitter填充满整个工作区
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actListlni_triggered()
{   //初始化项
    QListWidgetItem *aItem; //每一行是一个QListWidgetItem
    QIcon aIcon;
    aIcon.addFile("favicon0.ico"); //设置ICON的图标
    bool chk=ui->chkBoxListEditable->isChecked();//是否可编辑
    ui->listWidget->clear(); //清除项
    for (int i=0; i<10; i++)
    {
        QString str=QString::asprintf("Item %d",i);
        aItem=new QListWidgetItem(); //新建一个项
        aItem->setText(str); //设置文字标签
        aItem->setIcon(aIcon);//设置图标
        aItem->setCheckState(Qt::Checked); //设置为选中状态
        if (chk) //可编辑, 设置flags
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        else//不可编辑, 设置flags
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        ui->listWidget->addItem(aItem); //增加一个项
    }
}

void MainWindow::on_actListlnsert_triggered()
{   //插入一个项
    QIcon aIcon;
    aIcon.addFile("favicon1.ico"); //图标
    bool chk=ui->chkBoxListEditable->isChecked();
    QListWidgetItem* aItem=new QListWidgetItem("New Inserted Item"); //创建一个项
    aItem->setIcon(aIcon);//设置图标
    aItem->setCheckState(Qt::Checked); //设置为checked
    if (chk) //设置标记
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->listWidget->insertItem(ui->listWidget->currentRow(),aItem); //在当前行的上方插入一个项
}

void MainWindow::on_actListDelete_triggered()
{   //删除当前项
    int row=ui->listWidget->currentRow();//当前行
    QListWidgetItem* aItem=ui->listWidget->takeItem(row); //移除指定行的项，但不delete
    delete aItem; //需要手工删除对象
}

void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}

void MainWindow::on_actSelALL_triggered()
{   //项全选
    //QListWidgetItem *aItem; //项对象
    int cnt=ui->listWidget->count();//项个数
    for (int i=0; i<cnt; i++)
    {
        QListWidgetItem *aItem=ui->listWidget->item(i);//获取一个项
        aItem->setCheckState(Qt::Checked);//设置为选中
    }
}

void MainWindow::on_actSelNone_triggered()
{   //项全不选
    //QListWidgetItem *aItem; //项对象
    int cnt=ui->listWidget->count();//项个数
    for (int i=0; i<cnt; i++)
    {
        QListWidgetItem *aItem=ui->listWidget->item(i);//获取一个项
        aItem->setCheckState(Qt::Unchecked);//设置为不选中
    }
}

void MainWindow::on_actSelInvs_triggered()
{   //反选
    //QListWidgetItem *aItem; //项对象
    int cnt=ui->listWidget->count();//项个数
    for (int i=0; i<cnt; i++)
    {
        QListWidgetItem *aItem=ui->listWidget->item(i);//获取一个项
        if(aItem->checkState())
            aItem->setCheckState(Qt::Unchecked);//设置为不选中
        else
            aItem->setCheckState(Qt::Checked);//设置为不选中
    }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{   //listWidget当前选中项发生变化
    QString str;
    if (current != NULL) //需要检测变量指针是否为空
    {
        if (previous==NULL)  //需要检测变量指针是否为空
            str="当前："+current->text();
        else
            str="前一项："+previous->text()+"; 当前项："+current->text();
        ui->editCutItemText->setText(str);
    }
}
