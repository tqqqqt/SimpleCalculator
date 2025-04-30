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
    ValueInfo value_info;
    int curent_field;
    QString disable_button_style, enable_button_style;

    void loadStyle();
    void loadIcons();

private slots:
    void pressNumberButton(const QChar&);
    void buttonClear();
    void buttonDeleteLast();
    void buttonChangeMode();
    void updateMode(const int&);
    void updateResult();
    void updateText();
    void buttonChangeField(const int&);
    void fillLeftRightBox();

signals:
    void refreshText();
    void getResult();
    void changeWindow(const int&);
};

#endif // VALUEWINDOW_H
