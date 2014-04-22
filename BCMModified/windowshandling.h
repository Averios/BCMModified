#ifndef WINDOWSHANDLING_H
#define WINDOWSHANDLING_H

#include <QMainWindow>
#include <QObject>
#include "aboutDialog.h"
class WindowsHandling : public QObject
{
    Q_OBJECT
public:
    AboutDialog *OpenAbout;
    WindowsHandling(QObject* parent = 0);
public slots:
    void About();
};

#endif // WINDOWSHANDLING_H
