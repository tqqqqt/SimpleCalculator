#ifndef PROGRAMMISTWINDOW_H
#define PROGRAMMISTWINDOW_H

#include <QMainWindow>

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
};

#endif // PROGRAMMISTWINDOW_H
