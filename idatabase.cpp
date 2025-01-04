#include "idatabase.h"
#include "qapplication.h"

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

void IDatabase::exportDoctorMessage()
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM doctor")) {
        qDebug() << "Database query failed:" << query.lastError();
        return;
    }

    QXlsx::Document xlsx;
    int row = 1;

    // 添加列标题
    xlsx.write(row, 1, "Id");
    xlsx.write(row, 2, "DoctorName");
    xlsx.write(row, 3, "Sex");
    xlsx.write(row, 4, "Ration");
    xlsx.write(row, 5, "EntryTime");
    xlsx.write(row, 6, "Born");
    xlsx.write(row, 7, "Age");
    xlsx.write(row, 8, "EducationBackground");
    xlsx.write(row, 9, "MaritalStatus");
    xlsx.write(row, 10, "Height");
    xlsx.write(row, 11, "Weight");
    xlsx.write(row, 12, "JobId");
    xlsx.write(row, 13, "Department");
    xlsx.write(row, 14, "JobIdentity");
    xlsx.write(row, 15, "CertificateType");
    xlsx.write(row, 16, "CertificateNumber");
    xlsx.write(row, 17, "NativePlace");
    xlsx.write(row, 18, "Place");
    xlsx.write(row, 19, "Phone");
    xlsx.write(row, 20, "Email");
    xlsx.write(row, 21, "PractiseCertificate");
    row++;

    while (query.next()) {
        int Id = query.value(0).toInt();
        QString DoctorName = query.value(1).toString();
        QString Sex = query.value(2).toString();
        QString Ration = query.value(3).toString();
        QString EntryTime = query.value(4).toString();
        QString Born = query.value(5).toString();
        int Age = query.value(6).toInt();
        QString EducationBackground = query.value(7).toString();
        QString MaritalStatus = query.value(8).toString();
        double Height = query.value(9).toDouble();
        double Weight = query.value(10).toDouble();
        QString JobId = query.value(11).toString();
        QString Department = query.value(12).toString();
        QString JobIdentity = query.value(13).toString();
        QString CertificateType = query.value(14).toString();
        QString CertificateNumber = query.value(15).toString();
        QString NativePlace = query.value(16).toString();
        QString Place = query.value(17).toString();
        QString Phone = query.value(18).toString();
        QString Email = query.value(19).toString();
        QString PractiseCertificate = query.value(20).toString();

        xlsx.write(row, 1, Id);
        xlsx.write(row, 2, DoctorName);
        xlsx.write(row, 3, Sex);
        xlsx.write(row, 4, Ration);
        xlsx.write(row, 5, EntryTime);
        xlsx.write(row, 6, Born);
        xlsx.write(row, 7, Age);
        xlsx.write(row, 8, EducationBackground);
        xlsx.write(row, 9, MaritalStatus);
        xlsx.write(row, 10, Height);
        xlsx.write(row, 11, Weight);
        xlsx.write(row, 12, JobId);
        xlsx.write(row, 13, Department);
        xlsx.write(row, 14, JobIdentity);
        xlsx.write(row, 15, CertificateType);
        xlsx.write(row, 16, CertificateNumber);
        xlsx.write(row, 17, NativePlace);
        xlsx.write(row, 18, Place);
        xlsx.write(row, 19, Phone);
        xlsx.write(row, 20, Email);
        xlsx.write(row, 21, PractiseCertificate);
        row++;
    }

    QApplication::setQuitOnLastWindowClosed(false);
    // 弹出选择文件保存路径的对话框
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Excel File", "", "Excel Files (*.xlsx)");
    if (fileName.isEmpty()) {
        // 用户取消操作，不执行任何操作
        QApplication::setQuitOnLastWindowClosed(false);
    } else {
        if (!xlsx.saveAs(fileName)) {
            qDebug() << "Failed to save Excel file.";
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::warning(nullptr, "Warning", "Failed to save Excel file.");
        } else {
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::information(nullptr, "Success", "Export successful.");
        }
    }
}

