#ifndef PROBLEMWINDOW_H
#define PROBLEMWINDOW_H

#include <QMainWindow>

namespace Ui {
class ProblemWindow;
}

class ProblemWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProblemWindow(QWidget *parent = 0);
    ~ProblemWindow();

private:
    Ui::ProblemWindow *ui;
};

#endif // PROBLEMWINDOW_H
