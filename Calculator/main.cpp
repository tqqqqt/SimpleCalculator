#include <QApplication>
#include <QSettings>

#include "mainwindow.h"
#include "Value/valuewindow.h"
#include "Programmist/programmistwindow.h"
#include "Graphics/GraphicsInfo/graphicsinfowindow.h"

class WindowChanger: public QObject{
private:
    MainWindow* calculator_window;
    ValueWindow* value_window;
    ProgrammistWindow* programmist_window;
    GraphicsInfoWindow* graphics_info_window;

public:
    void setWindows(MainWindow* _calculator_window, ValueWindow* _value_window, ProgrammistWindow* _programmist_window, GraphicsInfoWindow* _graphics_info_window){
        calculator_window=_calculator_window;
        value_window=_value_window;
        programmist_window=_programmist_window;
        graphics_info_window=_graphics_info_window;
    }

    void curentWindow(int curent_mode){
        if(curent_mode==1) calculator_window->show();
        else if(curent_mode==2) value_window->show();
        else if(curent_mode==3) programmist_window->show();
        else if(curent_mode==4){
            graphics_info_window->show();
            graphics_info_window->openPainter();
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("tqqqqt","calculator");
    if(!settings.contains("calc/mode")) settings.setValue("calc/mode",1);
    int curent_mode=settings.value("calc/mode",1).toInt();

    WindowChanger window_changer;
    MainWindow calculator_window;
    ValueWindow value_window;
    ProgrammistWindow programmist_window;
    GraphicsInfoWindow graphics_window;
    window_changer.setWindows(&calculator_window,&value_window,&programmist_window,&graphics_window);

    QObject::connect(&calculator_window,&MainWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);
    QObject::connect(&value_window,&ValueWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);
    QObject::connect(&programmist_window,&ProgrammistWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);
    QObject::connect(&graphics_window,&GraphicsInfoWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);

    window_changer.curentWindow(curent_mode);

    return a.exec();
}