void IDatabase::importDoctorMessage()
{
    QApplication::setQuitOnLastWindowClosed(false);
    // 弹出选择文件打开路径的对话框
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open Excel File", "", "Excel Files (*.xlsx)");
    if (fileName.isEmpty()) {
        // 用户取消操作，不执行任何操作
        QApplication::setQuitOnLastWindowClosed(false);
        return;
    }

    QXlsx::Document xlsx(fileName);
    bool importSuccess = true; // 假设导入成功，除非遇到错误

    // 读取Excel文件并导入数据
    try {
        int row = 2; // 假设第一行是标题行，从第二行开始读取数据
        QSqlQuery query;

        // 准备插入语句，这里需要根据您的数据库表结构来编写
        query.prepare("INSERT INTO doctor (Id, DoctorName, Sex) VALUES (:Id, :DoctorName, :Sex)");

        while (xlsx.dimension().rowCount() >= row) {
            QString Id = xlsx.read(row, 1).toString();
            QString DoctorName = xlsx.read(row, 2).toString();
            QString Sex = xlsx.read(row, 3).toString();

            query.bindValue(":Id", Id);
            query.bindValue(":DoctorName", DoctorName);
            query.bindValue(":Sex", Sex);

            if (!query.exec()) {
                qDebug() << "Database query failed:" << query.lastError();
                importSuccess = false;
                break; // 遇到错误时停止导入
            }
            row++;
        }
    } catch (const std::exception& e) {
        qDebug() << "Error reading Excel file:" << e.what();
        importSuccess = false;
    }

    // 根据导入结果显示提示信息
    if (importSuccess) {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::information(nullptr, "Success", "Import successful.");
    } else {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::warning(nullptr, "Warning", "Failed to import Excel file.");
    }
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

void IDatabase::exportPatientMessage()
{
    QApplication::setQuitOnLastWindowClosed(false);
    QSqlQuery query;
    if (!query.exec("SELECT * FROM patient")) {
        qDebug() << "Database query failed:" << query.lastError();
        return;
    }

    QXlsx::Document xlsx;
    int row = 1;

    // 添加列标题
    xlsx.write(row, 1, "Id");
    xlsx.write(row, 2, "PatientName");
    xlsx.write(row, 3, "Sex");
    xlsx.write(row, 4, "Ration");
    xlsx.write(row, 5, "Height");
    xlsx.write(row, 6, "Weight");
    xlsx.write(row, 7, "Born");
    xlsx.write(row, 8, "Age");
    xlsx.write(row, 9, "CertificateType");
    xlsx.write(row, 10, "CertificateNumber");
    xlsx.write(row, 11, "NativePlace");
    xlsx.write(row, 12, "Place");
    xlsx.write(row, 13, "Phone");
    xlsx.write(row, 14, "Email");
    row++;

    while (query.next()) {
        int Id = query.value(0).toInt();
        QString PatientName = query.value(1).toString();
        QString Sex = query.value(2).toString();
        QString Ration = query.value(3).toString();
        double Height = query.value(4).toDouble();
        double Weight = query.value(5).toDouble();
        QString Born = query.value(6).toString();
        int Age = query.value(7).toInt();
        QString CertificateType = query.value(8).toString();
        QString CertificateNumber = query.value(9).toString();
        QString NativePlace = query.value(10).toString();
        QString Place = query.value(11).toString();
        QString Phone = query.value(12).toString();
        QString Email = query.value(13).toString();

        xlsx.write(row, 1, Id);
        xlsx.write(row, 2, PatientName);
        xlsx.write(row, 3, Sex);
        xlsx.write(row, 4, Ration);
        xlsx.write(row, 5, Height);
        xlsx.write(row, 6, Weight);
        xlsx.write(row, 7, Born);
        xlsx.write(row, 8, Age);
        xlsx.write(row, 9, CertificateType);
        xlsx.write(row, 10, CertificateNumber);
        xlsx.write(row, 11, NativePlace);
        xlsx.write(row, 12, Place);
        xlsx.write(row, 13, Phone);
        xlsx.write(row, 14, Email);
        row++;
    }

    // 弹出选择文件保存路径的对话框
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Excel File", "", "Excel Files (*.xlsx)");
    if (fileName.isEmpty()) {
        // 用户取消操作，不执行任何操作
        QApplication::setQuitOnLastWindowClosed(false);
    } else {
        if (!xlsx.saveAs(fileName)) {
            qDebug() << "Failed to save Excel file.";
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::warning(nullptr, "Warning", "Failed to save Excel file.");
        } else {
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::information(nullptr, "Success", "Export successful.");
        }
    }
}

void IDatabase::importPatientMessage()
{
    QApplication::setQuitOnLastWindowClosed(false);
    // 弹出选择文件打开路径的对话框
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open Excel File", "", "Excel Files (*.xlsx)");
    if (fileName.isEmpty()) {
        // 用户取消操作，不执行任何操作
        QApplication::setQuitOnLastWindowClosed(false);
        return;
    }

    QXlsx::Document xlsx(fileName);
    bool importSuccess = true; // 假设导入成功，除非遇到错误

    // 读取Excel文件并导入数据
    try {
        int row = 2; // 假设第一行是标题行，从第二行开始读取数据
        QSqlQuery query;

        // 准备插入语句，这里需要根据您的数据库表结构来编写
        query.prepare("INSERT INTO patient (Id, PatientName, Sex) VALUES (:Id, :PatientName, :Sex)");

        while (xlsx.dimension().rowCount() >= row) {
            QString Id = xlsx.read(row, 1).toString();
            QString PatientName = xlsx.read(row, 2).toString();
            QString Sex = xlsx.read(row, 3).toString();

            query.bindValue(":Id", Id);
            query.bindValue(":PatientName", PatientName);
            query.bindValue(":Sex", Sex);

            if (!query.exec()) {
                qDebug() << "Database query failed:" << query.lastError();
                importSuccess = false;
                break; // 遇到错误时停止导入
            }
            row++;
        }
    } catch (const std::exception& e) {
        qDebug() << "Error reading Excel file:" << e.what();
        importSuccess = false;
    }

    // 根据导入结果显示提示信息
    if (importSuccess) {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::information(nullptr, "Success", "Import successful.");
    } else {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::warning(nullptr, "Warning", "Failed to import Excel file.");
    }
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

void IDatabase::exportDrugMessage()
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM drug")) {
        qDebug() << "Database query failed:" << query.lastError();
        return;
    }

    QXlsx::Document xlsx;
    int row = 1;

    // 添加列标题
    xlsx.write(row, 1, "DrugId");
    xlsx.write(row, 2, "DrugName");
    xlsx.write(row, 3, "Dosage");
    xlsx.write(row, 4, "InventoryNumber");
    xlsx.write(row, 5, "DeliveryNumber");
    xlsx.write(row, 6, "ManufactureDate");
    xlsx.write(row, 7, "ExpirationDate");
    xlsx.write(row, 8, "EntryTime");
    xlsx.write(row, 9, "DeliveryTime");
    row++;

    while (query.next()) {
        QString DrugId = query.value(0).toString();
        QString DrugName = query.value(1).toString();
        QString Dosage = query.value(2).toString();
        QString InventoryNumber = query.value(3).toString();
        QString DeliveryNumber = query.value(4).toString();
        QString ManufactureDate = query.value(5).toString();
        QString ExpirationDate = query.value(6).toString();
        QString EntryTime = query.value(7).toString();
        QString DeliveryTime = query.value(8).toString();

        xlsx.write(row, 1, DrugId);
        xlsx.write(row, 2, DrugName);
        xlsx.write(row, 3, Dosage);
        xlsx.write(row, 4, InventoryNumber);
        xlsx.write(row, 5, DeliveryNumber);
        xlsx.write(row, 6, ManufactureDate);
        xlsx.write(row, 7, ExpirationDate);
        xlsx.write(row, 8, EntryTime);
        xlsx.write(row, 9, DeliveryTime);
        row++;
    }

    QApplication::setQuitOnLastWindowClosed(false);
    // 弹出选择文件保存路径的对话框
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Excel File", "", "Excel Files (*.xlsx)");
    if (fileName.isEmpty()) {
        // 用户取消操作，不执行任何操作
        QApplication::setQuitOnLastWindowClosed(false);
    } else {
        if (!xlsx.saveAs(fileName)) {
            qDebug() << "Failed to save Excel file.";
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::warning(nullptr, "Warning", "Failed to save Excel file.");
        } else {
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::information(nullptr, "Success", "Export successful.");
        }
    }
}

