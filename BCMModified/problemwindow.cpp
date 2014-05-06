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
    QTableWidget *tabel = ui->tableWidget;
    /*
        Parse the result
    */
    int column = tabel->columnCount();
    int row = tabel->rowCount();
    int **problem = new int[row][column];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            problem[i][j] = 0;
        }
    }

    //
    result->MakeTable(row,column);
    result->show();
    result->raise();
    result->activateWindow();
}

void ProblemWindow::setTable(int x, int y){
    ui->tableWidget->setRowCount(y);
    ui->tableWidget->setColumnCount(x);
}
