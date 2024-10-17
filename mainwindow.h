#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QKeyEvent>
#include <QString>
#include <QList>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void btnNumClicked();
    void binaryOperatorClicked();
    void btnUnaryOperatorClicked();
    void on_btnEqual_clicked();
    void on_btnClear_clicked();
    void on_btnClearAll_clicked();
    void on_btnDel_clicked();
    void on_btnPoint_clicked();
    void on_btnPlusMinus_clicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QString operand;
    QList<QString> operands;
    QList<QString> opcodes;

    // 添加 isNegative 变量
    bool isNegative;

    // 添加 digitBTNs 变量
    QMap<int, QPushButton *> digitBTNs; // 声明 digitBTNs 变量

    // 声明 calculation 函数
    QString calculation(bool *ok = nullptr);  // 添加或确认这一行
};

#endif // MAINWINDOW_H

