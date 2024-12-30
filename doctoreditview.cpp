#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"
#include <QSqlTableModel>

DoctorEditView::DoctorEditView(QWidget *parent, int index)
    : QDialog(parent)
    , ui(new Ui::DoctorEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().doctorTabModel;
    dataMapper->setModel(IDatabase::getInstance().doctorTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->DoctorName, tabModel->fieldIndex("DoctorName"));
    dataMapper->addMapping(ui->Sex, tabModel->fieldIndex("Ses"));
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

    dataMapper->setCurrentIndex(index);
}

DoctorEditView::~DoctorEditView()
{
    delete ui;
}