void IDatabase::importDrugMessage()
{
    QApplication::setQuitOnLastWindowClosed(false);
    // 弹出选择文件打开路径的对话框
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open Excel File", "", "Excel Files (*.xlsx)");
    if (fileName.isEmpty()) {
        // 用户取消操作，不执行任何操作
        QApplication::setQuitOnLastWindowClosed(false);
        return;
    }

    QXlsx::Document xlsx(fileName);
    bool importSuccess = true; // 假设导入成功，除非遇到错误

    // 读取Excel文件并导入数据
    try {
        int row = 2; // 假设第一行是标题行，从第二行开始读取数据
        QSqlQuery query;

        // 准备插入语句，这里需要根据您的数据库表结构来编写
        query.prepare("INSERT INTO patient (DrugId, DrugName) VALUES (:DrugId, :DrugName)");

        while (xlsx.dimension().rowCount() >= row) {
            QString DrugId = xlsx.read(row, 1).toString();
            QString DrugName = xlsx.read(row, 2).toString();

            query.bindValue(":DrugId", DrugId);
            query.bindValue(":DrugName", DrugName);

            if (!query.exec()) {
                qDebug() << "Database query failed:" << query.lastError();
                importSuccess = false;
                break; // 遇到错误时停止导入
            }
            row++;
        }
    } catch (const std::exception& e) {
        qDebug() << "Error reading Excel file:" << e.what();
        importSuccess = false;
    }

    // 根据导入结果显示提示信息
    if (importSuccess) {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::information(nullptr, "Success", "Import successful.");
    } else {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::warning(nullptr, "Warning", "Failed to import Excel file.");
    }
}

