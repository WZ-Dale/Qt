#include "mainwindow.h"
#include "ui_mainwindow.h"

#define FixedColumnCount 6    //文件固定 6 列

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(3, FixedColumnCount, this) ; //数据模型
    theSelection = new QItemSelectionModel (theModel) ;//选择模型
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)), this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(theModel) ; //设置数据模型
    ui->tableView->setSelectionModel(theSelection) ; //设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    //创建状态栏组件
    QStatusBar* bar = ui->statusBar; //获取状态栏
    LabCurFile = new QLabel; //新建标签
    LabCellPos = new QLabel;
    LabCellText = new QLabel;
    LabCurFile->setText("当前文件：");
    LabCellPos->setText("当前单元格：");
    LabCellText->setText("单元格内容：");
    bar->addWidget(LabCurFile);
    LabCurFile->setFrameShadow(QFrame::Sunken); //设置标签阴影
    bar->addWidget(LabCellPos);
    LabCellPos->setFrameShadow(QFrame::Sunken); //设置标签阴影
    bar->addWidget(LabCellText);
    LabCellPos->setFrameShadow(QFrame::Sunken); //设置标签阴影
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{   //选择单元格变化时的响应
    if (current.isValid())
    {
        LabCellPos->setText(QString::asprintf("当前单元格： %d 行， %d 列", current.row(),current.column()));
        QStandardItem* aItem=theModel->itemFromIndex(current);
        LabCellText->setText("单元格内容："+aItem->text());
    }
}

