#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QMainWindow>

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

private slots:
    void on_btSignin_clicked();

private:
    Ui::loginview *ui;
};
#endif // LOGINVIEW_H
