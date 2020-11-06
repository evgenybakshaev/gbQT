#ifndef BlockScheme_H
#define BlockScheme_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>

class BlockScheme  : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)
public:
    enum Geometry {RECTANGLE, ELLIPS, STAR};
    explicit BlockScheme (int x, int y, Geometry g, QObject *parent = nullptr);
    void setBrush(QBrush brush) {this->brush = brush; emit reDraw();}
signals:
   void reDraw();
   void dblClick();
public slots:
private:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
   QRectF boundingRect() const override;
private:
   QRectF brect;
   int m_x, m_y, m_w, m_h;
   Geometry geometry;
   QPoint bpoint;
   bool moving;
   bool rotate;
   QPointF rpoint;
   double angle;
   QBrush brush;
protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // BlockScheme _H