void MainWindow::on_actSave_triggered()
{   //以Qt预定义编码保存数据文件
    QString curPath=QDir::currentPath();
    QString aFileName=QFileDialog::getSaveFileName(this,tr("选择保存文件"),curPath,"Qt预定义编码数据文件(*.stm)");
    if (aFileName.isEmpty())
        return;
    if (saveDataAsStream(aFileName)) //保存为流数据文件
       QMessageBox::information(this,"提示消息","文件已经成功保存!");
}
bool MainWindow::saveDataAsStream(QString &aFileName)
{   //将模型数据保存为Qt预定义编码的数据文件
    QFile aFile(aFileName);  //以文件方式读出
    if (!(aFile.open(QIODevice::WriteOnly | QIODevice::Truncate)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_9); //设置版本号，写入和读取的版本号要兼容
    qint16 rowCount=theModel->rowCount(); //数据模型行数
    qint16 colCount=theModel->columnCount(); //数据模型列数
    aStream<<rowCount; //写入文件流，行数
    aStream<<colCount;//写入文件流，列数
    //获取表头文字
    for (int i=0;i<theModel->columnCount();i++)
    {
        QString str=theModel->horizontalHeaderItem(i)->text();//获取表头文字
        aStream<<str; //字符串写入文件流，Qt预定义编码方式
    }
    //获取数据区的数据
    for (int i=0;i<theModel->rowCount();i++)
    {
        QStandardItem* aItem=theModel->item(i,0); //测深
        qint16 ceShen=aItem->data(Qt::DisplayRole).toInt();
        aStream<<ceShen;// 写入文件流，qint16
        aItem=theModel->item(i,1); //垂深
        qreal chuiShen=aItem->data(Qt::DisplayRole).toFloat();
        aStream<<chuiShen;//写入文件流， qreal
        aItem=theModel->item(i,2); //方位
        qreal fangWei=aItem->data(Qt::DisplayRole).toFloat();
        aStream<<fangWei;//写入文件流， qreal
        aItem=theModel->item(i,3); //位移
        qreal weiYi=aItem->data(Qt::DisplayRole).toFloat();
        aStream<<weiYi;//写入文件流， qreal
        aItem=theModel->item(i,4); //固井质量
        QString zhiLiang=aItem->data(Qt::DisplayRole).toString();
        aStream<<zhiLiang;// 写入文件流，字符串
        aItem=theModel->item(i,5); //测井
        bool quYang=(aItem->checkState()==Qt::Checked);
        aStream<<quYang;// 写入文件流，bool型
    }
    aFile.close();
    return true;
}

void MainWindow::on_actOpen_triggered()
{
    QString curPath=QDir::currentPath();
    //调用打开文件对话框打开一个文件
    QString aFileName=QFileDialog::getOpenFileName(this,tr("打开一个文件"),curPath,"流数据文件(*.stm)");
    if (aFileName.isEmpty())
        return; //
    if  (openDataAsStream(aFileName)) //保存为流数据文件
         QMessageBox::information(this,"提示消息","文件已经打开!");
}
bool MainWindow::openDataAsStream(QString &aFileName)
{   //从Qt预定义流文件读入数据
    QFile aFile(aFileName);  //以文件方式读出
    if (!(aFile.open(QIODevice::ReadOnly)))
        return false;
    QDataStream aStream(&aFile); //用文本流读取文件
    aStream.setVersion(QDataStream::Qt_5_9); //设置流文件版本号
    qint16 rowCount,colCount;
    aStream>>rowCount; //读取行数
    aStream>>colCount; //列数
    this->resetTable(rowCount); //表格复位
    //获取表头文字
    QString str;
    for (int i=0;i<colCount;i++)
        aStream>>str;  //读取表头字符串
    //获取数据区文字，
    qint16  ceShen;
    qreal  chuiShen;
    qreal  fangWei;
    qreal  weiYi;
    QString  zhiLiang;
    bool    quYang;
    QStandardItem   *aItem;
    QModelIndex index;
    for (int i=0;i<rowCount;i++)
    {
        aStream>>ceShen;//读取测深, qint16
        index=theModel->index(i,0);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(ceShen,Qt::DisplayRole);
        aStream>>chuiShen;//垂深,qreal
        index=theModel->index(i,1);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(chuiShen,Qt::DisplayRole);
        aStream>>fangWei;//方位,qreal
        index=theModel->index(i,2);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(fangWei,Qt::DisplayRole);
        aStream>>weiYi;//位移,qreal
        index=theModel->index(i,3);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(weiYi,Qt::DisplayRole);
        aStream>>zhiLiang;//固井质量,QString
        index=theModel->index(i,4);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(zhiLiang,Qt::DisplayRole);
        aStream>>quYang;//bool
        index=theModel->index(i,5);
        aItem=theModel->itemFromIndex(index);
        if (quYang)
            aItem->setCheckState(Qt::Checked);
        else
            aItem->setCheckState(Qt::Unchecked);
    }
    aFile.close();
    return true;
}
void MainWindow::resetTable(int aRowCount)
{   //表格复位，先删除所有行，再设置新的行数，表头不变
    theModel->removeRows(0,theModel->rowCount()); //删除所有行
    theModel->setRowCount(aRowCount);//设置新的行数
    QString str=theModel->headerData(theModel->columnCount()-1,Qt::Horizontal,Qt::DisplayRole).toString();
    for (int i=0;i<theModel->rowCount();i++)
    { //设置最后一列
        QModelIndex index=theModel->index(i,FixedColumnCount-1); //获取模型索引
        QStandardItem* aItem=theModel->itemFromIndex(index); //获取item
        aItem->setCheckable(true);
        aItem->setData(str,Qt::DisplayRole);
        aItem->setEditable(false); //不可编辑
    }
}





void MainWindow::on_actSaveBin_triggered()
{   //保存二进制文件
    QString curPath=QDir::currentPath();
    //调用打开文件对话框选择一个文件
    QString aFileName=QFileDialog::getSaveFileName(this,tr("选择保存文件"),curPath,"二进制数据文件(*.dat)");
    if (aFileName.isEmpty())
        return;
    if  (saveBinaryFile(aFileName)) //保存为流数据文件
        QMessageBox::information(this,"提示消息","文件已经成功保存!");
}
bool MainWindow::saveBinaryFile(QString &aFileName)
{   //保存为纯二进制文件
    QFile aFile(aFileName);  //以文件方式读出
    if (!(aFile.open(QIODevice::WriteOnly)))
        return false;
    QDataStream aStream(&aFile); //用文本流读取文件
    aStream.setByteOrder(QDataStream::LittleEndian);//windows平台
    qint16  rowCount=theModel->rowCount();
    qint16  colCount=theModel->columnCount();
    aStream.writeRawData((char *)&rowCount,sizeof(qint16)); //写入文件流
    aStream.writeRawData((char *)&colCount,sizeof(qint16));//写入文件流
    //获取表头文字
    // QString str;
    QByteArray btArray;
    QStandardItem *aItem;
    for (int i=0;i<theModel->columnCount();i++)
    {
        aItem=theModel->horizontalHeaderItem(i); //获取表头item
        QString str=aItem->text(); //获取表头文字
        btArray=str.toUtf8(); //转换为字符数组
        aStream.writeBytes(btArray,btArray.length()); //写入文件流,长度uint型，然后是字符串内容
    }
    //获取数据区文字
    qint8   yes=1,no=0; //分别代表逻辑值 true和false
    for (int i=0;i<theModel->rowCount();i++)
    {
        aItem=theModel->item(i,0); //测深
        qint16 ceShen=aItem->data(Qt::DisplayRole).toInt();//qint16类型
        aStream.writeRawData((char *)&ceShen,sizeof(qint16));//写入文件流
        aItem=theModel->item(i,1); //垂深
        qreal chuiShen=aItem->data(Qt::DisplayRole).toFloat();//qreal 类型
        aStream.writeRawData((char *)&chuiShen,sizeof(qreal));//写入文件流
        aItem=theModel->item(i,2); //方位
        qreal fangWei=aItem->data(Qt::DisplayRole).toFloat();
        aStream.writeRawData((char *)&fangWei,sizeof(qreal));
        aItem=theModel->item(i,3); //位移
        qreal weiYi=aItem->data(Qt::DisplayRole).toFloat();
        aStream.writeRawData((char *)&weiYi,sizeof(qreal));
        aItem=theModel->item(i,4); //固井质量
        QString zhiLiang=aItem->data(Qt::DisplayRole).toString();
        btArray=zhiLiang.toUtf8();
        aStream.writeBytes(btArray,btArray.length());
        aItem=theModel->item(i,5); //测井取样
        bool quYang=(aItem->checkState()==Qt::Checked); //true or false
        if (quYang)
            aStream.writeRawData((char *)&yes,sizeof(qint8));
        else
            aStream.writeRawData((char *)&no,sizeof(qint8));
    }
    aFile.close();
    return true;
}

void MainWindow::on_actOpenBin_triggered()
{
    QString curPath=QDir::currentPath();
    //调用打开文件对话框打开一个文件
    QString aFileName=QFileDialog::getOpenFileName(this,tr("打开一个文件"),curPath,"二进制数据文件(*.dat)");
    if (aFileName.isEmpty())
        return; //
    if  (openBinaryFile(aFileName)) //保存为流数据文件
         QMessageBox::information(this,"提示消息","文件已经打开!");
}
bool MainWindow::openBinaryFile(QString &aFileName)
{//打开二进制文件
    QFile aFile(aFileName);  //以文件方式读出
    if (!(aFile.open(QIODevice::ReadOnly)))
        return false;
    QDataStream aStream(&aFile); //用文本流读取文件
    aStream.setByteOrder(QDataStream::LittleEndian);
    qint16  rowCount,colCount;
    aStream.readRawData((char *)&rowCount, sizeof(qint16));
    aStream.readRawData((char *)&colCount, sizeof(qint16));
    this->resetTable(rowCount);
    //获取表头文字,但是并不利用
    char *buf;
    uint strLen;  //也就是 quint32
    for (int i=0;i<colCount;i++)
    {
        aStream.readBytes(buf,strLen);//同时读取字符串长度，和字符串内容
        QString str=QString::fromLocal8Bit(buf,strLen); //可处理汉字
    }
    //获取数据区数据
    QStandardItem   *aItem;
    qint16  ceShen;
    qreal  chuiShen;
    qreal  fangWei;
    qreal  weiYi;
    QString  zhiLiang;
    qint8   quYang; //分别代表逻辑值 true和false
    QModelIndex index;
    for (int i=0;i<rowCount;i++)
    {
        aStream.readRawData((char *)&ceShen, sizeof(qint16)); //测深
        index=theModel->index(i,0);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(ceShen,Qt::DisplayRole);
        aStream.readRawData((char *)&chuiShen, sizeof(qreal)); //垂深
        index=theModel->index(i,1);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(chuiShen,Qt::DisplayRole);
        aStream.readRawData((char *)&fangWei, sizeof(qreal)); //方位
        index=theModel->index(i,2);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(fangWei,Qt::DisplayRole);
        aStream.readRawData((char *)&weiYi, sizeof(qreal)); //位移
        index=theModel->index(i,3);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(weiYi,Qt::DisplayRole);
        aStream.readBytes(buf,strLen);//固井质量
        zhiLiang=QString::fromLocal8Bit(buf,strLen);
        index=theModel->index(i,4);
        aItem=theModel->itemFromIndex(index);
        aItem->setData(zhiLiang,Qt::DisplayRole);
        aStream.readRawData((char *)&quYang, sizeof(qint8)); //测井取样
        index=theModel->index(i,5);
        aItem=theModel->itemFromIndex(index);
        if (quYang==1)
            aItem->setCheckState(Qt::Checked);
        else
            aItem->setCheckState(Qt::Unchecked);
    }
    aFile.close();
    return true;
}

