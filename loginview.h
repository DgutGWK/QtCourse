#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QMainWindow>
#include "mainview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class loginview;
}
QT_END_NAMESPACE

class loginview : public QMainWindow
{
    Q_OBJECT

public:
    loginview(QWidget *parent = nullptr);
    ~loginview();

public slots:
    void goMainView();
    void reshow();

private slots:
    void on_btSignin_clicked();

signals:
    void loginSuccess();

private:
    void pushWidgetToStackView(QWidget *widget);
    Ui::loginview *ui;
    mainview *MainView;

};
#endif // LOGINVIEW_H
