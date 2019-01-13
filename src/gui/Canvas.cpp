#include "Canvas.hpp"

#include "../engine/State.hpp"

/**
 * Create a state in the state charts and display it
 */
void Canvas::addState(std::string name, int posX, int posY)
{
    unsigned int id = state_chart.addState(name);
    StateUI* state = new StateUI(this, state_chart.getState(id), posX, posY);
    this->states.push_back(state);
    this->setStyleSheet("background-color: white");
}
