#ifndef GRAPHICSINFOWINDOW_H
#define GRAPHICSINFOWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QCloseEvent>

#include <iostream>
#include <string>

//

#include "./../GraphicsPainter/graphicspainterwindow.h"
#include "./../../Functions/functionswindow.h"
#include "./../../Mode/modewindow.h"

namespace Ui {
class GraphicsInfoWindow;
}

class GraphicsInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicsInfoWindow(QWidget *parent = nullptr);
    ~GraphicsInfoWindow();

private:
    Ui::GraphicsInfoWindow *ui;
    GraphicsPainterWindow *painter_window;
    bool painter_window_open;

signals:
    void closeWindow();
    void changeWindow(int);

private slots:
    void buttonChangeMode();
    void updateMode(int);
    void updatePainterWindowState();
    void openPainter();
};

#endif // GRAPHICSINFOWINDOW_H
