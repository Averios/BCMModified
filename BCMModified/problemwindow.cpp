#include "problemwindow.h"
#include "ui_problemwindow.h"

ProblemWindow::ProblemWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProblemWindow)
{
    ui->setupUi(this);
}

ProblemWindow::~ProblemWindow()
{
    delete ui;
}
