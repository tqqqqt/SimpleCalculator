#include <QApplication>
#include <QSettings>

#include "mainwindow.h"
#include "Value/valuewindow.h"
#include "Programmist/programmistwindow.h"

class WindowChanger: public QObject{
private:
    MainWindow* w;
    ValueWindow* v;
    ProgrammistWindow* p;

public:
    void setWindows(MainWindow* _w, ValueWindow* _v, ProgrammistWindow* _p){
        w=_w;
        v=_v;
        p=_p;
    }

    void curentWindow(int curent_mode){
        if(curent_mode==1) w->show();
        else if(curent_mode==2) v->show();
        else if(curent_mode==3) p->show();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("tqqqqt","calculator");
    if(!settings.contains("calc/mode")) settings.setValue("calc/mode",1);
    int curent_mode=1;//=settings.value("calc/mode",1).toInt();

    WindowChanger changer;
    MainWindow w;
    ValueWindow v;
    ProgrammistWindow p;
    changer.setWindows(&w,&v,&p);

    QObject::connect(&w,&MainWindow::changeWindow,&changer,&WindowChanger::curentWindow);
    QObject::connect(&v,&ValueWindow::changeWindow,&changer,&WindowChanger::curentWindow);

    changer.curentWindow(curent_mode);

    return a.exec();
}
