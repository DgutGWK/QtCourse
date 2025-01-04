#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"

loginview::loginview(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginview)
{
    ui->setupUi(this);

    connect(this, SIGNAL(loginSuccess()), this, SLOT(goMainView()));

    IDatabase::getInstance();

}

loginview::~loginview()
{
    delete ui;
}


void loginview::goMainView()
{
    qDebug() << "goMainView";
    this->close();
    MainView = new mainview(this);
    connect(MainView, SIGNAL(backSuccess()), this, SLOT(reshow()));
    MainView->show();
}

void loginview::reshow()
{
    this->show();
}

//登录功能，跳转到主页面
void loginview::on_btSignin_clicked()
{
    QString status = IDatabase::getInstance().userLogin(ui->inputUserName->text(), ui->inputUserPassword->text());

    if (status == "loginOk")
        emit loginSuccess();
}


void loginview::on_btSignUp_clicked()
{
    qDebug() << "goRegisterView";
    registerview = new RegisterView(this);
    connect(registerview, SIGNAL(backSuccess()), this, SLOT(reshow()));
    registerview->show();
}

