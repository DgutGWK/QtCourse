#include "mainview.h"
#include "ui_mainview.h"
#include "idatabase.h"

mainview::mainview(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainview)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);

    ui->DoctorMessageView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->DoctorMessageView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->DoctorMessageView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->DoctorMessageView->setAlternatingRowColors(true);

    ui->PatientMessageView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->PatientMessageView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->PatientMessageView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->PatientMessageView->setAlternatingRowColors(true);

    ui->DrugMessageView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->DrugMessageView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->DrugMessageView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->DrugMessageView->setAlternatingRowColors(true);

    ui->TreatRecordMessageView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TreatRecordMessageView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TreatRecordMessageView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TreatRecordMessageView->setAlternatingRowColors(true);

    connect(this, SIGNAL(goDoctorEditViewSuccess(int)), this, SLOT(goDoctorEditView(int)));
    connect(this, SIGNAL(goPatientEditViewSuccess(int)), this, SLOT(goPatientEditView(int)));
    connect(this, SIGNAL(goDrugEditViewSuccess(int)), this, SLOT(goDrugEditView(int)));
    connect(this, SIGNAL(goTreatRecordEditViewSuccess(int)), this, SLOT(goTreatRecordEditView(int)));
}

mainview::~mainview()
{
    delete ui;
}

//调整QTabBar中标签的尺寸，使得标签可以竖直显示
QSize CustomTabStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size,
                                       const QWidget *widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab) {
        s = s.transposed();     // 交换宽度和高度，以适应竖直排列的标签
        s.rwidth() = 100;
        s.rheight() = 50;
    }
    return s;
}

//自定义QTabBar标签的绘制方式
void CustomTabStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                                 const QWidget *widget) const
{
    if (element == CE_TabBarTabLabel) {
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
            QRect allRect = tab->rect;
            if (tab->state & QStyle::State_Selected) {
                painter->save();
                painter->setPen(0x89cfff);
                painter->setBrush(QBrush(0x89cfff));
                painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                painter->restore();
            }
            QTextOption option;
            option.setAlignment(Qt::AlignCenter);
            if (tab->state & QStyle::State_Selected) {
                painter->setPen(0xf8fcff);
            } else {
                painter->setPen(0x000001);
            }
            painter->drawText(allRect, tab->text, option);
            return ;
        }
    }
    if (element == CE_TabBarTab) {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}

void mainview::on_ActionDoctorcomboBox_activated(int index)
{
    index = ui->ActionDoctorcomboBox->currentIndex();
    if (index == 0) {
        int currow = IDatabase::getInstance().addNewDoctor();
        emit goDoctorEditViewSuccess(currow);
    } else if (index == 1) {
        QModelIndex curIndex = IDatabase::getInstance().theDoctorSelection->currentIndex();
        emit goDoctorEditView(curIndex.row());
    } else if (index == 2) {
        IDatabase::getInstance().deleteCurrentDoctor();
    } else if (index == 3) {
        IDatabase::getInstance().importDoctorMessage();
    } else {
        IDatabase::getInstance().exportDoctorMessage();
    }
}


void mainview::on_ActionPatientcomboBox_activated(int index)
{
    index = ui->ActionPatientcomboBox->currentIndex();
    if (index == 0) {
        int currow = IDatabase::getInstance().addNewPatient();
        emit goPatientEditViewSuccess(currow);
    } else if (index == 1) {
        QModelIndex curIndex = IDatabase::getInstance().thePatientSelection->currentIndex();
        emit goPatientEditView(curIndex.row());
    } else if (index == 2) {
        IDatabase::getInstance().deleteCurrentPatient();
    } else if (index == 3) {
        IDatabase::getInstance().importPatientMessage();
    } else {
        IDatabase::getInstance().exportPatientMessage();
    }
}


void mainview::on_ActionDrugcomboBox_activated(int index)
{
    index = ui->ActionDrugcomboBox->currentIndex();
    if (index == 0) {
        int currow = IDatabase::getInstance().addNewDrug();
        emit goDrugEditViewSuccess(currow);
    } else if (index == 1) {
        QModelIndex curIndex = IDatabase::getInstance().theDrugSelection->currentIndex();
        emit goDrugEditView(curIndex.row());
    } else if (index == 2) {
        IDatabase::getInstance().deleteCurrentDrug();
    } else if (index == 3) {
        IDatabase::getInstance().importDrugMessage();
    } else {
        IDatabase::getInstance().exportDrugMessage();
    }
}


