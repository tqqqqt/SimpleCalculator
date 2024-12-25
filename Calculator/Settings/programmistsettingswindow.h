#ifndef PROGRAMMISTSETTINGSWINDOW_H
#define PROGRAMMISTSETTINGSWINDOW_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class ProgrammistSettingsWindow;
}

class ProgrammistSettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProgrammistSettingsWindow(QWidget *parent = nullptr);
    ~ProgrammistSettingsWindow();

private:
    Ui::ProgrammistSettingsWindow *ui;

signals:
    void acceptSettings();

private slots:
    void buttonAccept();
    void buttonClose();
};

#endif // PROGRAMMISTSETTINGSWINDOW_H
