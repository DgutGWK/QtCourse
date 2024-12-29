#include "treatrecordeditview.h"
#include "ui_treatrecordeditview.h"

TreatRecordEditView::TreatRecordEditView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TreatRecordEditView)
{
    ui->setupUi(this);
}

TreatRecordEditView::~TreatRecordEditView()
{
    delete ui;
}