void mainview::on_ActionTreatRecordcomboBox_activated(int index)
{
    index = ui->ActionTreatRecordcomboBox->currentIndex();
    if (index == 0) {
        int currow = IDatabase::getInstance().addNewTreatRecord();
        emit goTreatRecordEditViewSuccess(currow);
    } else if (index == 1) {
        QModelIndex curIndex = IDatabase::getInstance().theTreatRecordSelection->currentIndex();
        emit goTreatRecordEditView(curIndex.row());
    } else if (index == 2) {
        IDatabase::getInstance().deleteCurrentTreatRecord();
    } else {
        IDatabase::getInstance().exportTreatRecordMessage();
    }
}


void mainview::on_backButton_clicked()
{
    qDebug() << "BackSuccess";
    emit backSuccess();
    this->close();
}


void mainview::on_SearchDoctorButton_clicked()
{
    QString filter = QString("doctorname like '%%1%'").arg(ui->SearchDoctorEdit->text());
    IDatabase::getInstance().searchDoctor(filter);
}

void mainview::goDoctorEditView(int rowNo)
{
    qDebug() << "goDoctorEditView";
    doctorEditView = new DoctorEditView(this, rowNo);
    connect(doctorEditView, SIGNAL(goPreviousView()), this, SLOT(reshow()));
    doctorEditView->show();
}

void mainview::goPatientEditView(int rowNo)
{
    qDebug() << "goPatientEditView";
    patientEditView = new PatientEditView(this, rowNo);
    connect(patientEditView, SIGNAL(goPreviousView()), this, SLOT(reshow()));
    patientEditView->show();
}

void mainview::goDrugEditView(int rowNo)
{
    qDebug() << "goDrugEditView";
    drugEditView = new DrugEditView(this, rowNo);
    connect(drugEditView, SIGNAL(goPreviousView()), this, SLOT(reshow()));
    drugEditView->show();
}

void mainview::goTreatRecordEditView(int rowNo)
{
    qDebug() << "goTreatRecordEditView";
    treatRecordEditView = new TreatRecordEditView(this, rowNo);
    connect(treatRecordEditView, SIGNAL(goPreviousView()), this, SLOT(reshow()));
    treatRecordEditView->show();
}

void mainview::reshow()
{
    this->show();
}

void mainview::on_tabWidget_currentChanged(int index)
{
    IDatabase &iDatabase = IDatabase::getInstance();
    if (index == 0 && iDatabase.initDoctorModel()) {
        ui->DoctorMessageView->setModel(iDatabase.doctorTabModel);
        ui->DoctorMessageView->setSelectionModel(iDatabase.theDoctorSelection);
    } else if (index == 1 && iDatabase.initPatientModel()) {
        ui->PatientMessageView->setModel(iDatabase.patientTabModel);
        ui->PatientMessageView->setSelectionModel(iDatabase.thePatientSelection);
    } else if (index == 2 && iDatabase.initDrugModel()) {
        ui->DrugMessageView->setModel(iDatabase.drugTabModel);
        ui->DrugMessageView->setSelectionModel(iDatabase.theDrugSelection);
    } else if (index == 3 && iDatabase.initTreatRecordModel()) {
        ui->TreatRecordMessageView->setModel(iDatabase.TreatRecordTabModel);
        ui->TreatRecordMessageView->setSelectionModel(iDatabase.theTreatRecordSelection);
    }
}


void mainview::on_SortDoctorcomboBox_activated(int index)
{
    index = ui->SortDoctorcomboBox->currentIndex();
    ui->DoctorMessageView->setSortingEnabled(true);
    if (index == 0) {
        ui->DoctorMessageView->sortByColumn(IDatabase::getInstance().doctorTabModel->fieldIndex("Age"), Qt::AscendingOrder);
    } else if (index == 1) {
        ui->DoctorMessageView->sortByColumn(IDatabase::getInstance().doctorTabModel->fieldIndex("Age"), Qt::DescendingOrder);
    } else if (index == 2) {
        ui->DoctorMessageView->sortByColumn(IDatabase::getInstance().doctorTabModel->fieldIndex("Height"), Qt::AscendingOrder);
    } else if (index == 3) {
        ui->DoctorMessageView->sortByColumn(IDatabase::getInstance().doctorTabModel->fieldIndex("Height"), Qt::DescendingOrder);
    } else if (index == 4) {
        ui->DoctorMessageView->sortByColumn(IDatabase::getInstance().doctorTabModel->fieldIndex("Weight"), Qt::AscendingOrder);
    } else if (index == 5) {
        ui->DoctorMessageView->sortByColumn(IDatabase::getInstance().doctorTabModel->fieldIndex("Weight"), Qt::DescendingOrder);
    } else if (index == 6) {
        ui->DoctorMessageView->sortByColumn(IDatabase::getInstance().doctorTabModel->fieldIndex("EntryTime"),
                                            Qt::AscendingOrder);
    } else {
        ui->DoctorMessageView->sortByColumn(IDatabase::getInstance().doctorTabModel->fieldIndex("EntryTime"),
                                            Qt::DescendingOrder);
    }
}


