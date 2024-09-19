#ifndef SUBWAYGRAPH_H
#define SUBWAYGRAPH_H

#include "station.h"
#include "line.h"
#include <QString>
#include <QPoint>
#include <QVector>
#include <QHash>

//图的邻接点结构
class Node{
public:
    int stationID;      //邻接点ID
    double distance;    //两点距离

    Node(){};
    Node(int s, double dist) :stationID(s), distance(dist)
    {};
    //">"运算重载，用于小顶堆
    bool operator > (const Node& n) const
    {
        return this->distance>n.distance;
    }
};

class SubwayGraph{
protected:
    QVector<Station> stations;          //存储所有站点
    QVector<Line> lines;                //存储所有线路
    QHash<QString, int> stationsHash;   //站点名到存储位置的hash
    QHash<QString, int> linesHash;      //线路名到存储位置的hash
    QSet<Edge> edges;                   //所有边的集合
    QVector<QVector<Node>> graph;       //地铁线路网络图
public:
    SubwayGraph();
    QString getLineName(int l);
    QColor getLineColor(int l);
    int getLineHash(QString lineName);
    QList<int> getLinesHash(QList<QString> linesList);
    QList<QString> getLinesNameList();
    QList<QString> getLineStationsList(int l);//获取线路的所有包含站点
    QString getStationName(int s);
    QPointF getStationCoord(int s);
    QPointF getMinCoord();
    QPointF getMaxCoord();
    QList<int> getStationLinesInfo(int s);
    QList<int> getCommonLines(int s1, int s2); //获取两个站点的公共所属线路
    int getStationHash(QString stationName);
    QList<QString> getStationsNameList();

    void addLine(QString lineName, QColor color); //添加新线路
    void addStation(Station s); //添加新站点
    void addConnection(int s1, int s2, int l);//添加站点连接关系
    void getGraph(QList<int>&stationsList, QList<Edge>&edgesList);
    //获取最少时间的线路
    bool queryTransferMinTime(int s1, int s2,QList<int>&stationsList,QList<Edge>&edgesList);
    //获取最少换乘的线路
    bool queryTransferMinTransfer(int s1, int s2,QList<int>&stationsList,QList<Edge>&edgesList);
    bool readFileData(QString fileName);
private:  
    void clearData();
    bool insertEdge(int s1, int s2);
    void updateMinMaxLongiLati();
    void makeGraph();
};

#endif // SUBWAYGRAPH_H
