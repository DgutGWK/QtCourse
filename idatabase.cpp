#include "idatabase.h"

void IDatabase::ininDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");     //添加 SQL LITE数据库驱动
    QString aFile = "D:/Qt/QtProject/HospitalSystemDatabase.db";
    database.setDatabaseName(aFile);     //设置数据库名称

    if (!database.open()) {     //打开数据库
        qDebug() << "failed to open database";
    } else
        qDebug() << "open database is ok" << database.connectionName();
}

bool IDatabase::initDoctorModel()
{
    doctorTabModel = new QSqlTableModel(this, database);
    doctorTabModel->setTable("doctor");
    doctorTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);     //数据保存方式，OnManualSubmit，OnRowChange
    doctorTabModel->setSort(doctorTabModel->fieldIndex("Id"), Qt::AscendingOrder);     //排序
    if (!(doctorTabModel->select()))     //查询数据
        return false;
    theDoctorSelection = new QItemSelectionModel(doctorTabModel);
    return true;
}

int IDatabase::addNewDoctor()
{
    doctorTabModel->insertRow(doctorTabModel->rowCount(), QModelIndex());
    QModelIndex curIndex = doctorTabModel->index(doctorTabModel->rowCount() - 1, 1);
    int curRecNo = curIndex.row();
    QSqlRecord curRec = doctorTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    doctorTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchDoctor(QString filter)
{
    doctorTabModel->setFilter(filter);
    return doctorTabModel->select();
}

void IDatabase::deleteCurrentDoctor()
{
    QModelIndex curIndex = theDoctorSelection->currentIndex();     //获取当前选择单元格的模型索引
    doctorTabModel->removeRow(curIndex.row());
    doctorTabModel->submitAll();
    doctorTabModel->select();
}

bool IDatabase::submitDoctorEdit()
{
    return doctorTabModel->submitAll();
}

void IDatabase::revertDoctorEdit()
{
    doctorTabModel->revertAll();
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this, database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(
        QSqlTableModel::OnManualSubmit);     //数据保存方式，OnManualSubmit，OnRowChange
    patientTabModel->setSort(patientTabModel->fieldIndex("Id"), Qt::AscendingOrder);     //排序
    if (!(patientTabModel->select()))     //查询数据
        return false;
    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;
}

int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(), QModelIndex());
    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount() - 1, 1);
    int curRecNo = curIndex.row();
    QSqlRecord curRec = patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    patientTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

void IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();     //获取当前选择单元格的模型索引
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

bool IDatabase::initDrugModel()
{
    drugTabModel = new QSqlTableModel(this, database);
    drugTabModel->setTable("drug");
    drugTabModel->setEditStrategy(
        QSqlTableModel::OnManualSubmit);     //数据保存方式，OnManualSubmit，OnRowChange
    drugTabModel->setSort(drugTabModel->fieldIndex("DrugId"), Qt::AscendingOrder);     //排序
    if (!(drugTabModel->select()))     //查询数据
        return false;
    theDrugSelection = new QItemSelectionModel(drugTabModel);
    return true;
}

int IDatabase::addNewDrug()
{
    drugTabModel->insertRow(drugTabModel->rowCount(), QModelIndex());
    QModelIndex curIndex = drugTabModel->index(drugTabModel->rowCount() - 1, 1);
    int curRecNo = curIndex.row();
    QSqlRecord curRec = drugTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    drugTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchDrug(QString filter)
{
    drugTabModel->setFilter(filter);
    return drugTabModel->select();
}

void IDatabase::deleteCurrentDrug()
{
    QModelIndex curIndex = theDrugSelection->currentIndex();     //获取当前选择单元格的模型索引
    drugTabModel->removeRow(curIndex.row());
    drugTabModel->submitAll();
    drugTabModel->select();
}

bool IDatabase::submitDrugEdit()
{
    return drugTabModel->submitAll();
}

void IDatabase::revertDrugEdit()
{
    drugTabModel->revertAll();
}

bool IDatabase::initTreatRecordModel()
{
    TreatRecordTabModel = new QSqlTableModel(this, database);
    TreatRecordTabModel->setTable("record");
    TreatRecordTabModel->setEditStrategy(
        QSqlTableModel::OnManualSubmit);     //数据保存方式，OnManualSubmit，OnRowChange
    TreatRecordTabModel->setSort(TreatRecordTabModel->fieldIndex("RecordId"), Qt::AscendingOrder);     //排序
    if (!(TreatRecordTabModel->select()))     //查询数据
        return false;
    theTreatRecordSelection = new QItemSelectionModel(drugTabModel);
    return true;
}

int IDatabase::addNewTreatRecord()
{
    TreatRecordTabModel->insertRow(TreatRecordTabModel->rowCount(), QModelIndex());
    QModelIndex curIndex = TreatRecordTabModel->index(TreatRecordTabModel->rowCount() - 1, 1);
    int curRecNo = curIndex.row();
    QSqlRecord curRec = TreatRecordTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    TreatRecordTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchTreatRecord(QString filter)
{
    TreatRecordTabModel->setFilter(filter);
    return TreatRecordTabModel->select();
}

void IDatabase::deleteCurrentTreatRecord()
{
    QModelIndex curIndex = theTreatRecordSelection->currentIndex();     //获取当前选择单元格的模型索引
    TreatRecordTabModel->removeRow(curIndex.row());
    TreatRecordTabModel->submitAll();
    TreatRecordTabModel->select();
}

bool IDatabase::submitTreatRecordEdit()
{
    return TreatRecordTabModel->submitAll();
}

void IDatabase::revertTreatRecordEdit()
{
    TreatRecordTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER", userName);
    query.exec();
    if (query.first() && query.value("username").isValid()) {
        QString passwd = query.value("password").toString();
        if (passwd == password) {
            qDebug() << "login ok";
            return "loginOk";
        } else {
            qDebug() << "wrong password";
            return "wrongPassword";
        }
    } else {
        qDebug() << "no such user";
        return "wrongUsername";
    }
}

IDatabase::IDatabase(QObject *parent) : QObject{parent}
{
    ininDatabase();
}
