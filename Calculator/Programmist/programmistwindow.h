#ifndef PROGRAMMISTWINDOW_H
#define PROGRAMMISTWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QSettings>

#include <vector>

#include "./../source/programmistobject.h"

#include "./../Mode/modewindow.h"
#include "./../Settings/programmistsettingswindow.h"

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
    ProgrammistObject *object;
    QSettings *settings;
    int curent_system;
    QString disable_button_style, enable_button_style;

    void loadStyle();
    void loadIcons();
    void setButtonsEnable(bool, bool);

private slots:
    void pressNumberButton(QChar);
    void pressMoveButton(int);
    void buttonClear();
    void buttonDeleteLast();
    void updateMode(int);
    void buttonChangeMode();
    void buttonChangeSystem(int);
    void updateResult();
    void openSettings();
    void updateSettings();

signals:
    void getResult();
    void changeWindow(int);
};

#endif // PROGRAMMISTWINDOW_H
