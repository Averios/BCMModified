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
    RealX = new vector< MyPair >[column];
    PointingX = new vector< MyPair >[column];
    RealY = new vector < MyPair >[row];
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
            (PointingY[i]).push_back(make_pair(problem->value,problem));
            (RealY[i]).push_back(make_pair(problem->value, problem));
            (PointingX[j]).push_back(make_pair(problem->value,problem));
            (RealX[j]).push_back(make_pair(problem->value,problem));
        }
    }
    SolveProblem();

//    result->MakeTable(column,row,problem);
    result->show();
    result->raise();
    result->activateWindow();

    //Free the memory allocation
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            delete RealY[i][j].second;
            delete PointingY[i][j].second;
            delete RealX[j][i].second;
            delete PointingX[j][i].second;
        }
    }
    delete RealX;
    delete RealY;
    delete PointingX;
    delete PointingY;
}

void ProblemWindow::SolveProblem(){
    bool up = ui->option1->isChecked();
    up = !up;

    bool phase1 = false;
    bool sorted = false;

    double optimum;
    int counter;
    //Count the amount of best candidate for every row and column
    int *rowCount = new int[row];
    int *columnCount = new int[column];

    vector < int > *NoMemberX = new vector < int >;
    vector < int > *NomemberY = new vector < int >;
    vector < int > *NoNextY = new vector < int >;
    vector < MyPair > *tempBest;
    for(int i = 0; i < row; i++){
        rowCount[i] = 0;
        NomemberY->push_back(i);
    }
    for(int i = 0; i < column; i++){
        columnCount[i] = 0;
    }

    int rowNow;
    int tempThisSize;
    int tempRowSize = NomemberY->size();
    //Select the best candidate for every rows
    //And make sure every rows have best candidate
    while(!phase1){

        tempBest = new vector< MyPair >[column];

        //Select temporary candidate for each row
        for(int i = 0; i < tempRowSize; i++){
            rowNow = NomemberY[i];
            //If the row hasn't been sorted before, sort the row
            if(!sorted){
                if(up){
                    sort(PointingY[rowNow].begin(), PointingY[rowNow].end(), sorter);
                }
                else{
                    sort(PointingY[rowNow].begin(), PointingY[rowNow].end(), backsort);
                }
            }
            counter = 1;
            optimum = PointingY[rowNow][0];
            for(int j = 0; j < column; j++){
                if(PointingY[rowNow][j].first == optimum){
                    PointingY[rowNow][j].second->active = 1;
                    tempBest[j].push_back(PointingY[rowNow][j]);
                }
                else{
                    counter++;
                    if(counter < 3){
                        optimum = PointingY[rowNow][j].first;
                        PointingY[rowNow][j].second->active = 1;
                        tempBest[j].push_back(PointingY[rowNow][j]);
                    }
                    else break;
                }
            }
        }

        //Elect the best candidate for each column
        for(int i = 0; i < column; i++){
            tempThisSize = tempBest[i].size();
            if(tempThisSize == 0) continue;
            if(up){
                sort(tempBest[i].begin(), tempBest[i].end(), sorter);
            }
            else {
                sort(tempBest[i].begin(), tempBest[i].end(), backsort);
            }
            counter = 1;
            optimum = tempBest[i][0].first;
            for(int j = 0; j < tempThisSize; j++){
                if(tempBest[i][j].first == optimum){
                    tempBest[i][j].second->active = 2;
                    rowCount[tempBest[i][j].second->y]++;
                    columnCount[tempBest[i][j].second->x]++;
                }
                else{
                    counter++;
                    if(counter < 3){
                        optimum = tempBest[i][j].first;
                        tempBest[i][j].second->active = 2;
                        rowCount[tempBest[i][j].second->y]++;
                        columnCount[tempBest[i][j].second->x]++;
                    }
                    else break;
                }
            }
        }
        //Mark that all the rows in PointingY have been sorted
        sorted = true;
        phase1 = true;
        //Check any row that haven't got any best candidate
        NoNextY->clear();
        for(int i = 0; i < tempRowSize; i++){
            if(rowCount[NomemberY[i]] == 0){
                NoNextY->push_back(i);
            }
        }
        //If there are rows without best candidate, repeat the steps for those rows
        tempRowSize = NoNextY->size();
        if(tempRowSize > 0) phase1 = false;
        NomemberY->clear();
        *NomemberY = *NoNextY;

        delete tempBest;
    }
    delete NoNextY;
    bool phase2 = true;
    sorted = false;
    for(int i = 0; i < column; i++){
        if(columnCount[i] == 0){
            NoMemberX->push_back(i);
        }
    }
    int tempColumnSize = NoMemberX->size();
    if(tempColumnSize > 0) phase2 = false;
    int columnNow;
    while (!phase2) {
        tempBest = new vector< MyPair >[row];
        for(int i = 0; i < tempColumnSize; i++){
            columnNow = NoMemberX[i];
            if(!sorted){
                if(up){
                    sort(PointingX[columnNow].begin(), PointingX[columnNow].end(), sorter);
                }
                else{
                    sort(PointingX[columnNow].begin(), PointingX[columnNow].end(), backsort);
                }
            }
            optimum = PointingX[columnNow][0].first;
            counter = 1;
            //Continue Here
        }

        delete tempBest;
    }


    //Free all the memory allocation
    delete NoMemberX;
    delete NomemberY;
    delete rowCount;
    delete columnCount;
    delete tempColumn;

}

void ProblemWindow::setTable(int x, int y){
    row = y;
    column = x;
    ui->tableWidget->setRowCount(y);
    ui->tableWidget->setColumnCount(x);
}
