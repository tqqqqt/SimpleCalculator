#ifndef GRAPHICSPAINTERWINDOW_H
#define GRAPHICSPAINTERWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPixmap>
#include <QPainter>

#include "./../../source/graphicsinfoobject.h"
#include "./../../source/calculatormath.h"

namespace Ui {
class GraphicsPainterWindow;
}

class GraphicsPainterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicsPainterWindow(QWidget *parent = nullptr);
    GraphicsPainterWindow(QVector<GraphicsInfoObject> *arr, QWidget *parent=nullptr);
    ~GraphicsPainterWindow();

private:
    Ui::GraphicsPainterWindow *ui;
    QVector<GraphicsInfoObject> *info_objects;
    QPixmap curent_ord;
    int curent_scale;

private:
    void closeEvent(QCloseEvent*);

public slots:
    void paintGraphics();

private slots:
    void needClose();
    void paintMainOrd();
    void paintPoints();
    void addScale();
    void minusScale();
    void updatePicture();

signals:
    void closeWindow();
    void needPaintOrd();
    void needPaintPoints();
    void needUpdatePicture();
};

#endif // GRAPHICSPAINTERWINDOW_H
