#ifndef GRAPHICSPAINTERWINDOW_H
#define GRAPHICSPAINTERWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPixmap>
#include <QPainter>

#include "./../../source/graphicsinfoobject.h"
#include "./../../source/calculatormath.h"

#define POINT_SPACE 30

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
    QPixmap clear_ord, clear_ord_with_point, curent_ord;
    int curent_scale, curent_new_color;

private:
    void closeEvent(QCloseEvent*);
    void resizeEvent(QResizeEvent*);
    Qt::GlobalColor getNewColor();

public slots:
    void paintGraphics();

private slots:
    void needClose();
    QPixmap paintMainOrd();
    void paintPoints();
    void addScale();
    void minusScale();
    void updatePicture();
    void clearGraphics();

signals:
    void closeWindow();
    void needPaintPoints();
    void needUpdatePicture();
    void needClearGraphics();
};

#endif // GRAPHICSPAINTERWINDOW_H
