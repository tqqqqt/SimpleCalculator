#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "./History/historywindow.h"
#include "./source/calculatormath.h"
#include "./Settings/settings.h"

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
    QSettings* settings;
    CalculatorMath* calculatorMathObject;
    bool flagAfterResult;
    int countOpenBracket, typeLastSymbol, curent_acuracy;

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
};

#endif // MAINWINDOW_H
