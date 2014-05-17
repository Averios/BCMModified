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

void ResultDialog::MakeTable(int x, int y, double *problem){
    QScrollArea *s = ui->scrollArea;
    WidgetList *l = new WidgetList(s);
    QTableWidget *w;
    QString converter;
    int height;
    int width;
    double answer[y][x];
    double value;
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            value = problem[j*i + j];
            answer[j][i] = value;
        }
    }
//    for(int i = 0; i < 10; i++){
        w = new QTableWidget(y,x);
        width = (w->columnCount() + 1)*(w->columnWidth(0));
        height = (w->rowCount() + 1)*(w->rowHeight(0));
        w->setMinimumWidth(width);
        w->setMinimumHeight(height);

        for(int i = 0; i < y; i++){
            for(int j = 0; j < x; j++){
                converter = QString::number( answer[j][i] );
                w->item(i,j)->setText( converter );
            }
        }

        w->setEditTriggers(QAbstractItemView::NoEditTriggers);
        l->addWidget(w);

//    }
    s->setWidget(l);
    s->setWidgetResizable(true);
    s->show();
}
