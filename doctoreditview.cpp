#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QDateTime>

DoctorEditView::DoctorEditView(QWidget *parent, int index)
    : QDialog(parent)
    , ui(new Ui::DoctorEditView)
{
    ui->setupUi(this);

    setupBornComboBoxes();

    // 创建数据映射器，用于将UI组件与数据库表模型字段关联
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().doctorTabModel; // 获取数据库表模型实例
    dataMapper->setModel(IDatabase::getInstance().doctorTabModel); // 设置数据映射器的模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); // 设置自动提交策略

    // 将UI组件与数据库表模型的字段进行映射
    dataMapper->addMapping(ui->DoctorName, tabModel->fieldIndex("DoctorName"));
    dataMapper->addMapping(ui->Sex, tabModel->fieldIndex("Sex"));
    dataMapper->addMapping(ui->Ration, tabModel->fieldIndex("Ration"));
    dataMapper->addMapping(ui->Age, tabModel->fieldIndex("Age"));
    dataMapper->addMapping(ui->Height, tabModel->fieldIndex("Height"));
    dataMapper->addMapping(ui->Weight, tabModel->fieldIndex("Weight"));
    dataMapper->addMapping(ui->JobId, tabModel->fieldIndex("JobId"));
    dataMapper->addMapping(ui->Department, tabModel->fieldIndex("Department"));
    dataMapper->addMapping(ui->JobIdentity, tabModel->fieldIndex("JobIdentity"));
    dataMapper->addMapping(ui->CertificateType, tabModel->fieldIndex("CertificateType"));
    dataMapper->addMapping(ui->CertificateNumber, tabModel->fieldIndex("CertificateNumber"));
    dataMapper->addMapping(ui->Place, tabModel->fieldIndex("Place"));
    dataMapper->addMapping(ui->Phone, tabModel->fieldIndex("Phone"));
    dataMapper->addMapping(ui->Email, tabModel->fieldIndex("Email"));
    dataMapper->addMapping(ui->PractiseCertificate, tabModel->fieldIndex("PractiseCertificate"));
    // 设置当前索引，用于定位到特定的数据记录
    dataMapper->setCurrentIndex(index);

    // 当用户选择年月日时
    connect(ui->Born_Year, SIGNAL(activated(int)), this, SLOT(onDateSelected()));
    connect(ui->Born_Month, SIGNAL(activated(int)), this, SLOT(onDateSelected()));
    connect(ui->Born_Day, SIGNAL(activated(int)), this, SLOT(onDateSelected()));
}

DoctorEditView::~DoctorEditView()
{
    delete ui;
}

//提交医生信息的编辑，返回到上一个视图
void DoctorEditView::on_btSaveDoctorMessage_clicked()
{
    qDebug() << "goPreviousView";
    IDatabase::getInstance().submitDoctorEdit();
    emit goPreviousView();
    this->close();
}


void DoctorEditView::on_btCancelDoctorMessage_clicked()
{
    qDebug() << "goPreviousView";
    IDatabase::getInstance().revertDoctorEdit();
    emit goPreviousView();
    this->close();
}

void DoctorEditView::setupBornComboBoxes()
{
    // 获取当前年份
    int currentYear = QDate::currentDate().year();

    // 填充年份
    for (int year = currentYear; year >= 1900; --year) {
        ui->Born_Year->addItem(QString::number(year));
    }

    // 填充月份
    for (int month = 1; month <= 12; ++month) {
        ui->Born_Month->addItem(QString::number(month));
    }

    // 填充日期（根据月份动态调整）
    connect(ui->Born_Year, &QComboBox::currentTextChanged, this, &DoctorEditView::initDate);
    connect(ui->Born_Month, &QComboBox::currentTextChanged, this, &DoctorEditView::initDate);

    // 初始化日期
    initDate();
}

void DoctorEditView::initDate()
{
    int year = ui->Born_Year->currentText().toInt();
    int month = ui->Born_Month->currentText().toInt();
    int daysInMonth = QDate(year, month, 1).daysInMonth();

    ui->Born_Day->clear();
    for (int day = 1; day <= daysInMonth; ++day) {
        ui->Born_Day->addItem(QString::number(day));
    }
}

void DoctorEditView::onDateSelected()
{
    QString year = ui->Born_Year->currentText();
    QString month = ui->Born_Month->currentText();
    QString day = ui->Born_Day->currentText();
    QString date = year + "-" + month + "-" + day; // 组合日期

    // 将组合的日期保存到数据库
    QSqlQuery query;
    query.prepare("INSERT INTO Doctor (Born) VALUES (:born)");
    query.bindValue(":born", date);
    query.exec();
}


void DoctorEditView::on_Born_Year_activated(int index)
{
    QString year = ui->Born_Year->itemText(index);
}


void DoctorEditView::on_Born_Month_activated(int index)
{
    QString month = ui->Born_Month->itemText(index);
}


void DoctorEditView::on_Born_Day_activated(int index)
{
    QString day = ui->Born_Day->itemText(index);
}

