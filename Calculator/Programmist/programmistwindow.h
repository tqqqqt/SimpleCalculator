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
    ProgrammistObject object;
    QSettings *settings;
    int curent_system;
    QString disable_button_style, enable_button_style, curent_system_button_style;

    void loadStyle();
    void loadIcons();
    void setSymbolButtonsEnable(const bool&,const QString&);
    void setNumsButtonsEnable(const bool&,const QString&);
    void setSystemButtonsEnable();

private slots:
    void pressNumberButton(const QChar&);
    void pressMinusButton();
    void pressMoveButton(const int&);
    void buttonClear();
    void buttonDeleteLast();
    void updateMode(const int&);
    void buttonChangeMode();
    void buttonChangeSystem(const int&);
    void updateResult();
    void openSettings();
    void updateSettings();

signals:
    void getResult();
    void changeWindow(const int&);
};

#endif // PROGRAMMISTWINDOW_H
