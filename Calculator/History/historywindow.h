#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QVector>
#include <QCloseEvent>

namespace Ui {
class HistoryWindow;
}

class HistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistoryWindow(QWidget *parent = nullptr);
    HistoryWindow(QVector<QString>* history, QWidget* parent=nullptr);
    ~HistoryWindow();

private:
    Ui::HistoryWindow *ui;
    QVector<QString>* memory;

private:
    void closeEvent(QCloseEvent*);

public slots:
    void updateHis();
    void needCloseWindow();

signals:
    void updateWindowState();
};

#endif // HISTORYWINDOW_H
