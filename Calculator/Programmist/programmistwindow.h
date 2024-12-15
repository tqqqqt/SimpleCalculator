#ifndef PROGRAMMISTWINDOW_H
#define PROGRAMMISTWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QPixmap>

#include <vector>

//source

#include "./../Mode/modewindow.h"

namespace Ui {
class ProgrammistWindow;
}

class ProgrammistWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProgrammistWindow(QWidget *parent = nullptr);
    ~ProgrammistWindow();

private:
    Ui::ProgrammistWindow *ui;
    int curent_system;
    QString disable_button_style, enable_button_style;

    void loadStyle();
    void loadIcons();

private slots:
    void pressNumberButton(QChar);
    void pressMoveButton(int);
    void buttonClear();
    void buttonDeleteLast();
    void updateMode(int);
    void buttonChangeMode();
    void buttonChangeSystem(int);

signals:
    void getResult();
    void changeWindow(int);
};

#endif // PROGRAMMISTWINDOW_H
