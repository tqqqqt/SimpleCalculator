#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./History/historywindow.h"
#include "./source/calculatormath.h"

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

private:
    Ui::MainWindow *ui;
    QString curentText;
    QVector<QString> historyArr;
    CalculatorMath* calculatorMathObject;
    bool flagAfterResult;
    int curentTextLength, countOpenBracket, typeLastSymbol;

private slots:
    void ButtonN0();
    void ButtonN1();
    void ButtonN2();
    void ButtonN3();
    void ButtonN4();
    void ButtonN5();
    void ButtonN6();
    void ButtonN7();
    void ButtonN8();
    void ButtonN9();
    void ButtonClear();
    void ButtonOpenBrackets();
    void ButtonCloseBrackets();
    void ButtonDevide();
    void ButtonMull();
    void ButtonMinus();
    void ButtonPlus();
    void ButtonResult();
    void ButtonZnak();
    void ButtonHistory();
    void ButtonDeleteLast();
};

#endif // MAINWINDOW_H
