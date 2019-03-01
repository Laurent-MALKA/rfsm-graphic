#include "TransitionUI.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QtMath>
#include <iostream>
#include <vector>

TransitionUI::TransitionUI(Transition& transition,
                           StateUI* start_state,
                           StateUI* end_state)
    : transition(transition),
      start_state(start_state),
      end_state(end_state),
      border_size(5),
      arrow_size(25),
      arrow_angle(30.0)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

Transition& TransitionUI::getTransition()
{
    return transition;
}

StateUI& TransitionUI::getStartState()
{
    return *start_state;
}

StateUI& TransitionUI::getEndState()
{
    return *end_state;
}

const Transition& TransitionUI::getTransition() const
{
    return transition;
}

const StateUI& TransitionUI::getStartState() const
{
    return *start_state;
}

const StateUI& TransitionUI::getEndState() const
{
    return *end_state;
}

void TransitionUI::setStartState(StateUI* start_state)
{
    this->start_state = start_state;
    transition.setStartState(&start_state->getState());
}

void TransitionUI::setEndState(StateUI* end_state)
{
    this->end_state = end_state;
    transition.setEndState(&end_state->getState());
}

QRectF TransitionUI::boundingRect() const
{
    return path.boundingRect();
}

QPainterPath TransitionUI::shape() const
{
    return path;
}

int TransitionUI::type() const
{
    return Type;
}

void TransitionUI::paint(QPainter* painter,
                         const QStyleOptionGraphicsItem*,
                         QWidget*)
{
    QBrush brush;
    if(isSelected())
        brush.setStyle(Qt::Dense4Pattern);
    else
        brush.setStyle(Qt::SolidPattern);

    if(transition.getCondition().empty())
        brush.setColor(Qt::red);
    else
        brush.setColor(Qt::black);

    painter->setPen(QPen(Qt::black));
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPathStroker stroker;
    stroker.setWidth(border_size);
    stroker.setCapStyle(Qt::FlatCap);
    stroker.setJoinStyle(Qt::MiterJoin);

    defineLine();
    defineArrowHead();

    path = QPainterPath();
    path.addPolygon(line);

    path = stroker.createStroke(path);

    // TODO find a better solution to avoid intersect area not to be filled
    {
        QPainterPath p;
        p.addPolygon(arrow_head);

        QPainterPath intersect = path.intersected(p);

        path.addPolygon(arrow_head);
        path.addPath(intersect);
    }

    painter->fillPath(path, QColor(205, 232, 255));
    painter->drawPath(path);
}

void TransitionUI::defineLine()
{
    QPointF start_point =
        start_state->mapToScene(start_state->boundingRect().center());
    QPointF end_point =
        end_state->mapToScene(end_state->boundingRect().center());

    line.clear();

    line << start_point;

    // Loop transition
    if(start_point == end_point)
    {
        line << QPointF(start_point.x(),
                        start_point.y() - start_state->boundingRect().height());
        line << QPointF(start_point.x() - start_state->boundingRect().width(),
                        start_point.y() - start_state->boundingRect().height());
        line << QPointF(start_point.x() - start_state->boundingRect().width(),
                        start_point.y());
    }
    // Transition to another state
    else
    {
        QRectF end_rect =
            QRectF(end_state->mapToScene(end_state->boundingRect().topLeft()),
                   end_state->boundingRect().size());

        if((start_point.x() < end_rect.left()
            || start_point.x() > end_rect.right())
           && (start_point.y() < end_rect.top()
               || start_point.y() > end_rect.bottom()))
        {
            line << QPointF(start_point.x(), end_point.y());
        }
        else
        {
            if(start_point.x() > end_rect.left()
               && start_point.x() < end_rect.right())
                end_point.setX(start_point.x());
            else
                line.first().setY(end_point.y());
        }
    }

    line << end_point;
}

void TransitionUI::defineArrowHead()
{
    QPointF previous_point = line.at(line.size() - 2);
    QPointF end_point = line.at(line.size() - 1);

    QLineF last_line(previous_point, end_point);
    QRectF end_rect(mapFromItem(end_state, end_state->boundingRect().topLeft()),
                    end_state->boundingRect().size());

    std::vector<QLineF> state_lines;
    state_lines.emplace_back(end_rect.topLeft(), end_rect.bottomLeft());
    state_lines.emplace_back(end_rect.bottomLeft(), end_rect.bottomRight());
    state_lines.emplace_back(end_rect.bottomRight(), end_rect.topRight());
    state_lines.emplace_back(end_rect.topRight(), end_rect.topLeft());

    for(auto& state_line : state_lines)
    {
        if(last_line.intersect(state_line, &end_point)
           == QLineF::BoundedIntersection)
            break;
    }

    arrow_head.clear();
    arrow_head << end_point;
    // Computes the position of the points to make the arrow_head
    QPointF arrow_point_1(
        end_point.x()
            - arrow_size
                  * qCos(qDegreesToRadians(arrow_angle - last_line.angle())),
        end_point.y()
            - arrow_size
                  * qSin(qDegreesToRadians(arrow_angle - last_line.angle())));

    QPointF arrow_point_2(
        end_point.x()
            - arrow_size
                  * qCos(qDegreesToRadians(arrow_angle + last_line.angle())),
        end_point.y()
            + arrow_size
                  * qSin(qDegreesToRadians(arrow_angle + last_line.angle())));

    arrow_head << arrow_point_1;
    arrow_head << arrow_point_2;
    arrow_head << end_point;

    last_line.intersect(QLineF(arrow_point_1, arrow_point_2), &end_point);

    line.last() = end_point;
}
