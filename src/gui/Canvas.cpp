#include <numeric>

#include "Canvas.hpp"
#include "../engine/State.hpp"

/**
 * Create a state in the state charts and display it
 */
StateUI* Canvas::addState(std::string name, float posX, float posY)
{
    unsigned int id = state_chart.addState(name);
    StateUI* state = new StateUI(this, state_chart.getState(id), posX, posY);
    this->states.push_back(state);

    return state;
}

/**
 * Do the action of the selected tool
 */
void Canvas::mousePressEvent(QMouseEvent *event)
{
    StateUI* state = this->addState(std::string("state_") + std::to_string(states.size()), event->x(), event->y());
    state->move(state->x() - state->width()/2, state->y() - state->height()/2);
    state->show();
}
