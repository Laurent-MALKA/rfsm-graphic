#include "PropertiesPanel.hpp"
#include "MainWindow.hpp"
#include "StateUI.hpp"
#include "TransitionUI.hpp"

#include <QComboBox>
#include <QFrame>
#include <QGraphicsItem>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>
#include <stdexcept>

PropertiesPanel::PropertiesPanel(MainWindow* parent) : QFrame(parent)
{
    main_window = parent;

    createStatePanel();
    createTransitionPanel();
    // createInputVariablePanel();
    // createOutputVariablePanel();
    // createInternVariablePanel();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(state_panel);
    layout->addWidget(transition_panel);
    layout->addWidget(input_variable_panel);

    this->setLayout(layout);

    connect(state_name_field,
            &QLineEdit::textEdited,
            this,
            &PropertiesPanel::setStateName);
    connect(transition_start_state_field,
            QOverload<int>::of(&QComboBox::activated),
            this,
            &PropertiesPanel::setTransitionStartState);
    connect(transition_end_state_field,
            QOverload<int>::of(&QComboBox::activated),
            this,
            &PropertiesPanel::setTransitionEndState);
    connect(transition_condition_field,
            &QLineEdit::textEdited,
            this,
            &PropertiesPanel::setTransitionCondition);
    connect(transition_action_field,
            &QLineEdit::textEdited,
            this,
            &PropertiesPanel::setTransitionAction);
}

void PropertiesPanel::unselectItem()
{
    selected_item = nullptr;
    state_panel->hide();
    transition_panel->hide();
}

void PropertiesPanel::setSelectedItem(QGraphicsItem* item)
{
    switch(item->type())
    {
        case StateUI::Type:
            setSelectedItem(dynamic_cast<StateUI*>(item));
            break;

        case TransitionUI::Type:
            setSelectedItem(dynamic_cast<TransitionUI*>(item));
            break;

        default:
            break;
    }
}

void PropertiesPanel::setSelectedItem(StateUI* state)
{
    selected_item = state;

    transition_panel->hide();
    state_panel->show();

    state_name_field->setText(state->getState().getName().c_str());
}

void PropertiesPanel::setSelectedItem(TransitionUI* transition)
{
    selected_item = transition;
    state_panel->hide();
    transition_panel->show();

    transition_start_state_field->clear();
    transition_end_state_field->clear();

    for(auto& stateUI : main_window->getCanvas()->getStates())
    {
        auto state = stateUI->getState();

        transition_start_state_field->addItem(state.getName().c_str(),
                                              QVariant(state.getId()));
        transition_end_state_field->addItem(state.getName().c_str(),
                                            QVariant(state.getId()));

        if(transition->getStartState().getState().getId() == state.getId())
            transition_start_state_field->setCurrentIndex(
                transition_start_state_field->count() - 1);

        if(transition->getEndState().getState().getId() == state.getId())
            transition_end_state_field->setCurrentIndex(
                transition_end_state_field->count() - 1);
    }

    transition_condition_field->setText(
        transition->getTransition().getCondition().c_str());

    transition_action_field->setText(
        transition->getTransition().getAction().c_str());
}

void PropertiesPanel::setStateName(const QString& name)
{
    auto state = dynamic_cast<StateUI*>(selected_item);
    if(state != nullptr)
    {
        state->getState().setName(name.toStdString());
    }
}

void PropertiesPanel::setTransitionStartState(int index)
{
    if(index == -1)
        return;

    auto transition = dynamic_cast<TransitionUI*>(selected_item);
    if(transition != nullptr)
    {
        int state_id = transition_start_state_field->itemData(index).toInt();

        auto states = main_window->getCanvas()->getStates();
        StateUI* state = nullptr;
        for(auto& stateUI : states)
        {
            if(stateUI->getState().getId() == state_id)
            {
                state = stateUI;
                break;
            }
        }

        if(state != nullptr)
            transition->setStartState(state);
        else
            throw std::invalid_argument("Wrong state id");
    }
}

void PropertiesPanel::setTransitionEndState(int index)
{
    if(index == -1)
        return;

    auto transition = dynamic_cast<TransitionUI*>(selected_item);
    if(transition != nullptr)
    {
        int state_id = transition_end_state_field->itemData(index).toInt();

        auto states = main_window->getCanvas()->getStates();
        StateUI* state = nullptr;
        for(auto& stateUI : states)
        {
            if(stateUI->getState().getId() == state_id)
            {
                state = stateUI;
                break;
            }
        }

        if(state != nullptr)
            transition->setEndState(state);
        else
            throw std::invalid_argument("Wrong state id");
    }
}

void PropertiesPanel::setTransitionCondition(const QString& condition)
{
    auto transition = dynamic_cast<TransitionUI*>(selected_item);
    if(transition != nullptr)
    {
        transition->getTransition().setCondition(
            condition.toStdString().c_str());
    }
}

void PropertiesPanel::setTransitionAction(const QString& action)
{
    auto transition = dynamic_cast<TransitionUI*>(selected_item);
    if(transition != nullptr)
    {
        transition->getTransition().setAction(action.toStdString().c_str());
    }
}

void PropertiesPanel::createStatePanel()
{
    state_panel = new QGroupBox("State settings");
    QVBoxLayout* statePanelLayout = new QVBoxLayout();

    // Name input
    QLabel* nameLabel = new QLabel("Name");
    state_name_field = new QLineEdit();

    statePanelLayout->addWidget(nameLabel);
    statePanelLayout->addWidget(state_name_field);

    state_panel->setLayout(statePanelLayout);

    state_panel->hide();
}

void PropertiesPanel::createTransitionPanel()
{
    transition_panel = new QGroupBox("Transition settings");
    QVBoxLayout* transitionLayout = new QVBoxLayout();

    // Group start and end transition state
    QLabel* startLabel = new QLabel("Starting Node");
    transition_start_state_field = new QComboBox();
    transitionLayout->addWidget(startLabel);
    transitionLayout->addWidget(transition_start_state_field);
    QLabel* endLabel = new QLabel("Ending Node");
    transition_end_state_field = new QComboBox();
    transitionLayout->addWidget(endLabel);
    transitionLayout->addWidget(transition_end_state_field);

    // Conditions input
    QLabel* conditionLabel = new QLabel("Conditions");
    transition_condition_field = new QLineEdit();
    transitionLayout->addWidget(conditionLabel);
    transitionLayout->addWidget(transition_condition_field);

    // Actions input
    QLabel* actionLabel = new QLabel("Actions");
    transition_action_field = new QLineEdit();
    transitionLayout->addWidget(actionLabel);
    transitionLayout->addWidget(transition_action_field);

    transition_panel->setLayout(transitionLayout);

    transition_panel->hide();
}
