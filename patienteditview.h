#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QDialog>

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QDialog
{
    Q_OBJECT

public:
    explicit PatientEditView(QWidget *parent = nullptr);
    ~PatientEditView();

private:
    Ui::PatientEditView *ui;
};

#endif // PATIENTEDITVIEW_H
