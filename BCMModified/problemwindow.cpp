#include "problemwindow.h"
#include "ui_problemwindow.h"

ProblemWindow::ProblemWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProblemWindow)
{
    ui->setupUi(this);
    handler = new WindowsHandling();
    connect(ui->action_About,SIGNAL(triggered()),handler,SLOT(About()));
    connect(ui->action_Credits,SIGNAL(triggered()),handler,SLOT(Credits()));
    solved = false;
}

ProblemWindow::~ProblemWindow()
{
    delete ui;
}


void ProblemWindow::on_pushButton_clicked()
{
    if(!solved){
        //Solve the problem
    }
    solved = true;
    ResultDialog *result = new ResultDialog();
    /*
        Parse the result
    */

    result->show();
    result->raise();
    result->activateWindow();
}

void ProblemWindow::setTable(int x, int y){
    ui->tableWidget->setRowCount(y);
    ui->tableWidget->setColumnCount(x);
}
