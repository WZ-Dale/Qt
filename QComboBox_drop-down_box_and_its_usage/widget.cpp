#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnIniItems_clicked()
{   //"初始化列表"按键
    QIcon icon;
    icon.addFile("C:\\Users\\WZ-Dale\\Documents\\Qt\\QComboBox_drop-down_box_and_its_usage\\aim.ico");
    ui->comboBox->clear(); //清除列表
    for (int i=0;i<20;i++)
        //ui->comboBox->addItem(icon, QString::asprintf("Item %d",i)); //带图标
        ui->comboBox->addItem(QString::asprintf("Item %d",i)); //不带图标
}

void Widget::on_btnIni2_clicked()
{   //初始化具有自定义数据的comboBox
    //QMap自动根据 key排序
    QMap<QString, int> City_Zone;
    City_Zone.insert("北京",10);
    City_Zone.insert("上海",21);
    City_Zone.insert("天津",22);
    City_Zone.insert("大连",411);
    City_Zone.insert("锦州",416);
    City_Zone.insert("徐州",516);
    City_Zone.insert("福州",591);
    City_Zone.insert("青岛",532);
    ui->comboBox_2->clear();
    foreach(const QString &str,City_Zone.keys())
        ui->comboBox_2->addItem(str,City_Zone.value(str));
}

void Widget::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString zone=ui->comboBox_2->currentData().toString();//项关联的数据
    ui->plainTextEdit->appendPlainText(arg1 + ":区号=" + zone);
}

void Widget::on_btnToComboBox_clicked()
{
    //plainTextEdit的内容逐行添加为comboBox的项
    QTextDocument* doc=ui->plainTextEdit->document () ; //文本对象
    int cnt=doc->blockCount () ;//回车符是一个 block
    QIcon icon("C:\\Users\\WZ-Dale\\Documents\\Qt\\QComboBox_drop-down_box_and_its_usage\\aim.ico");
    ui->comboBox->clear();
    for (int i=0; i<cnt;i++)
    {
        QTextBlock textLine=doc->findBlockByNumber(i); // 文本中的一段
        QString str=textLine.text();
        ui->comboBox->addItem(icon,str);
    }
}

void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    //创建并显示标准弹出式菜单
    QMenu* menu=ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}

void Widget::on_pushButton_5_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_pushButton_2_clicked()
{
    ui->comboBox->clear();
}

void Widget::on_checkBox_clicked(bool checked)
{
    ui->comboBox->setEnabled(checked);
}

void Widget::on_checkBox_2_clicked(bool checked)
{
    ui->plainTextEdit->setReadOnly(checked);
}
