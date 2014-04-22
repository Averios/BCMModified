#include "problemwindow.h"
#include "ui_problemwindow.h"

ProblemWindow::ProblemWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProblemWindow)
{
    ui->setupUi(this);
    handler = new WindowsHandling();
    connect(ui->action_About,SIGNAL(triggered()),handler,SLOT(About()));

}

ProblemWindow::~ProblemWindow()
{
    delete ui;
}
