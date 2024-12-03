#include "idatabase.h"
#include <QUuid>

//连接数据库
void IDatabase::ininDatabase()
{
    //打开数据库
    database=QSqlDatabase::addDatabase("QSQLITE");//添加数据库驱动;
    QString aFile="D:/2024年秋/QT/实验报告/lab4.db";
    database.setDatabaseName(aFile);
    if(!database.open())    //打开数据库
    {
        qDebug()<<"数据库打开失败";
    }
    else
        qDebug()<<"成功打开数据库";
}

bool IDatabase::initPatientModel()
{
    patientTabModel=new QSqlTableModel(this,database);
    patientTabModel->setTable("patient");   //关联表
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);   //数据保存方式
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);//排序
    if(!(patientTabModel->select()))    //查询数据
        return false;
    thePatientSelection=new QItemSelectionModel(patientTabModel);
    return true;
}

int IDatabase::addNwePatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());  //在末尾添加一个记录
    QModelIndex curIndex=patientTabModel->index(patientTabModel->rowCount()-1,1); //创建最后一行的modelindex
    int curRecNo=curIndex.row();
    QSqlRecord curRec=patientTabModel->record(curRecNo);//获取当前记录
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM--dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));   //自动加id
    patientTabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex=thePatientSelection->currentIndex();   //获取当前选择单元格的模型索引
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    return patientTabModel->revertAll();
}
//实现登录控制
QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password from User where username=:USER");
    query.bindValue(":USER",userName);
    query.exec();
    if(query.first()&&query.value("username").isValid()){
        QString passwd=query.value("password").toString();
        if(passwd==password){
            qDebug()<<"Welcome";
            return "loginOK";
        }
        else{
            qDebug()<<"error password";
            return "wrongPassword";
        }
    }
    else{
        qDebug()<<"no such user";
        return "wrongUsername";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
