#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"

DoctorEditView::DoctorEditView(QWidget *parent, int index)
    : QDialog(parent)
    , ui(new Ui::DoctorEditView)
{
    ui->setupUi(this);

    // 创建数据映射器，用于将UI组件与数据库表模型字段关联
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().doctorTabModel; // 获取数据库表模型实例
    dataMapper->setModel(IDatabase::getInstance().doctorTabModel); // 设置数据映射器的模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); // 设置自动提交策略

    // 将UI组件与数据库表模型的字段进行映射
    dataMapper->addMapping(ui->DoctorName, tabModel->fieldIndex("DoctorName"));
    dataMapper->addMapping(ui->Sex, tabModel->fieldIndex("Sex"));
    dataMapper->addMapping(ui->Ration, tabModel->fieldIndex("Ration"));
    dataMapper->addMapping(ui->EntryTime, tabModel->fieldIndex("EntryTime"));
    dataMapper->addMapping(ui->Born, tabModel->fieldIndex("Born"));
    dataMapper->addMapping(ui->Age, tabModel->fieldIndex("Age"));
    dataMapper->addMapping(ui->EducationBackground, tabModel->fieldIndex("EducationBackground"));
    dataMapper->addMapping(ui->MaritalStatus, tabModel->fieldIndex("MaritalStatus"));
    dataMapper->addMapping(ui->Height, tabModel->fieldIndex("Height"));
    dataMapper->addMapping(ui->Weight, tabModel->fieldIndex("Weight"));
    dataMapper->addMapping(ui->JobId, tabModel->fieldIndex("JobId"));
    dataMapper->addMapping(ui->Department, tabModel->fieldIndex("Department"));
    dataMapper->addMapping(ui->JobIdentity, tabModel->fieldIndex("JobIdentity"));
    dataMapper->addMapping(ui->CertificateType, tabModel->fieldIndex("CertificateType"));
    dataMapper->addMapping(ui->CertificateNumber, tabModel->fieldIndex("CertificateNumber"));
    dataMapper->addMapping(ui->NativePlace, tabModel->fieldIndex("NativePlace"));
    dataMapper->addMapping(ui->Place, tabModel->fieldIndex("Place"));
    dataMapper->addMapping(ui->Phone, tabModel->fieldIndex("Phone"));
    dataMapper->addMapping(ui->Email, tabModel->fieldIndex("Email"));
    dataMapper->addMapping(ui->PractiseCertificate, tabModel->fieldIndex("PractiseCertificate"));
    // 设置当前索引，用于定位到特定的数据记录
    dataMapper->setCurrentIndex(index);

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

