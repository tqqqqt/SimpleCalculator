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
    int countOpenBracket, typeLastSymbol;

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
};

#endif // MAINWINDOW_H
