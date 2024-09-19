#include <QWidget>
#include "bitree.h"


class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = nullptr);
    void setBiTree(BiTree* tr);
    friend class BiTree;
protected:
    void paintEvent(QPaintEvent *event);
private:
    BiTree* tree;
    const int rootLengt=160;
    const double PI=3.1415926;
};
