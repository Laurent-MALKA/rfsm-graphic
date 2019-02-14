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
    //setZValue(2);
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
    QPointF start_point = start_state.mapToScene(start_state.rect().center());
    QPointF end_point = end_state.mapToScene(end_state.rect().center());



    return QRectF(std::min(start_point.x(), end_point.x()),
                 std::min(start_point.y(), end_point.y()),
                 end_point.x() - start_point.x(),
                 end_point.y() - start_point.y())
                 .normalized();
}

QPainterPath TransitionUI::shape() const
{
    QLineF line = this->line();
    qreal angle = qDegreesToRadians(line.normalVector().angle());
    QPolygonF polygon;
    polygon << mapToScene(QPointF(line.x1() + border_size*qCos(angle), line.y1() - border_size*qSin(angle)));
    polygon << mapToScene(QPointF(line.x1() - border_size*qCos(angle), line.y1() + border_size*qSin(angle)));
    polygon << mapToScene(QPointF(line.x2() - border_size*qCos(angle), line.y2() + border_size*qSin(angle)));
    polygon << mapToScene(QPointF(line.x2() + border_size*qCos(angle), line.y2() - border_size*qSin(angle)));
    polygon << mapToScene(QPointF(line.x1() + border_size*qCos(angle), line.y1() - border_size*qSin(angle)));
    QPainterPath path;

    path.addPolygon(polygon);
    path.addPolygon(arrow_head);

    return path;
}

int TransitionUI::type() const
{
    return Type;
}

void TransitionUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(start_state.collidesWithItem(&end_state))
        return;

    QPen pen(Qt::black, border_size);
    QBrush brush(Qt::black);

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->setRenderHint(QPainter::Antialiasing);

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

    line().intersect(QLineF(arrow_point_1, arrow_point_2), &end_point);

    setLine(QLineF(start_point, end_point));

    painter->drawLine(line());

    painter->setPen(QPen(Qt::black));

    painter->drawPolygon(arrow_head);
}
