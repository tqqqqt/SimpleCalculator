#ifndef FUNCTIONSWINDOW_H
#define FUNCTIONSWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

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

private slots:
    void pressButtons(QString);
    void needCloseWindow();

signals:
    void pressFunction(QString);
    void updateWindowState();
};

#endif // FUNCTIONSWINDOW_H
