#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //setCentralWidget(ui->splitter_2);
    QStringList theStrList; //保存初始 StringList
    theStrList<<"北京"<<"上海"<<"天津"<<"河北"<<"山东"<<"四川"<<"重庆"<<"广东"<<"河南"; //初始化 StringList
    theModel=new QStringListModel(this); //创建数据模型
    theModel->setStringList(theStrList); //为模型设置StringList，会导入StringList的内容
    ui->listView->setModel(theModel); //为listView设置数据模型
    //编辑项
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    //若要设置为不可编辑，则可以设置为：
    //ui->listView->setEditTriggers(QAbstractItemView:: NoEditTriggers);
}

Widget::~Widget()
{
    delete ui;
}

//添加项
void Widget::on_btnListAppend_clicked()
{   //添加一行
    theModel->insertRow(theModel->rowCount()); //在尾部插入一空行
    //QModelIndex  index;
    QModelIndex index=theModel->index(theModel->rowCount()-1,0);//获取最后一行
    theModel->setData(index,"new item",Qt::DisplayRole);//设置显示文字
    ui->listView->setCurrentIndex(index); //设置当前选中的行
}
//插入项
void Widget::on_btnListInsert_clicked()
{   //插入一行
    QModelIndex index=ui->listView->currentIndex(); //当前 modelIndex
    theModel->insertRow(index.row()); //在当前行的前面插入一行
    theModel->setData(index,"inserted item",Qt::DisplayRole); //设置显示文字
    theModel->setData(index,Qt::AlignRight,Qt::TextAlignmentRole); //设置对齐方式，不起作用
    ui->listView->setCurrentIndex(index); //设置当前选中的行
}
//删除当前项
void Widget::on_btnListDelete_clicked()
{   //删除当前行
    QModelIndex index=ui->listView->currentIndex(); //获取当前 modelIndex
    theModel->removeRow(index.row()); //删除当前行
}
//删除列表
void Widget::on_btnListClear_clicked()
{   //清除ListView的所有项
    theModel->removeRows(0,theModel->rowCount());
}
//显示数据模型的StringList
void Widget::on_btnTextImport_clicked()
{   //显示数据模型的StringList
    QStringList tmpList;
    tmpList=theModel->stringList();//获取数据模型的StringList
    ui->plainTextEdit->clear(); //文本框清空
    for (int i=0; i<tmpList.count();i++)
        ui->plainTextEdit->appendPlainText(tmpList.at(i)); //显示数据模型的StringList()返回的内容
}
//QListView的clicked()信号会传递一个QModellndex类型的参数，利用该参数显示当前项的模型索引的行和列的信息
void Widget::on_listView_clicked(const QModelIndex &index)
{   //显示QModelIndex的行、列号
    ui->LabInfo->setText(QString::asprintf("当前项:row=%d, column=%d", index.row(), index.column()));
}
//列表恢复
void Widget::on_btnListRestore_clicked()
{
    QStringList theStrList; //保存初始 StringList
    theStrList<<"北京"<<"上海"<<"天津"<<"河北"<<"山东"<<"四川"<<"重庆"<<"广东"<<"河南"; //初始化 StringList
    theModel->setStringList(theStrList); //为模型设置StringList，会导入StringList的内容
}
//清空文本
void Widget::on_cleanText_clicked()
{
    ui->plainTextEdit->clear();
}
