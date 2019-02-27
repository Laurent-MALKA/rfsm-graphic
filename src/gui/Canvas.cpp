#include "Canvas.hpp"
#include "../engine/State.hpp"
#include "MainWindow.hpp"
#include "StateUI.hpp"

#include <QGraphicsScene>
#include <iostream>
#include <numeric>
#include <stdexcept>

Canvas::Canvas(MainWindow* parent) : QGraphicsScene(parent)
{
    main_window = parent;

    state_chart = new StateChart();

    setSceneRect(QRectF(0, 0, 5000, 5000));
}

Canvas::~Canvas()
{
    delete state_chart;
    for(auto& state : states)
        delete state;
    for(auto& transition : transitions)
        delete transition;
}

StateChart* Canvas::getStateChart()
{
    return state_chart;
}

const std::vector<StateUI*> Canvas::getStates() const
{
    return states;
}

std::vector<StateUI*> Canvas::getStates()
{
    return states;
}

/**
 * Create a state in the state charts and display it
 */
StateUI* Canvas::addState(double posX, double posY)
{
    std::string name =
        std::string("state_") + std::to_string(State::getStatesCounter());
    unsigned int id = state_chart->addState(name);
    StateUI* state = new StateUI(state_chart->getState(id), posX, posY);
    this->states.push_back(state);

    addItem(state);

    return state;
}

TransitionUI* Canvas::addTransition(StateUI* start_state, StateUI* end_state)
{
    int start_state_id = start_state->getState().getId();
    int end_state_id = end_state->getState().getId();

    unsigned int id = state_chart->addTransition(start_state_id, end_state_id);
    TransitionUI* transition = new TransitionUI(
        state_chart->getTransition(id), start_state, end_state);
    this->transitions.push_back(transition);

    addItem(transition);

    return transition;
}

void Canvas::deleteState(int state_id)
{
    auto state = states.begin();

    for(; state != states.end() && (*state)->getState().getId() != state_id;
        state++)
        continue;

    if(state == states.end())
        throw std::invalid_argument("State ID not found");

    for(int i = 0; i < transitions.size(); i++)
    {
        if(transitions[i]->getStartState().getState().getId() == state_id
           || transitions[i]->getEndState().getState().getId() == state_id)
        {
            delete transitions[i];
            transitions.erase(transitions.begin() + i);
            i--;
        }
    }
    delete *state;
    states.erase(state);

    state_chart->deleteState(state_id);
}

void Canvas::deleteTransition(int transition_id)
{
    auto transition = transitions.begin();

    for(; transition != transitions.end()
          && (*transition)->getTransition().getId() != transition_id;
        transition++)
        continue;

    if(transition == transitions.end())
        throw std::invalid_argument("Transition ID not found");

    delete *transition;
    transitions.erase(transition);

    state_chart->deleteTransition(transition_id);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    main_window->getCurrentTool()->pressAct(event);
    QGraphicsScene::mousePressEvent(event);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    main_window->getCurrentTool()->releaseAct(event);
    QGraphicsScene::mouseReleaseEvent(event);
}

void Canvas::setStatesFlag(QGraphicsItem::GraphicsItemFlag flag, bool enabled)
{
    for(auto& state : states)
    {
        state->setFlag(flag, enabled);
    }
}

void Canvas::setTransitionsFlag(QGraphicsItem::GraphicsItemFlag flag,
                                bool enabled)
{
    for(auto& transition : transitions)
    {
        transition->setFlag(flag, enabled);
    }
}