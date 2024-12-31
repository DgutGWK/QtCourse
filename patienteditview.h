#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QDialog
{
    Q_OBJECT

public:
    explicit PatientEditView(QWidget *parent = nullptr, int index = 0);
    ~PatientEditView();

private slots:
    void on_btSavePatientMessage_clicked();

    void on_btCancelPatientMessage_clicked();

signals:
    void goPreviousView();

private:
    Ui::PatientEditView *ui;
    QDataWidgetMapper *dataMapper;
};

#endif // PATIENTEDITVIEW_H
