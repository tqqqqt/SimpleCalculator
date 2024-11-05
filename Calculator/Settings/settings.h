#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;

private slots:
    void buttonAccept();
    void buttonClose();

signals:
    void acceptSettings();
};

#endif // SETTINGS_H
