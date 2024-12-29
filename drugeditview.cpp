#include "drugeditview.h"
#include "ui_drugeditview.h"

DrugEditView::DrugEditView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DrugEditView)
{
    ui->setupUi(this);
}

DrugEditView::~DrugEditView()
{
    delete ui;
}
