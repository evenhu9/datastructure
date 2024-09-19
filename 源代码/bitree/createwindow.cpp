#include "createwindow.h"
#include "ui_createwindow.h"
#include <QMessageBox>

#include<QDebug>

CreateWindow::CreateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateWindow)
{
    ui->setupUi(this);
    ui->label->setText("请输入先序遍历的二叉树字符串，用#表示空结点：");
    ui->createWindowLineEdit->setPlaceholderText("例:ABC##DE#G##F###");
    ui->createWindowLineEdit->setClearButtonEnabled(true);
    ui->createWindowLineEdit->setMaxLength(15);
    connect(ui->createBitreeWindowButton_OK,SIGNAL(clicked()),this,SLOT(createWindow_OKButton_clicked()));
}

CreateWindow::~CreateWindow()
{
    delete ui;
}

void CreateWindow::createWindow_OKButton_clicked()
{
    if(canFormBiTree()){
        createWindowTextEditString=ui->createWindowLineEdit->text();
        QMessageBox::information(this, "Success",tr(u8"创建成功"),QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, "Fail",tr(u8"创建失败"),QMessageBox::Ok);
    }
    this->close();
}

bool CreateWindow::canFormBiTree() {
    QString preorder=ui->createWindowLineEdit->text();
    if (preorder == "#"){
        return false;
    }
    int slot = 1; // 初始槽位数量为1（根节点占用一个槽位）

    for (int i=0; i< preorder.length();i++) {
        QChar ch=preorder[i];
        slot--; // 每访问一个节点占用一个槽位

        // 如果槽位数为负数，说明不可能构成二叉树
        if (slot < 0) {
            return false;
        }
        // 非空节点（如A, B, C等）提供两个新的槽位
        if (ch != '#') {
            slot += 2;
        }
    }
    // 如果所有槽位都刚好用完，说明可以构成二叉树
    return slot == 0;
}


void CreateWindow::on_createWindowLineEdit_textEdited()
{
    if(canFormBiTree()){
        ui->label->setText("字符串正确!");
    }
    else{
        ui->label->setText("字符串错误!");
    }
}

