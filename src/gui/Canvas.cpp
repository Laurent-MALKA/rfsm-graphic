#include <numeric>

#include "Canvas.hpp"
#include "../engine/State.hpp"
#include "StateUI.hpp"
#include "MainWindow.hpp"

Canvas::Canvas(QWidget* parent) : QFrame(parent)
{}

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

void Canvas::setCurrentTool(Tool* tool)
{
    current_tool = tool;
}

/**
 * Do the action of the selected tool
 */
void Canvas::mousePressEvent(QMouseEvent *event)
{
    current_tool->act(event);
}
