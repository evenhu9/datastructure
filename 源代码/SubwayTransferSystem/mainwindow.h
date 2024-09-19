#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphics_view_zoom.h"
#include "subwaygraph.h"
#include "managelines.h"
#include "apphelp.h"

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_toolEnlarge_triggered();
    void on_toolShrink_triggered();
    void on_actionAddAll_triggered();
    void on_actionAddLine_triggered();
    void on_actionAddStation_triggered();
    void on_actionAddConnect_triggered();
    void on_actionLineMap_triggered();
    void on_actionstatusBar_triggered(bool checked);
    void on_actiontoolBar_triggered(bool checked);
    void on_actionuseHelp_triggered();
    void on_actionClose_triggered();

    void timerUpdate();
    void tabWidgetCurrentChanged(int index);
    void addLine();
    void addStation();
    void addConnection();
    void updateTranserQueryInfo();
    void transferStartLineChanged(QString lineName);
    void transferDstLineChanged(QString lineNames);
    void transferQuery();


protected:
    Ui::MainWindow *ui;             //主窗口UI
    Graphics_view_zoom *myView;     //自定义视图，用于鼠标缩放
    QGraphicsScene *scene;          //场景
    SubwayGraph* subwayGraph;       //后端管理类
    ManageLines* manageLines;       //添加功能前端管理类
    AppHelp* appHelp;               //帮助显示类

    QColor getLinesColor(const QList<int>& linesList);
    QString getLinesName(const QList<int>& linesList);
    QPointF transferCoord(QPointF coord);
    void drawEdges (const QList<Edge>& edgesList);
    void drawStations (const QList<int>& stationsList);

private slots:
    void on_comboBoxStartLine_currentTextChanged(const QString &arg1);

    void on_comboBoxDstLine_currentTextChanged(const QString &arg1);

private:
    QLabel* statusLabel1, *statusLabel2, *statusLabel3;     //状态栏三个文本
    void initStatusBar();
};

#define LINE_INFO_WIDTH 0   //预留边框用于信息展示
#define MARGIN 30           //视图左边距
#define NET_WIDTH 2000      //网络图最大宽度
#define NET_HEIGHT 2000     //网络图最大高度
#define SCENE_WIDTH (LINE_INFO_WIDTH+MARGIN*2+NET_WIDTH)    //视图宽度
#define SCENE_HEIGHT (MARGIN*2+NET_HEIGHT)                  //视图高度

#define EDGE_PEN_WIDTH 2    //线路边宽
#define NODE_HALF_WIDTH 3   //节点大小

#endif // MAINWINDOW_H
