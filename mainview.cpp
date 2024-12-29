#include "mainview.h"
#include "ui_mainview.h"
#include "doctoreditview.h"
#include "patienteditview.h"
#include "drugeditview.h"

mainview::mainview(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainview)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
}

mainview::~mainview()
{
    delete ui;
}

//调整QTabBar中标签的尺寸，使得标签可以竖直显示
QSize CustomTabStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size,
                                       const QWidget *widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab) {
        s = s.transposed();     // 交换宽度和高度，以适应竖直排列的标签
        s.rwidth() = 100;
        s.rheight() = 50;
    }
    return s;
}

//自定义QTabBar标签的绘制方式
void CustomTabStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                                 const QWidget *widget) const
{
    if (element == CE_TabBarTabLabel) {
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
            QRect allRect = tab->rect;
            if (tab->state & QStyle::State_Selected) {
                painter->save();
                painter->setPen(0x89cfff);
                painter->setBrush(QBrush(0x89cfff));
                painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                painter->restore();
            }
            QTextOption option;
            option.setAlignment(Qt::AlignCenter);
            if (tab->state & QStyle::State_Selected) {
                painter->setPen(0xf8fcff);
            } else {
                painter->setPen(0x000001);
            }
            painter->drawText(allRect, tab->text, option);
            return ;
        }
    }
    if (element == CE_TabBarTab) {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}

void mainview::on_ActionDoctorcomboBox_activated(int index)
{
    index = ui->ActionDoctorcomboBox->currentIndex();
    if (index == 0) {
        DoctorEditView *view = new DoctorEditView;
        view->show();
    } else if (index == 1) {

    } else if (index == 2) {

    } else if (index == 3) {

    } else {

    }
}


void mainview::on_ActionPatientcomboBox_activated(int index)
{
    index = ui->ActionPatientcomboBox->currentIndex();
    if (index == 0) {
        PatientEditView *view = new PatientEditView;
        view->show();
    } else if (index == 1) {

    } else if (index == 2) {

    } else if (index == 3) {

    } else {

    }
}


void mainview::on_ActionDrugcomboBox_activated(int index)
{
    index = ui->ActionPatientcomboBox->currentIndex();
    if (index == 0) {
        DrugEditView *view = new DrugEditView;
        view->show();
    } else if (index == 1) {

    } else if (index == 2) {

    } else if (index == 3) {

    } else {

    }
}

