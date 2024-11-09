#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QPixmap>

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
    QString curentText;
    QVector<QString> historyArr;
    QSettings* settings;
    CalculatorMath* calculatorMathObject;
    bool flagAfterResult;
    int countOpenBracket, countOper, typeLastSymbol, curent_acuracy;

private slots:
    void PressNumberButton(QChar buttonNum);
    void PressOperButton(QChar buttonOper);
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
