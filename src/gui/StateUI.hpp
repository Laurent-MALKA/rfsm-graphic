#ifndef RFSM_GRAPHIC_STATE_UI_HPP
#define RFSM_GRAPHIC_STATE_UI_HPP

#include "../engine/State.hpp"

#include <QGraphicsWidget>

class StateUI : public QGraphicsWidget
{
  private:
    State& state;
    float borderSize = 1;
    bool initial;

  public:
    enum
    {
        Type = UserType + 1
    };

    StateUI(State& state, double posX, double posY);

    State& getState();
    const State& getState() const;

    int type() const;

    bool isInitial() const;
    void setInitial(bool initial = true);

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr);

    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
};

#endif
