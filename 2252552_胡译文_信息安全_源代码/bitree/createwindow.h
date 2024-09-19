#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QDialog>

namespace Ui {
class CreateWindow;
}

class CreateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateWindow(QWidget *parent = nullptr);
    ~CreateWindow();
    bool canFormBiTree();
    friend class BitreeMainWindow;

private slots:
    void createWindow_OKButton_clicked();
    void on_createWindowLineEdit_textEdited();

private:
    Ui::CreateWindow *ui;

protected:
    bool ifgood=false;
    QString createWindowTextEditString;
};

#endif // CREATEWINDOW_H
