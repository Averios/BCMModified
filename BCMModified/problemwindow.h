#ifndef PROBLEMWINDOW_H
#define PROBLEMWINDOW_H

#include <QMainWindow>
#include "windowshandling.h"

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
    WindowsHandling *handler;
};

#endif // PROBLEMWINDOW_H
