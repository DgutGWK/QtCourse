#include "drugeditview.h"
#include "ui_drugeditview.h"
#include "idatabase.h"

DrugEditView::DrugEditView(QWidget *parent, int index)
    : QDialog(parent)
    , ui(new Ui::DrugEditView)
{
    ui->setupUi(this);

    // 创建数据映射器，用于将UI组件与数据库表模型字段关联
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().drugTabModel; // 获取数据库表模型实例
    dataMapper->setModel(IDatabase::getInstance().drugTabModel); // 设置数据映射器的模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); // 设置自动提交策略

    // 将UI组件与数据库表模型的字段进行映射
    dataMapper->addMapping(ui->DrugName, tabModel->fieldIndex("DrugName"));
    dataMapper->addMapping(ui->Dosage, tabModel->fieldIndex("Dosage"));
    dataMapper->addMapping(ui->InventoryNumber, tabModel->fieldIndex("InventoryNumber"));
    dataMapper->addMapping(ui->DeliveryNumber, tabModel->fieldIndex("DeliveryNumber"));
    dataMapper->addMapping(ui->ManufactureDate, tabModel->fieldIndex("ManufactureDate"));
    dataMapper->addMapping(ui->ExpirationDate, tabModel->fieldIndex("ExpirationDate"));
    dataMapper->addMapping(ui->EntryTime, tabModel->fieldIndex("EntryTime"));
    dataMapper->addMapping(ui->DeliveryTime, tabModel->fieldIndex("DeliveryTime"));
    // 设置当前索引，用于定位到特定的数据记录
    dataMapper->setCurrentIndex(index);
}

DrugEditView::~DrugEditView()
{
    delete ui;
}

void DrugEditView::on_btSaveDrugMessage_clicked()
{
    qDebug() << "goPreviousView";
    IDatabase::getInstance().submitDrugEdit();
    emit goPreviousView();
    this->close();
}


void DrugEditView::on_btCancelDrugMessage_clicked()
{
    qDebug() << "goPreviousView";
    IDatabase::getInstance().revertDrugEdit();
    emit goPreviousView();
    this->close();
}

