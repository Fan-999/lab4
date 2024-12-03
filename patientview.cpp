#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"

PatientView::PatientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientView)
{
    ui->setupUi(this);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }
}

PatientView::~PatientView()
{
    delete ui;
}

//添加操作
void PatientView::on_btadd_clicked()
{
    int currow=IDatabase::getInstance().addNwePatient();
    emit goPatientEditView(currow);
}

//查找操作
void PatientView::on_btfind_clicked()
{
    QString filter=QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchPatient(filter);
}

//删除操作
void PatientView::on_btdelete_clicked()
{
    IDatabase::getInstance().deleteCurrentPatient();

}

//修改操作
void PatientView::on_btchange_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().thePatientSelection->currentIndex();  //获取当前选择单元格的行号

    emit goPatientEditView(curIndex.row());
}

