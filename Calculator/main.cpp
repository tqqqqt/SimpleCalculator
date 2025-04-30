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
    // save adress of all windows avalible in program
    void setWindows(MainWindow* _calculator_window, ValueWindow* _value_window, ProgrammistWindow* _programmist_window, GraphicsInfoWindow* _graphics_info_window){
        calculator_window=_calculator_window;
        value_window=_value_window;
        programmist_window=_programmist_window;
        graphics_info_window=_graphics_info_window;
    }

    // open curent calculatore mode
    void curentWindow(const int& curent_mode){
        if(curent_mode==1) calculator_window->show();
        else if(curent_mode==2) value_window->show();
        else if(curent_mode==3) programmist_window->show();
        else if(curent_mode==4){
            // graphics mode have to window, first when input equation, second where paint graphics
            // its first window
            graphics_info_window->show();
            // its second window
            graphics_info_window->openPainter();
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // open settings and check curent calculator mdoe
    QSettings settings("tqqqqt","calculator");
    if(!settings.contains("calc/mode")) settings.setValue("calc/mode",1);
    // if no mode then set default calculatore mode
    int curent_mode=settings.value("calc/mode",1).toInt();

    // create object to change curent calculator mode
    WindowChanger window_changer;
    // create all avalible windows
    MainWindow calculator_window;
    ValueWindow value_window;
    ProgrammistWindow programmist_window;
    GraphicsInfoWindow graphics_window;
    // add in window chenger object
    window_changer.setWindows(&calculator_window,&value_window,&programmist_window,&graphics_window);

    // connect signalst to change curent window when change mode
    QObject::connect(&calculator_window,&MainWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);
    QObject::connect(&value_window,&ValueWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);
    QObject::connect(&programmist_window,&ProgrammistWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);
    QObject::connect(&graphics_window,&GraphicsInfoWindow::changeWindow,&window_changer,&WindowChanger::curentWindow);

    // open curent window mode
    window_changer.curentWindow(curent_mode);

    return a.exec();
}
