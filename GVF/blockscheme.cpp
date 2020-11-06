#include "blockscheme.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QDebug>

BlockScheme::BlockScheme (int x, int y, Geometry g, QObject *parent)
    : QObject(parent), QGraphicsItem(), geometry(g)
{
   brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
   brush.setStyle(Qt::BrushStyle::SolidPattern);


   moving = false;
   angle = 0.0;

   switch(g)
   {
   case RECTANGLE:
   case ELLIPS:
       m_w = 200;
       m_h = 100;
       m_x = x-m_w/2;
       m_y = y-m_h/2;

       break;
   case STAR:
       m_w = 100;
       m_h = 100;
       m_x = x-m_w/2;
       m_y = y-m_h/2;
       break;
   }
    setPos(0,0);
    this->setTransformOriginPoint(this->boundingRect().center());
}

void BlockScheme::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->setBrush(brush);

   if (geometry == Geometry::ELLIPS)
   {
       painter->drawEllipse(m_x, m_y, m_w, m_h);
   }
   if (geometry == Geometry::RECTANGLE)
   {
       painter->drawRect(m_x, m_y, 200, 100);
   }
   if (geometry == Geometry::STAR)
   {
       QPainterPath starPath;
       int R = -50;
       int r = 25;
       starPath.moveTo(m_x+50, m_y+R+50);
       for (int i = 1; i <= 5; ++i) {
           starPath.lineTo(m_x+50+r * std::cos(72 * (i+2) * M_PI/180 + M_PI/2),
                           m_y+50+r * std::sin(72 * (i+2) * M_PI/180 + M_PI/2));
           starPath.lineTo(m_x+50+R * std::cos(72 * i * M_PI/180 + M_PI/2),
                           m_y+50+R * std::sin(72 * i * M_PI/180 + M_PI/2));

       }
       starPath.closeSubpath();
       painter->drawPath(starPath);
   }

   Q_UNUSED(option)
   Q_UNUSED(widget)
}

QRectF BlockScheme::boundingRect() const         // Обязателен для
                                                 // переопределения
{
   return QRectF(m_x, m_y, m_w, m_h);                // Текущие координаты
}

void BlockScheme::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)        // Левая кнопка, режим
                                                 // перемещения
   {
       moving = true;                            // Флаг активности                                                // перемещения
       bpoint = event->pos().toPoint();          // Запоминаем начальные
                                                 // координаты мыши
   }

   if (event->button() == Qt::MiddleButton)
   {
       rotate = true;
       QPointF p = mapToScene(event->pos());
       qreal x = p.x() - boundingRect().center().x();
       qreal y = p.y() - boundingRect().center().y();
       angle = std::acos(x/std::sqrt(pow(x,2)+pow(y,2)));
       if(y > 0.0)
            angle = 2*M_PI - angle;
   }
}

void BlockScheme::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)
   {
       moving = false;
       this->setTransformOriginPoint(this->boundingRect().center());
       emit reDraw();
   }
   if (event->button() == Qt::MiddleButton)
   {
       rotate = false;

       emit reDraw();
   }
}

void BlockScheme::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

   if (moving)                                    // Если активен флаг                                                 // перемещения
   {
       QPoint p = event->pos().toPoint() - bpoint;// Вычисляем вектор смещения
       m_x += p.x();
       m_y += p.y();
       bpoint = event->pos().toPoint();           // Запоминаем новую позицию
                                                  // курсора
       emit reDraw();                             // Переотрисовываем
   }
   if (rotate)
   {
       QPointF p = mapToScene(event->pos());
       qreal x = (p.x() - boundingRect().center().x())/**cos(angle)*/;
       qreal y = (p.y() - boundingRect().center().y())/**sin(angle)*/;

       double a1 = std::acos(x/std::sqrt(pow(x,2)+pow(y,2)));
       if(y > 0.0)
           a1 = 2*M_PI - a1;

       this->setRotation((angle - a1)*180.0/M_PI);
       emit reDraw();
   }
}

void BlockScheme::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)
   {
       emit dblClick();                            // Отправляем сигнал
                                                   // о двойном клике
   }
}

