#include <iostream>
#include <vector>

#include <QtMath>
#include <QPen>
#include <QPainter>
#include <QPainterPath>

#include "TransitionUI.hpp"

TransitionUI::TransitionUI(Transition& transition, StateUI& start_state, StateUI& end_state)
    : transition(transition), start_state(start_state), end_state(end_state), border_size(5), arrow_size(25), arrow_angle(30.0)
{

}

Transition& TransitionUI::getTransition()
{
    return transition;
}

StateUI& TransitionUI::getStartState()
{
    return start_state;
}

StateUI& TransitionUI::getEndState()
{
    return end_state;
}

QRectF TransitionUI::boundingRect() const
{
    if(start_state.getState().getId() != end_state.getState().getId())
    {
        QPointF start_point = start_state.mapToScene(start_state.rect().center());
        QPointF end_point = end_state.mapToScene(end_state.rect().center());

        return QRectF(start_point, end_point).normalized();
    }

    else
    {
        QPointF center_point = mapFromItem(&start_state, start_state.rect().center());
        return QRectF(center_point.x(), center_point.y(), -start_state.rect().width(), -start_state.rect().height()).normalized().adjusted(-border_size, -border_size, border_size, border_size);
    }
    
}

QPainterPath TransitionUI::shape() const
{
    QPainterPath path;
    
    if(start_state.getState().getId() != end_state.getState().getId())
    {
        QLineF line = this->line();
        qreal angle = qDegreesToRadians(line.normalVector().angle());
        QPolygonF polygon;
        polygon << mapToScene(QPointF(line.x1() + border_size*qCos(angle), line.y1() - border_size*qSin(angle)));
        polygon << mapToScene(QPointF(line.x1() - border_size*qCos(angle), line.y1() + border_size*qSin(angle)));
        polygon << mapToScene(QPointF(line.x2() - border_size*qCos(angle), line.y2() + border_size*qSin(angle)));
        polygon << mapToScene(QPointF(line.x2() + border_size*qCos(angle), line.y2() - border_size*qSin(angle)));
        polygon << mapToScene(QPointF(line.x1() + border_size*qCos(angle), line.y1() - border_size*qSin(angle)));

        path.addPolygon(polygon);
    }

    else
    {
        QPointF center_point = mapFromItem(&start_state, start_state.rect().center());
        QRectF arrow = QRectF(center_point.x(), center_point.y(), -start_state.rect().width(), -start_state.rect().height()).normalized();

        path.addRect(arrow);
    }


    path.addPolygon(arrow_head);

    return path;
}

int TransitionUI::type() const
{
    return Type;
}

void TransitionUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black, border_size);
    
    if(isSelected())
    {
        pen.setStyle(Qt::DotLine);
    }
    else
    {
        pen.setStyle(Qt::SolidLine);
    }
    
    painter->setPen(pen);

    painter->setRenderHint(QPainter::Antialiasing);


    if(start_state.getState().getId() != end_state.getState().getId())
    {
        if(start_state.collidesWithItem(&end_state))
            return;

        QPointF start_point = start_state.mapToScene(start_state.rect().center());
        QPointF end_point = end_state.mapToScene(end_state.rect().center());

        setLine(QLineF(start_point, end_point));

        std::vector<QLineF> state_lines;
        QPointF p1(mapFromItem(&end_state, QPointF(end_state.rect().x(), end_state.rect().y())));
        QPointF p2(mapFromItem(&end_state, QPointF(end_state.rect().x(), end_state.rect().y() + end_state.rect().height())));
        QPointF p3(mapFromItem(&end_state, QPointF(end_state.rect().x() + end_state.rect().width(), end_state.rect().y() + end_state.rect().height())));
        QPointF p4(mapFromItem(&end_state, QPointF(end_state.rect().x() + end_state.rect().width(), end_state.rect().y())));
        state_lines.push_back(QLineF(p1,p2));
        state_lines.push_back(QLineF(p2, p3));
        state_lines.push_back(QLineF(p3, p4));
        state_lines.push_back(QLineF(p4, p1));
        for(auto& state_line: state_lines)
        {
            if(line().intersect(state_line, &end_point) == QLineF::BoundedIntersection)
                break;
        }
        arrow_head.clear();
        arrow_head << end_point;
        QPointF arrow_point_1(end_point.x() - arrow_size*qCos(qDegreesToRadians(arrow_angle-line().angle())), end_point.y() - arrow_size*qSin(qDegreesToRadians(arrow_angle-line().angle())));
        QPointF arrow_point_2(end_point.x() - arrow_size*qCos(qDegreesToRadians(arrow_angle+line().angle())), end_point.y() + arrow_size*qSin(qDegreesToRadians(arrow_angle+line().angle())));
        arrow_head << arrow_point_1;
        arrow_head << arrow_point_2;
        arrow_head << end_point;

        line().intersect(QLineF(arrow_point_1, arrow_point_2), &end_point);

        setLine(QLineF(start_point, end_point));

        painter->drawLine(line());
    }

    else
    {
        QPointF center_point = mapFromItem(&start_state, start_state.rect().center());
        QRectF arrow = QRectF(center_point.x(), center_point.y(), -start_state.rect().width(), -start_state.rect().height()).normalized();
        
        painter->drawRect(arrow);

        arrow_head.clear();
        QPointF end_point(center_point.x() - arrow.width()/2, center_point.y());
        
        arrow_head << end_point;
        arrow_head << QPointF(end_point.x() - arrow_size*qCos(qDegreesToRadians(arrow_angle)), end_point.y() - arrow_size*qSin(qDegreesToRadians(arrow_angle)));
        arrow_head << QPointF(end_point.x() - arrow_size*qCos(qDegreesToRadians(arrow_angle)), end_point.y() + arrow_size*qSin(qDegreesToRadians(arrow_angle)));
        arrow_head << end_point;
    }
    
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    QBrush brush(Qt::black);
    painter->setBrush(brush);

    painter->drawPolygon(arrow_head);


    

}
