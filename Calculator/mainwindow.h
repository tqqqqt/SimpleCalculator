#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QPixmap>

#include <iostream>
#include <string>

#include "./source/calculatorobject.h"
#include "./History/historywindow.h"
#include "./source/calculatormath.h"
#include "./Settings/settingswindow.h"
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
    void PressResult();
    void changeWindow(int);

private:
    Ui::MainWindow *ui;
    QVector<CalculatorObject> objects;
    CalculatorObject curent_object;
    QString curentText;
    QVector<QString> historyArr;
    QSettings* settings;
    CalculatorMath* calculatorMathObject;
    bool flagAfterResult;
    int countOpenBracket, countOper, curent_acuracy;

    void loadStyle();
    void loadIcons();

private slots:
    void setFullText();
    void PressNumberButton(QChar buttonNum);
    void PressOperButton(QString buttonOper);
    void pressFunctionsButton();
    void ButtonDot();
    void ButtonClear();
    void ButtonOpenBrackets();
    void ButtonCloseBrackets();
    void ButtonResult();
    void ButtonZnak();
    void ButtonHistory();
    void ButtonDeleteLast();
    void ButtonSettings();
    void UpdateSettings();
    void ButtonChangeMode();
    void UpdateMode(int);
};

#endif  // MAINWINDOW_H
