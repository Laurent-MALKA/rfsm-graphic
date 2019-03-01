#ifndef RFSM_GRAPHIC_STATE_UI_HPP
#define RFSM_GRAPHIC_STATE_UI_HPP

#include "../engine/State.hpp"

#include <QGraphicsItem>

class StateUI : public QGraphicsItem
{
  private:
    State& state;
    bool initial;

    float border_size = 1;
    qreal width = 100;
    qreal height = 50;

    QSize size;

  public:
    enum
    {
        Type = UserType + 1
    };

    StateUI(State& state, double posX, double posY);

    State& getState();
    const State& getState() const;

    int type() const;
    QRectF boundingRect() const;
    QPainterPath shape() const;

    bool isInitial() const;
    void setInitial(bool initial = true);

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr);

    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
};

#endif
