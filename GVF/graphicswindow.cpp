#include "graphicswindow.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

GraphicsWindow::GraphicsWindow(QWidget *parent)
    : QGraphicsView(parent), bsCnt(0)
{
    scence = new QGraphicsScene(this);                      // Новая сцена
    scence->setSceneRect(QRectF(0,0,width(),height()));
    setScene(scence);
}

GraphicsWindow::~GraphicsWindow()
{

}

void GraphicsWindow::mousePressEvent(QMouseEvent *event)
{
    QPointF p = mapToScene(event->pos());
    QGraphicsItem *item = scence->itemAt(p, QGraphicsView::transform());

    if(item == nullptr)
    {
        if (event->button() == Qt::LeftButton)
        {
            BlockScheme *bs = new BlockScheme(p.x(),p.y(), (BlockScheme::Geometry)(bsCnt % 3), this);
            scence->addItem(bs);
            connect(bs, SIGNAL(reDraw()), this, SLOT(reDraw()));
            ++bsCnt;
            reDraw();
        }
    }
    else
    {
        if (event->button() == Qt::RightButton)
        {
            scence->removeItem(item);
        }
        else
        {
            QGraphicsView::mousePressEvent(event);
        }
    }
}

void GraphicsWindow::wheelEvent(QWheelEvent *event)
{
    qreal deltaScale = 1;

    deltaScale += event->delta() > 0 ? 0.1 : -0.1;
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(deltaScale, deltaScale);
}

void GraphicsWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Plus)
        zoomIn = true;
    if(event->key() == Qt::Key_Minus)
        zoomOut = true;
}

void GraphicsWindow::keyReleaseEvent(QKeyEvent *event)
{
    qreal deltaScale = 1;
    if(event->key() == Qt::Key_Plus)
        deltaScale += 0.1;
    if(event->key() == Qt::Key_Minus)
        deltaScale += -0.1;

    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    scale(deltaScale, deltaScale);
}

void GraphicsWindow::reDraw()
{
    scene()->update();
    update();
}







