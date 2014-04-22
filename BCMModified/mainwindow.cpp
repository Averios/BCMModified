#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!handler){
        handler = new WindowsHandling();
    }
    connect(ui->action_About,SIGNAL(triggered()),handler,SLOT(About()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Next_clicked()
{
    if(!problem){
        problem = new ProblemWindow();
    }
    problem->show();
    problem->activateWindow();
    this->close();
    delete this;
}
