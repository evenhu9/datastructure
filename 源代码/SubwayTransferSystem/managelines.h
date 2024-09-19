#ifndef MANAGELINES_H
#define MANAGELINES_H

#include <QDialog>
#include <QVector>
#include <QTabWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QString>

class MainWindow;

namespace Ui {
class ManageLines;
}

class ManageLines : public QDialog
{
    Q_OBJECT

private slots:
    void on_lineEditLineName_textChanged(const QString &arg1);
    void on_pushButtonChooseColor_clicked();
    void on_lineEditStationName_textChanged(const QString &arg1);
    void on_doubleSpinBoxLatitude_valueChanged(double arg1);
    void on_doubleSpinBoxLongitude_valueChanged(double arg1);
    void on_listWidget_itemClicked(QListWidgetItem *item);

public:
    explicit ManageLines(QWidget *parent = 0);
    ~ManageLines();
    void setAllVisible();//设置所有部件可见
    void setAddLineVisible();
    void setAddStationVisible();
    void setAddConnectionVisible();
    void updateLinesListWidget();
    void updateComboBox();

protected:
    Ui::ManageLines *ui;
    QVector<QWidget*> tabWigetsVector;  //保存tab部件指针
    QVector<QIcon> tabIconVector;       //保存tab部件Icon
    QVector<QString> tabTextVector;     //保存tab部件标题
    QString lineName;                   //保存输入线路名
    QColor lineColor;                   //保存输入线路颜色
    QString stationName;                //保存输入站点名
    double longitude;                   //保存输入站点经度
    double latitude;                    //保存输入站点纬度
    QList<QString> linesNameList;       //保存选择线路名表
    QList<QString> linesSelected;       //保存选择的线路名
    QList<QString> stationsNameList;    //保存选择站点名表

    friend class MainWindow;
};

#endif // MANAGELINES_H
