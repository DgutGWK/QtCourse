#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class DoctorEditView;
}

class DoctorEditView : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorEditView(QWidget *parent = nullptr, int index = 0);
    ~DoctorEditView();

private slots:
    void on_btSaveDoctorMessage_clicked();

    void on_btCancelDoctorMessage_clicked();

signals:
    void goPreviousView();

private:
    Ui::DoctorEditView *ui;
    QDataWidgetMapper *dataMapper;     //数据映射
};

#endif // DOCTOREDITVIEW_H
