#include "treatrecordeditview.h"
#include "ui_treatrecordeditview.h"
#include "idatabase.h"

TreatRecordEditView::TreatRecordEditView(QWidget *parent, int index)
    : QDialog(parent)
    , ui(new Ui::TreatRecordEditView)
{
    ui->setupUi(this);

    // 创建数据映射器，用于将UI组件与数据库表模型字段关联
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().TreatRecordTabModel; // 获取数据库表模型实例
    dataMapper->setModel(IDatabase::getInstance().TreatRecordTabModel); // 设置数据映射器的模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); // 设置自动提交策略

    // 将UI组件与数据库表模型的字段进行映射
    dataMapper->addMapping(ui->PatientName, tabModel->fieldIndex("PatientName"));
    dataMapper->addMapping(ui->DoctorName, tabModel->fieldIndex("DoctorName"));
    dataMapper->addMapping(ui->TreatDate, tabModel->fieldIndex("TreatDate"));
    dataMapper->addMapping(ui->TreatResult, tabModel->fieldIndex("TreatResult"));
    dataMapper->addMapping(ui->PrescribeDrug, tabModel->fieldIndex("PrescribeDrug"));
    // 设置当前索引，用于定位到特定的数据记录
    dataMapper->setCurrentIndex(index);
}

TreatRecordEditView::~TreatRecordEditView()
{
    delete ui;
}

void TreatRecordEditView::on_btSaveTreatRecordMessage_clicked()
{
    qDebug() << "goPreviousView";
    IDatabase::getInstance().submitTreatRecordEdit();
    emit goPreviousView();
    this->close();
}


void TreatRecordEditView::on_btCancelTreatRecordMessage_clicked()
{
    qDebug() << "goPreviousView";
    IDatabase::getInstance().revertTreatRecordEdit();
    emit goPreviousView();
    this->close();
}

