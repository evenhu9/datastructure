#include <cstdlib>
#include <QString>

#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define Overflow	-2

typedef int Status;

typedef QChar ElemType;

typedef class BiTNode {
public:
    ElemType data;
    BiTNode *lchild, *rchild;
    bool lTag,rTag;
    BiTNode();
    BiTNode(QChar a);
    ~BiTNode();
}*BiTNodeP;

class BiTree {//创建二叉树
public:
    BiTNode *root;//根节点
    int leafNum;
    bool ifThread=FALSE,ifhave=FALSE;
    int ThreadType=0;
    QString preString,inString,postString;
    BiTree():root(nullptr){}
    ~BiTree();
    //传递节点指针的指针！！！const char*& str
    //用#表示空结点
    Status isEmpty();
    BiTNode * createBiTree(QString str);
    Status preOrder(BiTNode *r);
    Status inOrder(BiTNode *r);
    Status postOrder(BiTNode *r);
    BiTNode* NextNode2(BiTNode* p);
    BiTNode* NextNode(BiTNode* p);
    BiTNode* FirstNode(BiTNode* p);
    Status preOrderThreading(BiTNode *r);
    Status inOrderThreading(BiTNode *r);
    Status postOrderThreading(BiTNode *r);
    Status cleanThread(BiTNode *r);
    int Leaves(BiTNode *r);
    int getHeight(BiTNode *r);
    Status destroy();
    friend class Paint;
};
