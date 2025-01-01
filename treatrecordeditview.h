#ifndef TREATRECORDEDITVIEW_H
#define TREATRECORDEDITVIEW_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class TreatRecordEditView;
}

class TreatRecordEditView : public QDialog
{
    Q_OBJECT

public:
    explicit TreatRecordEditView(QWidget *parent = nullptr, int index = 0);
    ~TreatRecordEditView();

private slots:
    void on_btSaveTreatRecordMessage_clicked();

    void on_btCancelTreatRecordMessage_clicked();

signals:
    void goPreviousView();

private:
    Ui::TreatRecordEditView *ui;
    QDataWidgetMapper *dataMapper;     //数据映射
};

#endif // TREATRECORDEDITVIEW_H
