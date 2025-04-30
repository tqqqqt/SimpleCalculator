#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QCloseEvent>

#include <iostream>
#include <string>

#include "./source/calculatorobject.h"
#include "./source/calculatormath.h"

#include "./History/historywindow.h"
#include "./Settings/settingswindow.h"
#include "./Functions/functionswindow.h"
#include "./Mode/modewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void pressResult();
    void closeWindow();
    void changeWindow(const int&);

private:
    Ui::MainWindow *ui;
    QVector<CalculatorObject> objects;
    CalculatorObject curent_object;
    QString curent_text;
    QVector<QString> history_arr;
    CalculatorMath calculator_math_object;
    bool flag_after_result, function_window_show, history_window_show;
    int count_open_bracket, count_oper;
    int curent_acuracy, function_acuracy;

private:
    void closeEvent(QCloseEvent*);
    void loadStyle();
    void loadIcons();

private slots:
    void setFullText();
    void pressNumberButton(const QChar&);
    void pressOperButton(const QString&);
    void pressFunctionsButton();
    void addedFunction(const QString&);
    void addedSpecialFunction(const QString&);
    void buttonDot();
    void buttonClear();
    void buttonOpenBrackets();
    void buttonCloseBrackets();
    void buttonResult();
    void buttonZnak();
    void buttonHistory();
    void buttonDeleteLast();
    void buttonSettings();
    void updateSettings();
    void buttonChangeMode();
    void updateMode(const int&);
    void updateFunctionWindowState();
    void updateHistoryWindowState();
};

#endif  // MAINWINDOW_H
