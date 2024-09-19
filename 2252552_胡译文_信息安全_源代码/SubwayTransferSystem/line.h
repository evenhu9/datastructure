#ifndef LINE_H
#define LINE_H

#include <QString>
#include <QColor>
#include <QPair>
#include <QSet>
#include <QVector>

typedef QPair<int,int> Edge;
class SubwayGraph;
class QTextStream;
class Line
{
protected:
    int id;                     //线路ID
    QString name;               //线路名称
    QColor color;               //线路颜色
    QVector <QString> fromTo;   //线路起始站点
    QSet<int> stationsSet;      //线路站点集合
    QSet<Edge> edges;           //线路站点连接关系

public:
    Line(){};
    Line(QString lineName, QColor lineColor):name(lineName), color(lineColor)
    {};
    friend class SubwayGraph;
    friend class QTextStream;
};

#endif // LINE_H