void IDatabase::showLowStockDrugs()
{
    int lowStockThreshold = 10;
    QString queryText = "SELECT DrugName, InventoryNumber FROM drug WHERE InventoryNumber < :threshold";

    QSqlQuery query;
    query.prepare(queryText);
    query.bindValue(":threshold", lowStockThreshold);

    if (query.exec()) {
        QStringList lowStockDrugs;
        while (query.next()) {
            QString drugName = query.value("DrugName").toString();
            int inventoryNumber = query.value("InventoryNumber").toInt();
            lowStockDrugs.append(QString("%1 - 库存数量: %2").arg(drugName).arg(inventoryNumber));
        }

        if (!lowStockDrugs.isEmpty()) {
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::information(nullptr, "库存预警", "以下药品库存低于阈值:\n" + lowStockDrugs.join("\n"));
        } else {
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::information(nullptr, "库存预警", "所有药品库存正常.");
        }
    } else {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::critical(nullptr, "查询失败", "无法查询药品库存信息.");
    }
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
    theTreatRecordSelection = new QItemSelectionModel(TreatRecordTabModel);
    return true;
}

int IDatabase::addNewTreatRecord()
{
    TreatRecordTabModel->insertRow(TreatRecordTabModel->rowCount(), QModelIndex());
    QModelIndex curIndex = TreatRecordTabModel->index(TreatRecordTabModel->rowCount() - 1, 1);
    int curRecNo = curIndex.row();
    QSqlRecord curRec = TreatRecordTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("RecordId", QUuid::createUuid().toString(QUuid::WithoutBraces));
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

void IDatabase::exportTreatRecordMessage()
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM record")) {
        qDebug() << "Database query failed:" << query.lastError();
        return;
    }

    QXlsx::Document xlsx;
    int row = 1;

    // 添加列标题
    xlsx.write(row, 1, "RecordId");
    xlsx.write(row, 2, "DoctorName");
    xlsx.write(row, 3, "PatientName");
    xlsx.write(row, 4, "TreatDate");
    xlsx.write(row, 5, "TreatResult");
    xlsx.write(row, 6, "PrescribeDrug");
    row++;

    while (query.next()) {
        int RecordId = query.value(0).toInt();
        QString DoctorName = query.value(1).toString();
        QString PatientName = query.value(2).toString();
        QString TreatDate = query.value(0).toString();
        QString TreatResult = query.value(1).toString();
        QString PrescribeDrug = query.value(2).toString();

        xlsx.write(row, 1, RecordId);
        xlsx.write(row, 2, DoctorName);
        xlsx.write(row, 3, PatientName);
        xlsx.write(row, 4, TreatDate);
        xlsx.write(row, 5, TreatResult);
        xlsx.write(row, 6, PrescribeDrug);
        row++;
    }

    QApplication::setQuitOnLastWindowClosed(false);
    // 弹出选择文件保存路径的对话框
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Excel File", "", "Excel Files (*.xlsx)");
    if (fileName.isEmpty()) {
        // 用户取消操作，不执行任何操作
        QApplication::setQuitOnLastWindowClosed(false);
    } else {
        if (!xlsx.saveAs(fileName)) {
            qDebug() << "Failed to save Excel file.";
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::warning(nullptr, "Warning", "Failed to save Excel file.");
        } else {
            QApplication::setQuitOnLastWindowClosed(false);
            QMessageBox::information(nullptr, "Success", "Export successful.");
        }
    }
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
