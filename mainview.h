#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QPainter>

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

private slots:
    void on_backButton_clicked();

    void on_SearchDoctorButton_clicked();

signals:
    void backSuccess();
    void goDoctorEditView(int idx);

private:
    Ui::mainview *ui;
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
