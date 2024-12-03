#include "masterview.h"
#include "ui_masterview.h"
#include "idatabase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    // this->setWindowFlag(Qt::FramelessWindowHint);
    goLoginView();

    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    // qDebug()<<"goLoginView";
    loginview=new LoginView(this);
    pushWidgetToStackView(loginview);

    connect(loginview,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));
}

void MasterView::goWelcomeView()
{
    welcomeview=new WelcomeView(this);
    pushWidgetToStackView(welcomeview);

    connect(welcomeview,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect(welcomeview,SIGNAL(goPatientView()),this,SLOT(goPatientView()));
    connect(welcomeview,SIGNAL(goDepartmentView()),this,SLOT(goDepartmentView()));
}

void MasterView::goDoctorView()
{
    doctorview=new DoctorView(this);
    pushWidgetToStackView(doctorview);
}

void MasterView::goDepartmentView()
{
    departmentview=new DepartmentView(this);
    pushWidgetToStackView(departmentview);
}

void MasterView::goPatientView()
{
    patientview=new PatientView(this);
    pushWidgetToStackView(patientview);

    connect(patientview,SIGNAL(goPatientEditView(int)),this,SLOT(goPatientEditView(int)));
}

void MasterView::goPatientEditView(int rowNo)
{
    patientEditView=new PatientEditView(this,rowNo);
    pushWidgetToStackView(patientEditView);

    connect(patientEditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}


void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count=ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);    //总是显示最新加入的view
    ui->labeltitle->setText(widget->windowTitle());
}

void MasterView::goPreviousView()
{
    int count=ui->stackedWidget->count();
    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->labeltitle->setText(ui->stackedWidget->currentWidget()->windowTitle());
        QWidget *widget=ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterView::on_btBlack_clicked()
{
    goPreviousView();
}

void MasterView::on_btLogout_clicked()
{
    loginview=new LoginView(this);
    pushWidgetToStackView(loginview);
    connect(loginview,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));
}

void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count=ui->stackedWidget->count();
    if(count>1)
        ui->btBlack->setEnabled(true);
    else
        ui->btBlack->setEnabled(false);
    //先获取当前页面的windowtitle
    QString title=ui->stackedWidget->currentWidget()->windowTitle();
    if(title=="欢迎"){
        // ui->btLogout->setEnabled(true);
        ui->btBlack->setEnabled(false);

    }

}



