#include "loginview.h"
#include "ui_loginview.h"
#include "mainview.h"

loginview::loginview(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginview)
{
    ui->setupUi(this);
}

loginview::~loginview()
{
    delete ui;
}

//登录功能，跳转到主页面
void loginview::on_btSignin_clicked()
{
    this->close();
    mainview *view = new mainview;
    view->show();
}

