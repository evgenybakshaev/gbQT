#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "blockscheme.h"

class GraphicsWindow : public QGraphicsView
{
    Q_OBJECT

 public:
    GraphicsWindow(QWidget *parent = 0);
    ~GraphicsWindow();
 private:
    //QGraphicsView *view;
    QGraphicsScene *scence;
    int bsCnt;
    bool zoomIn;
    bool zoomOut;
 protected:
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

 private slots:
    void reDraw();
};

#endif // GRAPHICSWINDOW_H
