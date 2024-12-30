#ifndef FUNCTIONSWINDOW_H
#define FUNCTIONSWINDOW_H

#include <QMainWindow>

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

private slots:
    void pressButtons(QString);
    void closeWindow();

signals:
    void pressFunction(QString);
};

#endif // FUNCTIONSWINDOW_H
