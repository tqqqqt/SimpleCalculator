#ifndef VALUEWINDOW_H
#define VALUEWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <vector>

#include "./../source/valueinfo.h"
#include "./../source/valueobject.h"

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
    ValueObject up_object, bottom_object;
    ValueInfo* value_info;
    int curent_field;

private slots:
    void pressNumberButton(QChar button_num);
    void buttonClear();
    void buttonDeleteLast();
    void buttonChangeMode();
    void updateMode(int);
    void updateResult();
    void buttonChangeField(int);
    void fillLeftRightBox();

signals:
    void getResult();
    void changeWindow(int);
};

#endif // VALUEWINDOW_H
