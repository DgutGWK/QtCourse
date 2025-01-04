#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"

PatientEditView::PatientEditView(QWidget *parent, int index)
    : QDialog(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    // 创建数据映射器，用于将UI组件与数据库表模型字段关联
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().patientTabModel; // 获取数据库表模型实例
    dataMapper->setModel(IDatabase::getInstance().patientTabModel); // 设置数据映射器的模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); // 设置自动提交策略

    // 将UI组件与数据库表模型的字段进行映射
    dataMapper->addMapping(ui->PatientName, tabModel->fieldIndex("PatientName"));
    dataMapper->addMapping(ui->Sex, tabModel->fieldIndex("Sex"));
    dataMapper->addMapping(ui->Ration, tabModel->fieldIndex("Ration"));
    dataMapper->addMapping(ui->Height, tabModel->fieldIndex("Height"));
    dataMapper->addMapping(ui->Weight, tabModel->fieldIndex("Weight"));
    dataMapper->addMapping(ui->Born, tabModel->fieldIndex("Born"));
    dataMapper->addMapping(ui->Age, tabModel->fieldIndex("Age"));
    dataMapper->addMapping(ui->CertificateType, tabModel->fieldIndex("CertificateType"));
    dataMapper->addMapping(ui->CertificateNumber, tabModel->fieldIndex("CertificateNumber"));
    dataMapper->addMapping(ui->NativePlace, tabModel->fieldIndex("NativePlace"));
    dataMapper->addMapping(ui->Place, tabModel->fieldIndex("Place"));
    dataMapper->addMapping(ui->Phone, tabModel->fieldIndex("Phone"));
    dataMapper->addMapping(ui->Email, tabModel->fieldIndex("Email"));
    // 设置当前索引，用于定位到特定的数据记录
    dataMapper->setCurrentIndex(index);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_btSavePatientMessage_clicked()
{
    qDebug() << "goPreviousView";
    IDatabase::getInstance().submitPatientEdit();
    emit goPreviousView();
    this->close();
}

void PatientEditView::on_btCancelPatientMessage_clicked()
{
    qDebug() << "goPreviousView";
    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();
    this->close();
}

