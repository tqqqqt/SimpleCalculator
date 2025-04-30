#ifndef FUNCTIONSWINDOW_H
#define FUNCTIONSWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTextStream>

namespace Ui {
class FunctionsWindow;
}

class FunctionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FunctionsWindow(QWidget *parent = nullptr);
    ~FunctionsWindow();

private:
    Ui::FunctionsWindow *ui;

private:
    void closeEvent(QCloseEvent*);
    void loadStyle();

private slots:
    void pressButtons(const QString&);
    void needCloseWindow();

signals:
    void pressFunction(const QString&);
    void pressSpecialFunction(const QString&);
    void updateWindowState();
};

#endif // FUNCTIONSWINDOW_H
