#ifndef PROBLEMWINDOW_H
#define PROBLEMWINDOW_H

#include <QMainWindow>
#include "windowshandling.h"
#include "resultdialog.h"
#include "TableContainer.h"

namespace Ui {
class ProblemWindow;
}

class ProblemWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProblemWindow(QWidget *parent = 0);
    ~ProblemWindow();
    void setTable(int x,int y);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ProblemWindow *ui;
    WindowsHandling *handler;
    bool solved;
    bool maximizing;
    vector < MyPair > *PointingX;
    vector < MyPair > *PointingY;
    void SolveProblem(int row, int column);
};

#endif // PROBLEMWINDOW_H
