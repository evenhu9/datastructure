#include "bitreemainwindow.h"
#include "ui_bitreemainwindow.h"

#include<QDebug>

BitreeMainWindow::BitreeMainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::BitreeMainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);

    QMenuBar *pMenuBar = menuBar();

    //工具栏创建
    menuBarHelp= new QMenu(QStringLiteral("Help(Alt+&H)"));
    //工具栏菜单创建/
    actionHelpOpen = new QAction(QStringLiteral("About"), this);
    actionHelpOpen->setShortcut(Qt::CTRL | Qt::Key_A);
    menuBarHelp->addAction(actionHelpOpen);
    //将菜单添加至工具栏按钮
    pMenuBar->addMenu(menuBarHelp);

    tree.root=nullptr;
    connect(ui->createBitreeButton,SIGNAL(clicked()),this,SLOT(createWindowButton_clicked()));
    connect(ui->bitreeLeafCountButton,SIGNAL(clicked()),this,SLOT(on_bitreeLeafCountButton_clicked()));
    connect(ui->bitreeDisplayButton,SIGNAL(clicked()),this,SLOT(bitreeDisplayButton_clicked()));
    connect(actionHelpOpen,SIGNAL(triggered()),this,SLOT(actionHelpButton_clicked()));
}

BitreeMainWindow::~BitreeMainWindow()
{
    delete ui;
}

void BitreeMainWindow::createWindowButton_clicked()
{
    CreateWindow *form=new CreateWindow(this);
    form->exec();
    biTreeString=form->createWindowTextEditString;

    if((!biTreeString.isEmpty()))//biTreeString非空时
    {
        tree.root=tree.createBiTree(biTreeString);
        tree.preOrder(tree.root);
        tree.inOrder(tree.root);
        tree.postOrder(tree.root);
        tree.leafNum=tree.Leaves(tree.root);
        tree.ifhave=TRUE;
    }
}

void BitreeMainWindow::bitreeDisplayButton_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    Paint *form=new Paint();

    form->setBiTree(&tree);
    form->show();
}

void BitreeMainWindow:: actionHelpButton_clicked()
{
    QString helpString=QStringLiteral("Author:EvenHu\nID:2252552");
    QMessageBox::information(nullptr, tr(u8"About"),helpString,QMessageBox::Ok);
}

void BitreeMainWindow::on_bitreeLeafCountButton_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    QString result="叶子数为"+QString::number(tree.leafNum);
    QMessageBox::information(nullptr, tr(u8"统计叶子数"),result,QMessageBox::Ok);
    return;
}


void BitreeMainWindow::on_preButton_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    QString result="先序遍历为"+tree.preString;
    QMessageBox::information(nullptr, tr(u8"先序遍历"),result,QMessageBox::Ok);
}


void BitreeMainWindow::on_inButton_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    QString result="中序遍历为"+tree.inString;
    QMessageBox::information(nullptr, tr(u8"中序遍历"),result,QMessageBox::Ok);
}


void BitreeMainWindow::on_postButton_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    QString result="后序遍历为"+tree.postString;
    QMessageBox::information(nullptr, tr(u8"后序遍历"),result,QMessageBox::Ok);
}


void BitreeMainWindow::on_prethreadButton_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    if(tree.ifThread){
        tree.cleanThread(tree.root);
    }
    tree.preOrderThreading(tree.root);
    QMessageBox::information(this, "Success",tr(u8"完成线索化"),QMessageBox::Ok);
}


void BitreeMainWindow::on_inthreadButton_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    if(tree.ifThread){
        tree.cleanThread(tree.root);
    }
    tree.inOrderThreading(tree.root);
    QMessageBox::information(this, "Success",tr(u8"完成线索化"),QMessageBox::Ok);
}


void BitreeMainWindow::on_posthreadButton_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    if(tree.ifThread){
        tree.cleanThread(tree.root);
    }
    tree.postOrderThreading(tree.root);
    QMessageBox::information(this, "Success",tr(u8"完成线索化"),QMessageBox::Ok);
}


void BitreeMainWindow::on_preButton_2_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    if(tree.ThreadType!=1){
        QMessageBox::warning(nullptr, "警告","未先序线索化！",QMessageBox::Ok);
        return;
    }
    QString pre;
    for (BiTNode* p = tree.root; p != NULL; p = tree.NextNode2(p)){
        pre+=p->data;
    }
    QString result="先序遍历为"+pre;
    QMessageBox::information(this, "先序遍历",result,QMessageBox::Ok);
}


void BitreeMainWindow::on_inButton_2_clicked()
{
    if(tree.root==nullptr){
        QMessageBox::warning(nullptr, "警告","请先创建树！",QMessageBox::Ok);
        return;
    }
    if(tree.ThreadType!=2){
        QMessageBox::warning(nullptr, "警告","未中序线索化！",QMessageBox::Ok);
        return;
    }
    QString in;
    for (BiTNode* p = tree.FirstNode(tree.root); p != NULL; p = tree.NextNode(p))
        in+=p->data;
    QString result="中序遍历为"+in;
    QMessageBox::information(this, "中序遍历",result,QMessageBox::Ok);
}

