#ifndef TREATRECORDEDITVIEW_H
#define TREATRECORDEDITVIEW_H

#include <QDialog>

namespace Ui {
class TreatRecordEditView;
}

class TreatRecordEditView : public QDialog
{
    Q_OBJECT

public:
    explicit TreatRecordEditView(QWidget *parent = nullptr);
    ~TreatRecordEditView();

private:
    Ui::TreatRecordEditView *ui;
};

#endif // TREATRECORDEDITVIEW_H
