#include"paint.h"
#include <QPainter>
#include<stack>
#include<cstdio>
#include<QStack>
#include<QStack>
#include<QPoint>

Paint::Paint(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);
}

void Paint::setBiTree(BiTree* tr)
{
    tree=tr;
    return;
}


void Paint::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    BiTNodeP bt=tree->root;
    struct stackNode
    {
        BiTNode * treeNode;
        int layer;      // 标记该节点属于第几层
    };
        // 反锯齿
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::TextAntialiasing);


        //设置字体
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        painter.setFont(font);

        //设置画笔
        QPen penLine;
        penLine.setWidth(2); //线宽
        penLine.setColor(Qt::blue); //划线颜色
        penLine.setStyle(Qt::SolidLine);//线的类型，实线、虚线等
        penLine.setCapStyle(Qt::FlatCap);//线端点样式
        penLine.setJoinStyle(Qt::BevelJoin);//线的连接点样式
        painter.setPen(penLine);

        qreal W = this->width();                            // 画布的宽
        qreal H = this->height();                           // 画布的高
        int treeHeight = tree->getHeight(tree->root);               // 树的高度
        qreal R = W / (2 * std::pow(2, treeHeight) + 2);    // 节点的半径

        const int layerHeight = int((H-4*R) / (treeHeight-1));     // 层高，即垂直偏移量

        // 初始化
        // 节点的定义
        QRectF node(QPointF(-R, -R), QPointF(R, R));
        std::stack<stackNode> stack;    // 存放右孩子节点
        stackNode qNode;

        std::stack<QPointF> points;     // 存放右孩子节点相对于当前坐标系统原点的位置
        QPointF point;

        qreal Hoffset;                  // 水平偏移量
        const qreal Pi = 3.14159;
        int curLayer = 1;
        int curAngle;                   // 当前角度
        qreal deg;                      // 当前弧度

        // 将坐标系统的原点（下文简称原点）移动到初始位置
        painter.translate(W/2, 2*R);

        while (1)
        {
            painter.drawEllipse(node);
            painter.drawText(node, Qt::AlignCenter, QString(bt->data));

            // 设置孩子节点相对于父节点的水平偏移量
            Hoffset = std::pow(2, (treeHeight - curLayer)) * R;
            deg = std::atan(Hoffset / layerHeight);             // 返回的是弧度
            curAngle = int(180 / Pi * deg);                          // 将弧度转化为角度

            if (bt->rchild != nullptr&&bt->rTag==0)
            {
                // 坐标轴逆时针旋转
                painter.rotate(-curAngle);

                //绘制图形路径
                painter.drawLine(0, int(R), 0, int(layerHeight / std::cos(deg) - R));

                // 旋转复原
                painter.rotate(curAngle);

                // 右孩子节点压栈
                qNode.treeNode = bt->rchild;
                qNode.layer = curLayer + 1;
                stack.push(qNode);

                // 右孩子相对于当前坐标系统原点的位置压栈
                points.push(QPointF(QPointF(0, 0) + QPointF(Hoffset, layerHeight)));
                painter.save();
            }
            if (bt->lchild != nullptr&&bt->lTag==0)
            {
                // 坐标轴顺时针旋转
                painter.rotate(curAngle);
                // 绘制边
                painter.drawLine(0, int(R), 0, int(layerHeight / std::cos(deg) - R));
                // 旋转复原
                painter.rotate(-curAngle);
                // 原点移动到左孩子节点的位置
                painter.translate(QPointF(QPointF(0, 0) + QPointF(-Hoffset, layerHeight)));
                bt = bt->lchild;
                // 层次加1
                curLayer++;
            }
            else {
                    if(stack.empty())
                    {
                        painter.resetTransform();
                        return;
                    }
                    qNode=stack.top();
                    stack.pop();
                    bt = qNode.treeNode;
                    curLayer = qNode.layer;

                    painter.restore();
                    point=points.top();
                    points.pop();
                    painter.translate(point);
                }

        }
}
