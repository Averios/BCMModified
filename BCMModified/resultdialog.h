#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include"WidgetList.h"
#include"TableContainer.h"
#include<vector>
using namespace std;
namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = 0);
    ~ResultDialog();

    void MakeTable(int x,int y, double *problem);
private:
    Ui::ResultDialog *ui;
    int **values;

};

#endif // RESULTDIALOG_H
