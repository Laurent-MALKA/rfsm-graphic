#include "Canvas.hpp"
#include "../../includes/nlohmann_json.hpp"
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
    free();
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

    update();

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

    update();

    return transition;
}

void Canvas::deleteState(int state_id)
{
    auto state = states.begin();

    for(; state != states.end() && (*state)->getState().getId() != state_id;
        state++)
        continue;

    if(state == states.end())
        throw std::invalid_argument(std::string("No state found with id : ")
                                    + std::to_string(state_id));

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
    removeItem(*state);
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
        throw std::invalid_argument(
            std::string("No transition found with id : ")
            + std::to_string(transition_id));

    removeItem(*transition);
    delete *transition;
    transitions.erase(transition);

    state_chart->deleteTransition(transition_id);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        main_window->getCurrentTool()->pressAct(event);
    }
    QGraphicsScene::mousePressEvent(event);

    update();
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        main_window->getCurrentTool()->releaseAct(event);
    }
    QGraphicsScene::mouseReleaseEvent(event);

    update();
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

void Canvas::importCanvas(const std::string& json_data)
{
    auto json_file = nlohmann::json::parse(json_data);

    std::unique_ptr<StateChart> new_state_chart(new StateChart);
    std::vector<std::unique_ptr<StateUI>> new_states;
    std::vector<std::unique_ptr<TransitionUI>> new_transitions;

    new_states.reserve(json_file.at("states").size());

    for(const auto& json_state_ui : json_file.at("states"))
    {
        auto json_state = json_state_ui.at("state");
        int state_id = new_state_chart->addState(json_state.at("name"),
                                                 json_state.at("id"));
        new_states.emplace_back(new StateUI(new_state_chart->getState(state_id),
                                            json_state_ui.at("x"),
                                            json_state_ui.at("y")));
    }

    new_transitions.reserve(json_file.at("transitions").size());

    for(const auto& json_transition_ui : json_file.at("transitions"))
    {
        int start_id = json_transition_ui.at("start_state_id");
        int end_id = json_transition_ui.at("end_state_id");
        std::string condition = json_transition_ui.at("condition");
        std::string action = json_transition_ui.at("action");

        unsigned int transition_id =
            new_state_chart->addTransition(start_id, end_id, condition, action);

        StateUI* start_state = nullptr;
        StateUI* end_state = nullptr;

        auto it = new_states.begin();

        for(; it != new_states.end()
              && (start_state == nullptr || end_state == nullptr);
            it++)
        {
            if((*it)->getState().getId() == start_id)
                start_state = it->get();
            if((*it)->getState().getId() == end_id)
                end_state = it->get();
        }
        if(start_state == nullptr)
            throw std::invalid_argument("No start state found with id : "
                                        + std::to_string(start_id));
        if(end_state == nullptr)
            throw std::invalid_argument("No end state found with id : "
                                        + std::to_string(start_id));

        new_transitions.emplace_back(
            new TransitionUI(new_state_chart->getTransition(transition_id),
                             start_state,
                             end_state));
    }

    for(const auto& json_input_variable : json_file.at("input_variables"))
    {
        new_state_chart->addInputVariable(json_input_variable.at("name"),
                                          json_input_variable.at("type"),
                                          json_input_variable.at("stimuli"));
    }

    for(const auto& json_output_variable : json_file.at("output_variables"))
    {
        new_state_chart->addOutputVariable(json_output_variable.at("name"),
                                           json_output_variable.at("type"));
    }

    for(const auto& json_inout_variable : json_file.at("inout_variables"))
    {
        new_state_chart->addInoutVariable(json_inout_variable.at("name"),
                                          json_inout_variable.at("type"));
    }

    for(const auto& json_intern_variable : json_file.at("intern_variables"))
    {
        new_state_chart->addInternVariable(json_intern_variable.at("name"),
                                           json_intern_variable.at("type"));
    }

    free();

    state_chart = new_state_chart.release();

    states.reserve(new_states.size());
    for(auto& new_state : new_states)
    {
        states.push_back(new_state.release());
        addItem(states.back());
    }

    transitions.reserve(new_transitions.size());
    for(auto& new_transition : new_transitions)
    {
        transitions.push_back(new_transition.release());
        addItem(transitions.back());
    }

    update();
}

