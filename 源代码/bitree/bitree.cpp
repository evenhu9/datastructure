#include "bitree.h"
#include <iostream>
#include <QDebug>

using namespace std;

BiTNode::BiTNode()
{
    data='\0';
    lchild = nullptr;
    rchild = nullptr;
	lTag = 0;
	rTag = 0;
}

BiTNode::BiTNode(QChar a)
{
    data=a;
    lchild = nullptr;
    rchild = nullptr;
    lTag = 0;
    rTag = 0;
}

Status BiTree::isEmpty()
{
    if(root==nullptr)
        return OK;
    else
        return FALSE;
}

BiTNode* BiTree::createBiTree(QString str)//先序遍历创建二叉树
{
    static int i=0;
    if(ifhave==TRUE){
        i=0;
        ifhave=FALSE;
    }
    if (str[i] == '#'|| i>str.length())//没有树
    {
        return nullptr;
    }
    else
    {
        BiTNode* root = new BiTNode(str[i]);//新创建根结点
        i++;
        root->lchild = createBiTree(str);//创建左孩子
        i++;
        root->rchild = createBiTree(str);//创建右孩子
        return root;
    }
}

Status BiTree::preOrder(BiTNode *r)
{
    if(r==nullptr)return OK;
    preString.append(r->data);
    if (r->lchild!=nullptr){
        preOrder(r->lchild);
    }
    if (r->rchild!=nullptr){
        preOrder(r->rchild);
    }
	return OK;
}

Status BiTree::inOrder(BiTNode *r)
{
    if(r==nullptr)return OK;
    if (r->lchild!=nullptr){
        inOrder(r->lchild);
    }
    inString.append(r->data);
    if (r->rchild!=nullptr){
        inOrder(r->rchild);
    }
	return OK;
}

Status BiTree::postOrder(BiTNode *r)
{
    if(r==nullptr)return OK;
    if (r->lchild!=nullptr){
        postOrder(r->lchild);
    }
    if (r->rchild!=nullptr){
        postOrder(r->rchild);
    }
    postString.append(r->data);
	return OK;
}

BiTNode* BiTree::NextNode2(BiTNode* p) {
    if (p->rTag == 1)
        return p->rchild;
    else {						// 此时p必有右孩子
        if (p->lTag == 0)		// 有左孩子，左孩子为后继结点
            return p->lchild;
        else					// 无左孩子，右孩子为后继结点
            return p->rchild;
    }
}

//-----------------------------------------
// 找到以p为根节点的子树中，第一个被中序遍历的结点
BiTNode* BiTree::FirstNode(BiTNode* p) {
    while (p->lTag == 0)
        p = p->lchild;
    return p;
}

// 在中序线索二叉树中找到结点p的后继结点
BiTNode* BiTree::NextNode(BiTNode* p) {
    if (p->rTag == 1)
        return p->rchild;
    else
        return FirstNode(p->rchild);	// 返回右子树最左下结点（即p的后继节点）
}

BiTNode::~BiTNode()
{
    if(lchild != nullptr&&lchild->lchild==nullptr&&lchild->rchild==nullptr)
    {
        delete lchild;
        lchild=nullptr;
    }

    if(rchild != nullptr&&rchild->lchild==nullptr&&rchild->rchild==nullptr)
    {
        delete rchild;
        rchild=nullptr;
    }

    if (lchild!=nullptr)
        lchild->~BiTNode();
    if (rchild!=nullptr)
        rchild->~BiTNode();
}

Status BiTree::destroy()
{
    root->~BiTNode();
    return OK;
}

int  BiTree::Leaves(BiTNode *r)
{
    if (r == NULL)
        return 0;
    if (r->lchild == NULL && r->rchild == NULL)
        return 1;
    return Leaves(r->lchild) + Leaves(r->rchild);
}

Status  BiTree::preOrderThreading(BiTNode *r)
{
    static BiTNode *pre1=nullptr;
    if(ifThread==false){
        pre1=nullptr;
    }
    ifThread=true;
    ThreadType=1;
    if(pre1!=nullptr&&pre1->rTag)
        pre1->rchild=r;

    if(r->lchild==nullptr)
    {
        r->lTag=1;
        r->lchild=pre1;
    }
    if(r->rchild==nullptr){
        r->rTag=1;
    }
    pre1=r;
    if(r->lTag==false)
        preOrderThreading(r->lchild);
    if(r->rTag==false)
        preOrderThreading(r->rchild);
    return OK;
}

Status  BiTree::inOrderThreading(BiTNode *r)
{
    static BiTNode *pre2=nullptr;
    if(ifThread==false){
        pre2=nullptr;
    }
    ifThread=true;
    ThreadType=2;
    if (pre2 != nullptr&&pre2->rchild==nullptr){
        pre2->rchild = r;
        pre2->rTag=1;
    }
    if (r == NULL) {
        return OK;
    }
    inOrderThreading(r->lchild);
    if (r->lchild == nullptr)
    {
        r->lTag = 1;
        r->lchild = pre2;
    }
    if (pre2 != nullptr&&pre2->rchild==nullptr){
        pre2->rchild = r;
        pre2->rTag=1;
    }
    pre2 = r;
    inOrderThreading(r->rchild);
	return OK;
}

Status  BiTree::postOrderThreading(BiTNode *r)
{
    static BiTNode *pre3=nullptr;
    if(ifThread==false){
        pre3=nullptr;
    }
    ifThread=true;
    ThreadType=3;
    if (pre3 != nullptr&&pre3->rTag)
        pre3->rchild = r;

    if (r->lchild == nullptr)
	{
        r->lTag = 1;
        r->lchild = pre3;
	}
    if (r->rchild == nullptr)
        r->rTag = 1;

    if (r->lTag == false){
        postOrderThreading(r->lchild);
    }
    if (r->rTag == false){
        postOrderThreading(r->rchild);
    }
    pre3 = r;
	return OK;
}
Status BiTree::cleanThread(BiTNode *r){
    // 复原左子树
    if(r==nullptr)return OK;
    if (r->lTag) {
        r->lTag=0;
        r->lchild = nullptr;
    } else {
        cleanThread(r->lchild);
    }
    // 复原右子树
    if (r->rTag) {
        r->rTag=0;
        r->rchild = nullptr;
    } else {
        cleanThread(r->rchild);
    }

    ifThread=false;
    ThreadType=0;
    return OK;
}

int  BiTree::getHeight(BiTNode*r)
{
	if (r == nullptr)
		return 0;
    int i=0,j=0;
    if(r->lTag==0){
        i = getHeight(r->lchild);
    }
    if(r->rTag==0){
        j = getHeight(r->rchild);
    }
    return (i > j) ? i + 1 : j + 1;
}
BiTree::~BiTree()
{
    root->~BiTNode();
}
