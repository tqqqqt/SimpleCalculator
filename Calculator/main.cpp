#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings settings("tqqqqt","calculator");
    if(!settings.contains("calc/mode")) settings.setValue("calc/mode",1);
    int curent_mode=settings.value("calc/mode",1).toInt();
    MainWindow w;
    if(curent_mode==1) w.show();

    return a.exec();
}
