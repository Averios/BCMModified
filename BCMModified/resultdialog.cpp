#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{

    ui->setupUi(this);
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::MakeTable(int x, int y){
    QScrollArea *s = ui->scrollArea;
    WidgetList *l = new WidgetList(s);
    QTableWidget *w;
    int height;
    int width;
    for(int i = 0; i < 10; i++){
        w = new QTableWidget(x,y);
        width = (w->columnCount() + 1)*(w->columnWidth(0));
        height = (w->rowCount() + 1)*(w->rowHeight(0));
        w->setMinimumWidth(width);
        w->setMinimumHeight(height);
        w->setEditTriggers(QAbstractItemView::NoEditTriggers);
        l->addWidget(w);
    }
    s->setWidget(l);
    s->setWidgetResizable(true);
    s->show();
}
