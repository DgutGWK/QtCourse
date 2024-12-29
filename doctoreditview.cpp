#include "doctoreditview.h"
#include "ui_doctoreditview.h"

DoctorEditView::DoctorEditView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DoctorEditView)
{
    ui->setupUi(this);
}

DoctorEditView::~DoctorEditView()
{
    delete ui;
}
