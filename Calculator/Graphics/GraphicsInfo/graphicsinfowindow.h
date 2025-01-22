#ifndef GRAPHICSINFOWINDOW_H
#define GRAPHICSINFOWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QCloseEvent>
#include <QVector>

#include <iostream>
#include <string>

#include "./../../source/calculatorobject.h"
#include "./../../source/graphicsinfoobject.h"
#include "./../../source/calculatormath.h"

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
    CalculatorObject curent_object;
    QVector<CalculatorObject> objects;
    QVector<GraphicsInfoObject> info_objects;
    CalculatorMath info_math;
    QString curent_text;
    bool function_window_show;
    int count_open_bracket;
    int curent_acuracy, function_acuracy, graphics_point_count;

private:
    void closeEvent(QCloseEvent*);
    void loadIcons();
    void loadStyles();

signals:
    void closeWindow();
    void changeWindow(int);
    void needUpdateList();
    void addNewElement();

public slots:
    void openPainter();

private slots:
    void buttonChangeMode();
    void updateMode(int);
    void updatePainterWindowState();
    void setFullText();
    void pressNumberButton(QChar buttonNum);
    void pressOperButton(QString buttonOper);
    void pressVariableButton();
    void pressFunctionsButton();
    void addedFunction(QString);
    void addedSpecialFunction(QString);
    void buttonDot();
    void buttonClear();
    void buttonOpenBrackets();
    void buttonCloseBrackets();
    void buttonAdd();
    void buttonZnak();
    void buttonDeleteLast();
    void deleteListElement();
    void updateFunctionWindowState();
    void updateListWidget();
};

#endif // GRAPHICSINFOWINDOW_H
