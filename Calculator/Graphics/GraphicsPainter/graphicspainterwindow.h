#ifndef GRAPHICSPAINTERWINDOW_H
#define GRAPHICSPAINTERWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class GraphicsPainterWindow;
}

class GraphicsPainterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicsPainterWindow(QWidget *parent = nullptr);
    ~GraphicsPainterWindow();

private:
    Ui::GraphicsPainterWindow *ui;

private:
    void closeEvent(QCloseEvent*);

private slots:
    void needClose();

signals:
    void closeWindow();
};

#endif // GRAPHICSPAINTERWINDOW_H
