#include "windowshandling.h"

WindowsHandling::WindowsHandling(QObject *parent):QObject(parent)
{
}
void WindowsHandling::About(){
    if(!OpenAbout){
        OpenAbout = new AboutDialog();
    }
    OpenAbout->show();
    OpenAbout->raise();
    OpenAbout->activateWindow();
}
