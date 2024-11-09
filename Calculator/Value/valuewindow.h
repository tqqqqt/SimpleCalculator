#ifndef VALUEWINDOW_H
#define VALUEWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QPixmap>

#include "./../Mode/modewindow.h"

namespace Ui {
class ValueWindow;
}

class ValueWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ValueWindow(QWidget *parent = nullptr);
    ~ValueWindow();

private:
    Ui::ValueWindow *ui;
    QString left_text, right_text;
    int curent_field;

private slots:
    void pressNumberButton(QChar button_num);
    void buttonDot();
    void buttonClear();
    void buttonDeleteLast();
    void buttonChangeMode();
    void updateMode(int);
    void updateResult();
    void buttonChangeField(int);

signals:
    void getResult();
    void changeWindow(int);
};

#endif // VALUEWINDOW_H
