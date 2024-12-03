#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QDataWidgetMapper>
#include <QWidget>

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientEditView(QWidget *parent = nullptr,int index=0);
    ~PatientEditView();

private slots:
    void on_btSave_clicked();

    void on_btCancel_clicked();

private:
    Ui::PatientEditView *ui;
    QDataWidgetMapper *dataMapper;  //数据映射

signals:
    void goPreviousView();//返回前一页面
};

#endif // PATIENTEDITVIEW_H
