#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isNegative(false)  // 初始化负号状态
{
    ui->setupUi(this);

    digitBTNs = { {Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9},
    };

    foreach (auto btn, digitBTNs)
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));

    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(binaryOperatorClicked()));
    connect(ui->btnMinus, SIGNAL(clicked()), this, SLOT(binaryOperatorClicked()));
    connect(ui->btnMultiple, SIGNAL(clicked()), this, SLOT(binaryOperatorClicked()));
    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(binaryOperatorClicked()));

    connect(ui->btnpercentage, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    if (operands.size() == 2 && opcodes.size() > 0) {
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();
        QString op = opcodes.front();
        opcodes.pop_front();

        if (op == "+") {
            result = operand1 + operand2;
        } else if (op == "-") {
            result = operand1 - operand2;
        } else if (op == "×") {
            result = operand1 * operand2;
        } else if (op == "/") {
            result = operand1 / operand2;
        }

        operands.push_back(QString::number(result));
        ui->statusbar->showMessage(QString("calculation is in progress: operands is %1, opcode is %2").arg(operands.size()).arg(
                                       opcodes.size()));
    } else {
        ui->statusbar->showMessage(QString("operands is %1, opcode is %2").arg(operands.size()).arg(opcodes.size()));
    }
    return QString::number(result);
}

void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    // 如果当前是负数状态，则加上负号
    if (isNegative) {
        operand = "-" + digit;
        isNegative = false;  // 重置状态
    } else {
        // 如果是0且点击数字，不添加前导0
        if (operand == "0" && digit != "0") {
            operand = "";
        }
        operand += digit;
    }

    ui->lineEdit->setText(operand);
}

void MainWindow::on_btnPoint_clicked()
{
    if (!operand.contains("."))
        operand += qobject_cast<QPushButton *>(sender())->text();
    ui->lineEdit->setText(operand);
}

void MainWindow::on_btnDel_clicked()
{
    if (!operand.isEmpty()) {
        operand = operand.left(operand.length() - 1);
    }
    if (operand.isEmpty()) {
        operand = "0";
    }
    ui->lineEdit->setText(operand);
}

void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->lineEdit->setText("0");
}

void MainWindow::on_btnClearAll_clicked()
{
    operand.clear();
    operands.clear();
    opcodes.clear();
    ui->lineEdit->clear();
}

void MainWindow::binaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton *>(sender())->text();

    if (operand != "") {
        operands.push_back(operand);
        operand = "";
    }
    opcodes.push_back(opcode);
    QString result = calculation();
    ui->lineEdit->setText(result);
}

void MainWindow::btnUnaryOperatorClicked()
{
    if (operand != "") {
        double result = operand.toDouble();
        operand = "";

        QString op = qobject_cast<QPushButton *>(sender())->text();

        if (op == "%")
            result /= 100.0;
        else if (op == "1/x")
            result = 1 / result;
        else if (op == "x^2")
            result *= result;
        else if (op == "√")
            result = sqrt(result);

        ui->lineEdit->setText(QString::number(result));
    }
}

void MainWindow::on_btnEqual_clicked()
{
    if (operand != "") {
        operands.push_back(operand);
        operand = "";
    }
    QString result = calculation();
    ui->lineEdit->setText(result);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach (auto btnKey, digitBTNs.keys()) {
        if (event->key() == btnKey)
            digitBTNs[btnKey]->animateClick();
    }
    if (event->key() == Qt::Key_Delete) {
        ui->btnDel->animateClick();
    }
    if (event->key() == Qt::Key_Period) {
        ui->btnPoint->animateClick();
    }
}

void MainWindow::on_btnPlusMinus_clicked()
{
    if (!operand.isEmpty()) {
        double value = operand.toDouble();
        value = -value;
        operand = QString::number(value);
    } else {
        isNegative = !isNegative;
        if (isNegative) {
            operand = "-";
        } else {
            operand = "";
        }
    }
    ui->lineEdit->setText(operand);
}
