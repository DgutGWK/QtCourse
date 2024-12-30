#include "patienteditview.h"
#include "ui_patienteditview.h"
#include <QSqlTableModel>

PatientEditView::PatientEditView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

}

PatientEditView::~PatientEditView()
{
    delete ui;
}
