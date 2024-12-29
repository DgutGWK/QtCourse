#ifndef DRUGEDITVIEW_H
#define DRUGEDITVIEW_H

#include <QDialog>

namespace Ui {
class DrugEditView;
}

class DrugEditView : public QDialog
{
    Q_OBJECT

public:
    explicit DrugEditView(QWidget *parent = nullptr);
    ~DrugEditView();

private:
    Ui::DrugEditView *ui;
};

#endif // DRUGEDITVIEW_H
