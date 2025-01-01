#ifndef DRUGEDITVIEW_H
#define DRUGEDITVIEW_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class DrugEditView;
}

class DrugEditView : public QDialog
{
    Q_OBJECT

public:
    explicit DrugEditView(QWidget *parent = nullptr, int index = 0);
    ~DrugEditView();

private slots:

    void on_btSaveDrugMessage_clicked();

    void on_btCancelDrugMessage_clicked();

signals:
    void goPreviousView();

private:
    Ui::DrugEditView *ui;
    QDataWidgetMapper *dataMapper;     //数据映射
};

#endif // DRUGEDITVIEW_H
