#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QDialog>

namespace Ui {
class DoctorEditView;
}

class DoctorEditView : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorEditView(QWidget *parent = nullptr);
    ~DoctorEditView();

private:
    Ui::DoctorEditView *ui;
};

#endif // DOCTOREDITVIEW_H
