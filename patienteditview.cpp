#include "patienteditview.h"
#include "ui_patienteditview.h"
#include <QSqlTableModel>
#include "idatabase.h"

PatientEditView::PatientEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabmodel=IDatabase::getInstance().patientTabModel;
    dataMapper->setModel(IDatabase::getInstance().patientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->lineID,tabmodel->fieldIndex("ID"));
    dataMapper->addMapping(ui->lineName,tabmodel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->lineNo,tabmodel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->spHeight,tabmodel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->spWeight,tabmodel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->linePhone,tabmodel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dateEditBD,tabmodel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->cbSex,tabmodel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dateEditTime,tabmodel->fieldIndex("CREATEDTIMESTAMP"));
    dataMapper->setCurrentIndex(index);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

//保存操作
void PatientEditView::on_btSave_clicked()
{
    IDatabase::getInstance().submitPatientEdit();
    emit goPreviousView(); //回到之前页面
}

//取消操作
void PatientEditView::on_btCancel_clicked()
{
    IDatabase::getInstance().revertPatientEdit();
}

