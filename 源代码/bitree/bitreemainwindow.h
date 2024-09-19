#ifndef BitreeMainWindow_H
#define BitreeMainWindow_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QMenu>
#include <QMenuBar>
#include <qlogging.h>
#include <QMessageBox>
#include <QScrollArea>
#include <QTextCodec>

#include "createwindow.h"
#include "paint.h"


namespace Ui
{
    class BitreeMainWindow;
}


class BitreeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BitreeMainWindow(QWidget *parent = nullptr);
    ~BitreeMainWindow();

    friend class CreateWindow;

private slots:
    void createWindowButton_clicked();
    void bitreeDisplayButton_clicked();
    void actionHelpButton_clicked();
    void on_bitreeLeafCountButton_clicked();
    void on_preButton_clicked();
    void on_inButton_clicked();
    void on_postButton_clicked();

    void on_prethreadButton_clicked();

    void on_inthreadButton_clicked();

    void on_posthreadButton_clicked();

    void on_preButton_2_clicked();

    void on_inButton_2_clicked();

private:
    Ui::BitreeMainWindow *ui;

    QMenu *menuBarHelp;
    QAction *actionHelpOpen;

protected:
    QString biTreeString;
    BiTree tree;
};


#endif // BitreeMainWindow_H