std::string Canvas::exportCanvas()
{
    nlohmann::json json_res;

    // Fill states properties
    json_res["states"] = nlohmann::json::array();
    for(const auto& state_ui : states)
    {
        const auto& state = state_ui->getState();

        nlohmann::json json_state_ui;

        json_state_ui["x"] =
            state_ui->x() + int(state_ui->boundingRect().width() / 2);
        json_state_ui["y"] =
            state_ui->y() + int(state_ui->boundingRect().height() / 2);

        nlohmann::json json_state;
        json_state["id"] = state.getId();
        json_state["name"] = state.getName();

        json_state_ui["state"] = json_state;

        json_res["states"].push_back(json_state_ui);
    }

    json_res["transitions"] = nlohmann::json::array();
    for(const auto& transition_ui : transitions)
    {
        const auto& transition = transition_ui->getTransition();
        nlohmann::json json_transition;

        json_transition["id"] = transition.getId();
        json_transition["start_state_id"] = transition.getStartStateId();
        json_transition["end_state_id"] = transition.getEndStateId();
        json_transition["condition"] = transition.getCondition();
        json_transition["action"] = transition.getAction();

        json_res["transitions"].push_back(json_transition);
    }

    json_res["input_variables"] = nlohmann::json::array();
    for(const auto& input_variable : state_chart->getInputVariables())
    {
        nlohmann::json json_input_variable;
        json_input_variable["type"] = input_variable->getType();
        json_input_variable["name"] = input_variable->getName();
        json_input_variable["stimuli"] = input_variable->getStimuli();

        json_res["input_variables"].push_back(json_input_variable);
    }

    json_res["output_variables"] = nlohmann::json::array();
    for(const auto& output_variable : state_chart->getOutputVariables())
    {
        nlohmann::json json_output_variable;
        json_output_variable["type"] = output_variable->getType();
        json_output_variable["name"] = output_variable->getName();

        json_res["output_variables"].push_back(json_output_variable);
    }

    json_res["inout_variables"] = nlohmann::json::array();
    for(const auto& inout_variable : state_chart->getInoutVariables())
    {
        nlohmann::json json_inout_variable;
        json_inout_variable["type"] = inout_variable->getType();
        json_inout_variable["name"] = inout_variable->getName();

        json_res["inout_variables"].push_back(json_inout_variable);
    }

    json_res["intern_variables"] = nlohmann::json::array();
    for(const auto& intern_variable : state_chart->getInternVariables())
    {
        nlohmann::json json_intern_variable;
        json_intern_variable["type"] = intern_variable->getType();
        json_intern_variable["name"] = intern_variable->getName();

        json_res["intern_variables"].push_back(json_intern_variable);
    }

    return json_res.dump(4);
}

void Canvas::selectAllItems()
{
    for(auto& item : items())
    {
        item->setSelected(true);
    }
}

void Canvas::deleteSelectedItems()
{
    QList<QGraphicsItem*> items = selectedItems();
    while(!items.isEmpty())
    {
        auto current_item = items.front();

        if(current_item->type() == StateUI::Type)
        {
            auto state = dynamic_cast<StateUI*>(current_item);
            deleteState(state->getState().getId());
        }
        else if(current_item->type() == TransitionUI::Type)
        {
            auto transition = dynamic_cast<TransitionUI*>(current_item);
            deleteTransition(transition->getTransition().getId());
        }

        items = selectedItems();
    }
}

void Canvas::clear()
{
    free();

    state_chart = new StateChart();

    update();
}

void Canvas::free()
{
    QGraphicsScene::clear();

    states.clear();
    transitions.clear();

    delete state_chart;
    state_chart = nullptr;
}
