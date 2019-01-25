#include <numeric>
#include <iostream>

#include <QGraphicsScene>

#include "Canvas.hpp"
#include "../engine/State.hpp"
#include "StateUI.hpp"
#include "MainWindow.hpp"

Canvas::Canvas(MainWindow* parent) : QGraphicsScene(parent)
{
    main_window = parent;

    setSceneRect(QRectF(0,0,5000,5000));
}

const std::vector<StateUI*> Canvas::getStates() const
{
    return states;
}

/**
 * Create a state in the state charts and display it
 */
StateUI* Canvas::addState(double posX, double posY)
{
    std::string name = std::string("state_") + std::to_string(State::getStatesCounter());
    unsigned int id = state_chart.addState(name);
    StateUI* state = new StateUI(state_chart.getState(id), posX, posY);
    this->states.push_back(state);

    addItem(state);

    return state;
}

void Canvas::deleteState(int state_id)
{
    auto state = states.begin();
    
    for(; state != states.end() && (*state)->getState().getId() != state_id; state++);
    
    if(state != states.end())
    {
        delete *state;
        states.erase(state);
    }
    state_chart.deleteState(state_id);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    main_window->getCurrentTool()->act(event);
    QGraphicsScene::mousePressEvent(event);
}

void Canvas::setStatesFlag(QGraphicsItem::GraphicsItemFlag flag, bool enabled)
{
    for(auto& state: states)
    {
        state->setFlag(flag, enabled);
    }
}
