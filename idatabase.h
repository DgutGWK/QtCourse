#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>

class IDatabase : public QObject
{
    Q_OBJECT
public:

    static IDatabase &getInstance()
    {
        static IDatabase instance;
        return instance;
    }
    QString userLogin(QString userName, QString password);

private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const &) = delete;
    void operator=(IDatabase const &) = delete;
    QSqlDatabase database;
    void ininDatabase();

signals:

public:
    bool initDoctorModel();
    int addNewDoctor();
    bool searchDoctor(QString filter);
    void deleteCurrentDoctor();
    bool submitDoctorEdit();
    void revertDoctorEdit();
    QSqlTableModel *doctorTabModel;     //数据模型
    QItemSelectionModel *theDoctorSelection;     //选择模型

    bool initPatientModel();
    int addNewPatient();
    bool searchPatient(QString filter);
    void deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();
    QSqlTableModel *patientTabModel;     //数据模型
    QItemSelectionModel *thePatientSelection;     //选择模型

    bool initDrugModel();
    int addNewDrug();
    bool searchDrug(QString filter);
    void deleteCurrentDrug();
    bool submitDrugEdit();
    void revertDrugEdit();
    QSqlTableModel *drugTabModel;     //数据模型
    QItemSelectionModel *theDrugSelection;     //选择模型

    bool initTreatRecordModel();
    int addNewTreatRecord();
    bool searchTreatRecord(QString filter);
    void deleteCurrentTreatRecord();
    bool submitTreatRecordEdit();
    void revertTreatRecordEdit();
    QSqlTableModel *TreatRecordTabModel;     //数据模型
    QItemSelectionModel *theTreatRecordSelection;     //选择模型
};

#endif // IDATABASE_H