void mainview::on_SortPatientcomboBox_activated(int index)
{
    index = ui->SortPatientcomboBox->currentIndex();
    ui->PatientMessageView->setSortingEnabled(true);
    if (index == 0) {
        ui->PatientMessageView->sortByColumn(IDatabase::getInstance().patientTabModel->fieldIndex("Age"), Qt::AscendingOrder);
    } else if (index == 1) {
        ui->PatientMessageView->sortByColumn(IDatabase::getInstance().patientTabModel->fieldIndex("Age"), Qt::DescendingOrder);
    } else if (index == 2) {
        ui->PatientMessageView->sortByColumn(IDatabase::getInstance().patientTabModel->fieldIndex("Height"),
                                             Qt::AscendingOrder);
    } else if (index == 3) {
        ui->PatientMessageView->sortByColumn(IDatabase::getInstance().patientTabModel->fieldIndex("Height"),
                                             Qt::DescendingOrder);
    } else if (index == 4) {
        ui->PatientMessageView->sortByColumn(IDatabase::getInstance().patientTabModel->fieldIndex("Weight"),
                                             Qt::AscendingOrder);
    } else {
        ui->PatientMessageView->sortByColumn(IDatabase::getInstance().patientTabModel->fieldIndex("Weight"),
                                             Qt::DescendingOrder);
    }
}


void mainview::on_SortDrugcomboBox_activated(int index)
{
    index = ui->SortDrugcomboBox->currentIndex();
    ui->DrugMessageView->setSortingEnabled(true);
    if (index == 0) {
        ui->DrugMessageView->sortByColumn(IDatabase::getInstance().drugTabModel->fieldIndex("InventoryNumber"),
                                          Qt::AscendingOrder);
    } else if (index == 1) {
        ui->DrugMessageView->sortByColumn(IDatabase::getInstance().drugTabModel->fieldIndex("InventoryNumber"),
                                          Qt::DescendingOrder);
    } else if (index == 2) {
        ui->DrugMessageView->sortByColumn(IDatabase::getInstance().drugTabModel->fieldIndex("ExpirationDate"),
                                          Qt::AscendingOrder);
    } else if (index == 3) {
        ui->DrugMessageView->sortByColumn(IDatabase::getInstance().drugTabModel->fieldIndex("ExpirationDate"),
                                          Qt::DescendingOrder);
    } else if (index == 4) {
        ui->DrugMessageView->sortByColumn(IDatabase::getInstance().drugTabModel->fieldIndex("EntryTime"), Qt::AscendingOrder);
    } else if (index == 5) {
        ui->DrugMessageView->sortByColumn(IDatabase::getInstance().drugTabModel->fieldIndex("EntryTime"), Qt::DescendingOrder);
    } else if (index == 6) {
        ui->DrugMessageView->sortByColumn(IDatabase::getInstance().drugTabModel->fieldIndex("DeliveryTime"),
                                          Qt::AscendingOrder);
    } else {
        ui->DrugMessageView->sortByColumn(IDatabase::getInstance().drugTabModel->fieldIndex("DeliveryTime"),
                                          Qt::DescendingOrder);
    }
}


void mainview::on_SortTreatRecordcomboBox_activated(int index)
{
    index = ui->SortTreatRecordcomboBox->currentIndex();
    ui->TreatRecordMessageView->setSortingEnabled(true);
    if (index == 0) {
        ui->TreatRecordMessageView->sortByColumn(IDatabase::getInstance().TreatRecordTabModel->fieldIndex("TreatDate"),
                Qt::AscendingOrder);
    } else {
        ui->TreatRecordMessageView->sortByColumn(IDatabase::getInstance().TreatRecordTabModel->fieldIndex("TreatDate"),
                Qt::DescendingOrder);
    }
}
