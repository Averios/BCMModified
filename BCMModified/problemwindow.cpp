#include "problemwindow.h"
#include "ui_problemwindow.h"
#include <vector>
#include<algorithm>
using namespace std;

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
    bool ok;
    ResultDialog *result = new ResultDialog();
    QTableWidget *tabel = ui->tableWidget;
    QString converter;
    /*
        Parse the result
    */
    int column = tabel->columnCount();
    int row = tabel->rowCount();
    PointingX = new vector< MyPair >[column];
    PointingY = new vector< MyPair >[row];
//    PointingX = new vector< pair< double, TableContainer* > >[column];
//    PointingY = new vector< pair< double, TableContainer* > >[row];
    TableContainer *problem;
//    vector< pair< double, TableContainer> > *empty;
//    for(int i = 0; i < row; i++){
//        empty = new vector< pair< double, *TableContainer> >;
//        PointingY->push_back(*empty);
//    }
//    for(int i = 0; i < column; i++){
//        empty = new vector< pair< double, *TableContainer> >;
//        PointingX->push_back(*empty);
//    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            problem = new TableContainer;
            converter = tabel->item(i,j)->text();
            problem->active = 0;
            problem->value = converter.toDouble(&ok);
            problem->x = j;
            problem->y = i;
            (PointingY[i]).push_back(make_pair(converter.toDouble(&ok),problem));
            (PointingX[j]).push_back(make_pair(converter.toDouble(&ok),problem));
        }
    }
    SolveProblem(row,column);

//    result->MakeTable(column,row,problem);
    result->show();
    result->raise();
    result->activateWindow();
}

void ProblemWindow::SolveProblem(int row, int column){
    bool up = ui->option1->isChecked();
    int minus, opt;
    if(up){
        minus = -1;
        opt = 1;
    }
    else{
        minus = 1;
        opt = 0;
    }
    double optimum;
    int counter;
    int countings;

    //Selecting candidate from every row
    for(int i = 0; i < row; i++){
        //Sort the vector
        sort(PointingY[i].begin(),PointingY[i].end(), sorter);
        counter = 1;
        //Select the candidate(2 optimum value)
        optimum = PointingY[i][0 + (column - 1)*opt].first;
        for(int j = 0; j < column; j++){
            countings = j*minus + (column - 1)*opt;
            if(PointingY[i][countings].first == optimum){
                PointingY[i][countings].second->active++;
            }
            else{
                counter++;
                if(counter < 3){
                    optimum = PointingY[i][countings].first;
                    PointingY[i][countings].second->active++;
                }
                else break;
            }
        }

    }
    //electing candidate from every column
    int stop;
    for(int i = 0; i < column; i++){
        sort(PointingX[i].begin(),PointingX[i].end(), sorter);
        counter = 0;
        for(int j = 0; j < row; j++){
            countings = j*minus + (column - 1)*opt;
            if(PointingX[i][countings].second->active == 1){
                optimum = PointingX[i][countings].first;
                PointingX[i][countings].second->active++;
                stop = j + 1;
                counter++;
                break;
            }
        }

        for(int j = stop; j < row; j++){
            countings = j*minus + (column - 1)*opt;
            if(PointingX[i][countings].second->active == 1){
                if(PointingX[i][countings].first == optimum){
                    PointingX[i][countings].second->active++;
                }
                else{
                    counter++;
                    if(counter < 3){
                        PointingX[i][countings].second->active++;
                        optimum = PointingX[i][countings].first;
                    }
                    else break;
                }
            }
            else continue;
        }
    }


}

void ProblemWindow::setTable(int x, int y){
    ui->tableWidget->setRowCount(y);
    ui->tableWidget->setColumnCount(x);
}
