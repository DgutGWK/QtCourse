#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QPainter>
#include <QSqlQuery>
#include "doctoreditview.h"
#include "patienteditview.h"
#include "drugeditview.h"
#include "treatrecordeditview.h"

namespace Ui {
class mainview;
}

class mainview : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainview(QWidget *parent = nullptr);
    ~mainview();

private slots:
    void on_ActionDoctorcomboBox_activated(int index);

    void on_ActionPatientcomboBox_activated(int index);

    void on_ActionDrugcomboBox_activated(int index);

    void on_ActionTreatRecordcomboBox_activated(int index);

    void on_backButton_clicked();

    void on_SearchDoctorButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_SortDoctorcomboBox_activated(int index);

    void on_SortPatientcomboBox_activated(int index);

    void on_SortDrugcomboBox_activated(int index);

    void on_SortTreatRecordcomboBox_activated(int index);

    void on_FilterTreatRecordcomboBox_activated(int index);

    void on_SearchPatientButton_clicked();

    void on_SearchDrugButton_clicked();

    void on_SearchTreatRecordButton_clicked();

public slots:
    void goDoctorEditView(int rowNo);
    void goPatientEditView(int rowNo);
    void goDrugEditView(int rowNo);
    void goTreatRecordEditView(int rowNo);
    void reshow();

signals:
    void backSuccess();
    void goDoctorEditViewSuccess(int idx);
    void goPatientEditViewSuccess(int idx);
    void goDrugEditViewSuccess(int idx);
    void goTreatRecordEditViewSuccess(int idx);

private:
    Ui::mainview *ui;
    DoctorEditView *doctorEditView;
    PatientEditView *patientEditView;
    DrugEditView *drugEditView;
    TreatRecordEditView *treatRecordEditView;
};

//自定义tabbar的样式
class CustomTabStyle: public QProxyStyle
{

public:
    CustomTabStyle() {}
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
};

#endif // MAINVIEW_H
