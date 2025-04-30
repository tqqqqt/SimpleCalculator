#ifndef MODEWINDOW_H
#define MODEWINDOW_H

#include <QDialog>
#include <QString>
#include <QSettings>

namespace Ui {
class ModeWindow;
}

class ModeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModeWindow(QWidget *parent = nullptr);
    ~ModeWindow();

private:
    Ui::ModeWindow *ui;

private slots:
    void buttonMode(const int&);

signals:
    void changeMode(const int&);
};

#endif // MODEWINDOW_H
