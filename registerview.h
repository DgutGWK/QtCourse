#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class RegisterView;
}

class RegisterView : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterView(QWidget *parent = nullptr);
    ~RegisterView();

signals:
    void backSuccess();

private slots:
    void on_btRegister_clicked();

    void on_btCancel_clicked();

    void on_DoctorOrPatient_activated(int index);

    void saveDoctorToDatabase(const QString &UserName, const QString &Password, const QString &DoctorName, const QString &Sex, const QString &Ration,
                              const QString &EntryTime, const QString &Born, const int Age, const double Height, const double Weight,
                              const QString &JobId,
                              const QString &Department, const QString &JobIdenty, const QString &CertificateType, const QString &CertificateNumber,
                              const QString &NativePlace, const QString &Place, const QString &Phone, const QString &Email,
                              const QString &PractiseCertificate);
    void savePatientToDatabase(
        const QString &UserName, const QString &Password, const QString &PatientName, const QString &Sex, const QString &Ration,
        const QString &Born, const int Age, const double Height, const double Weight, const QString &CertificateType,
        const QString &CertificateNumber, const QString &NativePlace, const QString &Place, const QString &Phone,
        const QString &Email);

private:
    Ui::RegisterView *ui;
};

#endif // REGISTERVIEW_H
