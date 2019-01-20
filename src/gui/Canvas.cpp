#include <numeric>

#include "Canvas.hpp"
#include "../engine/State.hpp"
#include "StateUI.hpp"
#include "MainWindow.hpp"

Canvas::Canvas(QWidget* parent) : QFrame(parent)
{}

const std::vector<StateUI*> Canvas::getStates() const
{
    return states;
}

/**
 * Create a state in the state charts and display it
 */
StateUI* Canvas::addState(float posX, float posY)
{
    std::string name = std::string("state_") + std::to_string(states.size());
    unsigned int id = state_chart.addState(name);
    StateUI* state = new StateUI(this, state_chart.getState(id), posX, posY);
    this->states.push_back(state);

    return state;
}
