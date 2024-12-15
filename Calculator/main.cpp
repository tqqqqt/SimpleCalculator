#include <QApplication>
#include <QSettings>

#include "mainwindow.h"
#include "Value/valuewindow.h"
#include "Programmist/programmistwindow.h"

class WindowChanger: public QObject{
private:
    MainWindow* calculator_window;
    ValueWindow* value_window;
    ProgrammistWindow* programmist_window;

public:
    void setWindows(MainWindow* _calculator_window, ValueWindow* _value_window, ProgrammistWindow* _programmist_window){
        calculator_window=_calculator_window;
        value_window=_value_window;
        programmist_window=_programmist_window;
    }

    void curentWindow(int curent_mode){
        if(curent_mode==1) calculator_window->show();
        else if(curent_mode==2) value_window->show();
        else if(curent_mode==3) programmist_window->show();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("tqqqqt","calculator");
    if(!settings.contains("calc/mode")) settings.setValue("calc/mode",1);
    int curent_mode=1;//=settings.value("calc/mode",1).toInt();

    WindowChanger window_changer;
    MainWindow calculator_window;
    ValueWindow value_window;
    ProgrammistWindow programmist_window;
    window_changer.setWindows(&calculator_window,&value_window,&programmist_window);

    QObject::connect(&calculator_window,&MainWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);
    QObject::connect(&value_window,&ValueWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);

    window_changer.curentWindow(curent_mode);

    return a.exec();
}
