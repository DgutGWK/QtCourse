#include "registerview.h"
#include "ui_registerview.h"

RegisterView::RegisterView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterView)
{
    ui->setupUi(this);
}

RegisterView::~RegisterView()
{
    delete ui;
}

void RegisterView::on_btRegister_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    // 根据当前页面获取输入数据
    if (currentIndex == 0) {
        QString UserName = ui->UserName->text();
        QString Password = ui->Password->text();
        QString DoctorName = ui->DoctorName->text();
        QString Sex = ui->Sex->currentText();
        QString Ration = ui->Ration->currentText();
        QString EntryTime = ui->EntryTime->text();
        QString Born = ui->Born->text();
        int Age = ui->Age->value();
        double Height = ui->Height->value();
        double Weight = ui->Weight->value();
        QString JobId = ui->JobId->text();
        QString Department = ui->Department->currentText();
        QString JobIdenty = ui->JobIdentity->currentText();
        QString CertificateType = ui->CertificateType->currentText();
        QString CertificateNumber = ui->CertificateNumber->text();
        QString NativePlace = ui->NativePlace->text();
        QString Place = ui->Place->text();
        QString Phone = ui->Phone->text();
        QString Email = ui->Email->text();
        QString PractiseCertificate = ui->PractiseCertificate->text();

        // 数据库操作：保存医生信息
        saveDoctorToDatabase(UserName, Password, DoctorName, Sex, Ration, EntryTime, Born, Age, Height, Weight, JobId,
                             Department, JobIdenty, CertificateType, CertificateNumber, NativePlace, Place, Phone, Email, PractiseCertificate);
    } else if (currentIndex == 1) {
        QString UserName = ui->UserName->text();
        QString Password = ui->Password->text();
        QString PatientName = ui->PatientName->text();
        QString Sex = ui->Sex_2->currentText();
        QString Ration = ui->Ration_2->currentText();
        QString Born = ui->Born_2->text();
        int Age = ui->Age_2->value();
        double Height = ui->Height_2->value();
        double Weight = ui->Weight_2->value();
        QString CertificateType = ui->CertificateType_2->currentText();
        QString CertificateNumber = ui->CertificateNumber_2->text();
        QString NativePlace = ui->NativePlace_2->text();
        QString Place = ui->Place_2->text();
        QString Phone = ui->Phone_2->text();
        QString Email = ui->Email_2->text();

        // 数据库操作：保存患者信息
        savePatientToDatabase(UserName, Password, PatientName, Sex, Ration, Born, Age, Height, Weight, CertificateType,
                              CertificateNumber, NativePlace, Place, Phone, Email);
    }
}


void RegisterView::on_btCancel_clicked()
{
    this->close();
}


void RegisterView::on_DoctorOrPatient_activated(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void RegisterView::saveDoctorToDatabase(
    const QString &UserName, const QString &Password, const QString &DoctorName, const QString &Sex, const QString &Ration,
    const QString &EntryTime, const QString &Born, const int Age, const double Height, const double Weight,
    const QString &JobId, const QString &Department, const QString &JobIdenty, const QString &CertificateType,
    const QString &CertificateNumber, const QString &NativePlace, const QString &Place, const QString &Phone,
    const QString &Email, const QString &PractiseCertificate)
{
    // 准备 SQL 插入语句
    QSqlQuery query;
    query.prepare("INSERT INTO User (UserName, Password) VALUES (:UserName, :Password)");
    query.bindValue(":UserName", UserName);
    query.bindValue(":Password", Password);

    // 执行插入操作
    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to insert user!");
        return;
    }

    // 获取生成的 UserId
    int Id = query.lastInsertId().toInt();

    // 插入到 Doctor 表
    query.prepare(R"(
        INSERT INTO Doctor (Id, DoctorName, Sex, Ration, EntryTime, Born, Age, Height, Weight, JobId,
                            Department, JobIdenty, CertificateType, CertificateNumber, NativePlace, Place, Phone, Email, PractiseCertificate)
        VALUES (:Id, :DoctorName, :Sex, :Ration, :EntryTime, :Born, :Age, :Height, :Weight, :JobId, :Department, :JobIdenty,
                :CertificateType, :CertificateNumber, :NativePlace, :Place, :Phone, :Email, :PractiseCertificate)
    )");

    // 绑定参数
    query.bindValue(":Id", Id);
    query.bindValue(":DoctorName", DoctorName);
    query.bindValue(":Sex", Sex);
    query.bindValue(":Ration", Ration);
    query.bindValue(":EntryTime", EntryTime);
    query.bindValue(":Born", Born);
    query.bindValue(":Age", Age);
    query.bindValue(":Height", Height);
    query.bindValue(":Weight", Weight);
    query.bindValue(":JobId", JobId);
    query.bindValue(":Department", Department);
    query.bindValue(":JobIdenty", JobIdenty);
    query.bindValue(":CertificateType", CertificateType);
    query.bindValue(":CertificateNumber", CertificateNumber);
    query.bindValue(":NativePlace", NativePlace);
    query.bindValue(":Place", Place);
    query.bindValue(":Phone", Phone);
    query.bindValue(":Email", Email);
    query.bindValue(":PractiseCertificate", PractiseCertificate);

    // 执行插入操作并处理结果
    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to register doctor!");
    } else {
        QMessageBox::information(nullptr, "Success", "Doctor registered successfully!");
    }
}

void RegisterView::savePatientToDatabase(
    const QString &UserName, const QString &Password, const QString &PatientName, const QString &Sex, const QString &Ration,
    const QString &Born, const int Age, const double Height, const double Weight, const QString &CertificateType,
    const QString &CertificateNumber, const QString &NativePlace, const QString &Place, const QString &Phone,
    const QString &Email)
{

    QSqlQuery query;
    // 获取生成的 UserID
    int Id = query.lastInsertId().toInt();
    if (Id == 0) Id++;
    query.prepare("INSERT INTO User (Id, UserName, Password) VALUES (:Id, :UserName, :Password)");
    query.bindValue(":UserName", UserName);
    query.bindValue(":Password", Password);
    query.bindValue(":Id", Id);
    // 插入到 Patient 表
    query.prepare(R"(
        INSERT INTO Patient (Id, PatientName, Sex, Ration, Born, Age, Height, Weight,
                             CertificateType, CertificateNumber, NativePlace, Place, Phone, Email)
        VALUES (:Id, :PatientName, :Sex, :Ration, :Born, :Age, :Height, :Weight,
                :CertificateType, :CertificateNumber, :NativePlace, :Place, :Phone, :Email)
    )");
    query.bindValue(":Id", Id);
    query.bindValue(":UserName", UserName);
    query.bindValue(":Password", Password);
    query.bindValue(":PatientName", PatientName);
    query.bindValue(":Sex", Sex);
    query.bindValue(":Ration", Ration);
    query.bindValue(":Born", Born);
    query.bindValue(":Age", Age);
    query.bindValue(":Height", Height);
    query.bindValue(":Weight", Weight);
    query.bindValue(":CertificateType", CertificateType);
    query.bindValue(":CertificateNumber", CertificateNumber);
    query.bindValue(":NativePlace", NativePlace);
    query.bindValue(":Place", Place);
    query.bindValue(":Phone", Phone);
    query.bindValue(":Email", Email);

    // 执行插入操作并处理结果
    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to register patient!");
    } else {
        QMessageBox::information(nullptr, "Success", "Patient registered successfully!");
    }
}
