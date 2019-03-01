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
#include <QListView>
#include <QString>
#include <QStringList>
#include <QStringListModel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <stdexcept>

PropertiesPanel::PropertiesPanel(MainWindow* parent) : QFrame(parent)
{
    main_window = parent;

    createStatePanel();
    createTransitionPanel();

    createInternVariablePanel();
    createInputVariablePanel();
    createOutputVariablePanel();
    createInoutVariablePanel();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(state_panel);
    layout->addWidget(transition_panel);

    layout->addWidget(intern_variable_panel);
    layout->addWidget(input_variable_panel);
    layout->addWidget(output_variable_panel);
    layout->addWidget(inout_variable_panel);

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

PropertiesPanel::~PropertiesPanel()
{
    free();
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
        main_window->getCanvas()->update();
        main_window->setUnsavedChanges(true);
    }
}

void PropertiesPanel::setTransitionStartState(int index)
{
    if(index == -1)
        return;

    auto transition = dynamic_cast<TransitionUI*>(selected_item);

    if(transition == nullptr)
        throw std::invalid_argument("No transition selected");

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

    if(state == nullptr)
        throw std::invalid_argument(std::string("No state found with id : ")
                                    + std::to_string(state_id));

    transition->setStartState(state);

    main_window->getCanvas()->update();
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::setTransitionEndState(int index)
{
    if(index == -1)
        return;

    auto transition = dynamic_cast<TransitionUI*>(selected_item);

    if(transition == nullptr)
        throw std::invalid_argument("No transition selected");

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

    if(state == nullptr)
        throw std::invalid_argument(std::string("No state found with id : ")
                                    + std::to_string(state_id));

    transition->setEndState(state);

    main_window->getCanvas()->update();
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::setTransitionCondition(const QString& condition)
{
    auto transition = dynamic_cast<TransitionUI*>(selected_item);
    if(transition != nullptr)
    {
        transition->getTransition().setCondition(condition.toStdString());
        main_window->getCanvas()->update();
        main_window->setUnsavedChanges(true);
    }
}

void PropertiesPanel::setTransitionAction(const QString& action)
{
    auto transition = dynamic_cast<TransitionUI*>(selected_item);
    if(transition != nullptr)
    {
        transition->getTransition().setAction(action.toStdString());
        main_window->getCanvas()->update();
        main_window->setUnsavedChanges(true);
    }
}

void PropertiesPanel::addInternVariable()
{
    if(intern_variable_name->text() == "" || intern_variable_type->text() == "")
        return;

    StateChart* state_chart = main_window->getCanvas()->getStateChart();

    state_chart->addInternVariable(intern_variable_name->text().toStdString(),
                                   intern_variable_type->text().toStdString());

    QStringList string_list = intern_variables_model->stringList();
    string_list << intern_variable_name->text() + " : "
                       + intern_variable_type->text();
    intern_variables_model->setStringList(string_list);
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::removeInternVariables()
{
    QList<QModelIndex> model_indexes =
        intern_variables_view->selectionModel()->selectedIndexes();
    QList<int> indexes;
    for(auto& model_index : model_indexes)
        indexes.append(model_index.row());

    std::sort(indexes.begin(), indexes.end());

    QStringList string_list = intern_variables_model->stringList();
    StateChart* state_chart = main_window->getCanvas()->getStateChart();

    for(auto it = indexes.rbegin(); it != indexes.rend(); it++)
    {
        string_list.removeAt(*it);
        state_chart->removeInternVariable(*it);
    }

    intern_variables_model->setStringList(string_list);
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::addInputVariable()
{
    if(input_variable_name->text() == "" || input_variable_type->text() == ""
       || input_variable_stimuli->text() == "")
        return;

    StateChart* state_chart = main_window->getCanvas()->getStateChart();

    state_chart->addInputVariable(input_variable_name->text().toStdString(),
                                  input_variable_type->text().toStdString(),
                                  input_variable_stimuli->text().toStdString());

    QStringList string_list = input_variables_model->stringList();
    string_list << input_variable_name->text() + " : "
                       + input_variable_type->text() + " = "
                       + input_variable_stimuli->text();
    input_variables_model->setStringList(string_list);
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::removeInputVariables()
{
    QList<QModelIndex> model_indexes =
        input_variables_view->selectionModel()->selectedIndexes();

    QList<int> indexes;
    for(auto& model_index : model_indexes)
        indexes.append(model_index.row());

    std::sort(indexes.begin(), indexes.end());

    QStringList string_list = input_variables_model->stringList();
    StateChart* state_chart = main_window->getCanvas()->getStateChart();

    for(auto it = indexes.rbegin(); it != indexes.rend(); it++)
    {
        string_list.removeAt(*it);
        state_chart->removeInputVariable(*it);
    }

    input_variables_model->setStringList(string_list);
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::addOutputVariable()
{
    if(output_variable_name->text() == "" || output_variable_type->text() == "")
        return;

    StateChart* state_chart = main_window->getCanvas()->getStateChart();

    state_chart->addOutputVariable(output_variable_name->text().toStdString(),
                                   output_variable_type->text().toStdString());

    QStringList string_list = output_variables_model->stringList();
    string_list << output_variable_name->text() + " : "
                       + output_variable_type->text();
    output_variables_model->setStringList(string_list);
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::removeOutputVariables()
{
    QList<QModelIndex> model_indexes =
        output_variables_view->selectionModel()->selectedIndexes();

    QList<int> indexes;
    for(auto& model_index : model_indexes)
        indexes.append(model_index.row());

    std::sort(indexes.begin(), indexes.end());

    QStringList string_list = output_variables_model->stringList();
    StateChart* state_chart = main_window->getCanvas()->getStateChart();

    for(auto it = indexes.rbegin(); it != indexes.rend(); it++)
    {
        string_list.removeAt(*it);
        state_chart->removeOutputVariable(*it);
    }

    output_variables_model->setStringList(string_list);
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::addInoutVariable()
{
    if(inout_variable_name->text() == "" || inout_variable_type->text() == "")
        return;

    StateChart* state_chart = main_window->getCanvas()->getStateChart();

    state_chart->addInoutVariable(inout_variable_name->text().toStdString(),
                                  inout_variable_type->text().toStdString());

    QStringList string_list = inout_variables_model->stringList();
    string_list << inout_variable_name->text() + " : "
                       + inout_variable_type->text();
    inout_variables_model->setStringList(string_list);
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::removeInoutVariables()
{
    QList<QModelIndex> model_indexes =
        inout_variables_view->selectionModel()->selectedIndexes();

    QList<int> indexes;
    for(auto& model_index : model_indexes)
        indexes.append(model_index.row());

    std::sort(indexes.begin(), indexes.end());

    QStringList string_list = inout_variables_model->stringList();
    StateChart* state_chart = main_window->getCanvas()->getStateChart();

    for(auto it = indexes.rbegin(); it != indexes.rend(); it++)
    {
        string_list.removeAt(*it);
        state_chart->removeInoutVariable(*it);
    }

    inout_variables_model->setStringList(string_list);
    main_window->setUnsavedChanges(true);
}

void PropertiesPanel::clear()
{
    selected_item = nullptr;

    state_panel->hide();
    transition_panel->hide();

    fillVariablesLists();

    intern_variable_name->clear();
    intern_variable_type->clear();
    input_variable_name->clear();
    input_variable_type->clear();
    input_variable_stimuli->clear();
    output_variable_name->clear();
    output_variable_type->clear();
    inout_variable_name->clear();
    inout_variable_type->clear();
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
    QLabel* startLabel = new QLabel("Start State");
    transition_start_state_field = new QComboBox();
    transitionLayout->addWidget(startLabel);
    transitionLayout->addWidget(transition_start_state_field);
    QLabel* endLabel = new QLabel("End State");
    transition_end_state_field = new QComboBox();
    transitionLayout->addWidget(endLabel);
    transitionLayout->addWidget(transition_end_state_field);

    // Conditions input
    QLabel* conditionLabel = new QLabel("Condition");
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

/**
 * Create the intern variable pannel
 */
void PropertiesPanel::createInternVariablePanel()
{
    intern_variable_panel = new QGroupBox("Intern variables");
    QGridLayout* grid = new QGridLayout();

    // QLabel* variableLabel = new QLabel("Variables");
    grid->addWidget(new QLabel("Name"), 0, 0, 1, 3);
    grid->addWidget(new QLabel("Type"), 0, 3, 1, 3);

    intern_variable_name = new QLineEdit();
    intern_variable_type = new QLineEdit();
    grid->addWidget(intern_variable_name, 1, 0, 1, 3);
    grid->addWidget(intern_variable_type, 1, 3, 1, 3);

    QStringList intern_variables;
    for(auto& var :
        main_window->getCanvas()->getStateChart()->getInternVariables())
    {
        std::string res = var->getName() + " : " + var->getType();
        intern_variables << QString(res.c_str());
    }
    intern_variables_model = new QStringListModel(intern_variables);

    intern_variables_view = new QListView();
    intern_variables_view->setModel(intern_variables_model);
    intern_variables_view->setSelectionMode(
        QAbstractItemView::ExtendedSelection);
    grid->addWidget(intern_variables_view, 2, 0, 3, 6);

    QPushButton* add_button = new QPushButton("Add");
    QPushButton* remove_button = new QPushButton("Remove");

    grid->addWidget(add_button, 5, 0, 1, 3);
    grid->addWidget(remove_button, 5, 3, 1, 3);

    intern_variable_panel->setLayout(grid);

    connect(add_button,
            &QPushButton::clicked,
            this,
            &PropertiesPanel::addInternVariable);
    connect(intern_variable_type,
            &QLineEdit::returnPressed,
            this,
            &PropertiesPanel::addInternVariable);
    connect(remove_button,
            &QPushButton::clicked,
            this,
            &PropertiesPanel::removeInternVariables);
}

/**
 * Create the input variable pannel
 */
void PropertiesPanel::createInputVariablePanel()
{
    input_variable_panel = new QGroupBox("Input variables");
    QGridLayout* grid = new QGridLayout();

    // QLabel* variableLabel = new QLabel("Variables");
    grid->addWidget(new QLabel("Name"), 0, 0, 1, 2);
    grid->addWidget(new QLabel("Type"), 0, 2, 1, 2);
    grid->addWidget(new QLabel("Stimuli"), 0, 4, 1, 2);

    input_variable_name = new QLineEdit();
    input_variable_type = new QLineEdit();
    input_variable_stimuli = new QLineEdit();
    grid->addWidget(input_variable_name, 1, 0, 1, 2);
    grid->addWidget(input_variable_type, 1, 2, 1, 2);
    grid->addWidget(input_variable_stimuli, 1, 4, 1, 2);

    QStringList input_variables;
    for(auto& var :
        main_window->getCanvas()->getStateChart()->getInputVariables())
    {
        std::string res =
            var->getName() + " : " + var->getType() + " = " + var->getStimuli();
        input_variables << QString(res.c_str());
    }
    input_variables_model = new QStringListModel(input_variables);

    input_variables_view = new QListView();
    input_variables_view->setModel(input_variables_model);
    input_variables_view->setSelectionMode(
        QAbstractItemView::ExtendedSelection);
    grid->addWidget(input_variables_view, 2, 0, 3, 6);

    QPushButton* add_button = new QPushButton("Add");
    QPushButton* remove_button = new QPushButton("Remove");

    grid->addWidget(add_button, 5, 0, 1, 3);
    grid->addWidget(remove_button, 5, 3, 1, 3);

    input_variable_panel->setLayout(grid);

    connect(add_button,
            &QPushButton::clicked,
            this,
            &PropertiesPanel::addInputVariable);
    connect(input_variable_stimuli,
            &QLineEdit::returnPressed,
            this,
            &PropertiesPanel::addInputVariable);
    connect(remove_button,
            &QPushButton::clicked,
            this,
            &PropertiesPanel::removeInputVariables);
}

/**
 * Create the ouput variable pannel
 */
void PropertiesPanel::createOutputVariablePanel()
{
    output_variable_panel = new QGroupBox("Output variables");
    QGridLayout* grid = new QGridLayout();

    // QLabel* variableLabel = new QLabel("Variables");
    grid->addWidget(new QLabel("Name"), 0, 0, 1, 3);
    grid->addWidget(new QLabel("Type"), 0, 3, 1, 3);

    output_variable_name = new QLineEdit();
    output_variable_type = new QLineEdit();
    grid->addWidget(output_variable_name, 1, 0, 1, 3);
    grid->addWidget(output_variable_type, 1, 3, 1, 3);

    QStringList output_variables;
    for(auto& var :
        main_window->getCanvas()->getStateChart()->getOutputVariables())
    {
        std::string res = var->getName() + " : " + var->getType();
        output_variables << QString(res.c_str());
    }
    output_variables_model = new QStringListModel(output_variables);

    output_variables_view = new QListView();
    output_variables_view->setModel(output_variables_model);
    output_variables_view->setSelectionMode(
        QAbstractItemView::ExtendedSelection);
    grid->addWidget(output_variables_view, 2, 0, 3, 6);

    QPushButton* add_button = new QPushButton("Add");
    QPushButton* remove_button = new QPushButton("Remove");

    grid->addWidget(add_button, 5, 0, 1, 3);
    grid->addWidget(remove_button, 5, 3, 1, 3);

    output_variable_panel->setLayout(grid);

    connect(add_button,
            &QPushButton::clicked,
            this,
            &PropertiesPanel::addOutputVariable);
    connect(output_variable_type,
            &QLineEdit::returnPressed,
            this,
            &PropertiesPanel::addOutputVariable);
    connect(remove_button,
            &QPushButton::clicked,
            this,
            &PropertiesPanel::removeOutputVariables);
}

/**
 * Create the inout variable pannel
 */
void PropertiesPanel::createInoutVariablePanel()
{
    inout_variable_panel = new QGroupBox("Inout variables");
    QGridLayout* grid = new QGridLayout();

    // QLabel* variableLabel = new QLabel("Variables");
    grid->addWidget(new QLabel("Name"), 0, 0, 1, 3);
    grid->addWidget(new QLabel("Type"), 0, 3, 1, 3);

    inout_variable_name = new QLineEdit();
    inout_variable_type = new QLineEdit();
    grid->addWidget(inout_variable_name, 1, 0, 1, 3);
    grid->addWidget(inout_variable_type, 1, 3, 1, 3);

    QStringList inout_variables;
    for(auto& var :
        main_window->getCanvas()->getStateChart()->getInoutVariables())
    {
        std::string res = var->getName() + " : " + var->getType();
        inout_variables << QString(res.c_str());
    }
    inout_variables_model = new QStringListModel(inout_variables);

    inout_variables_view = new QListView();
    inout_variables_view->setModel(inout_variables_model);
    inout_variables_view->setSelectionMode(
        QAbstractItemView::ExtendedSelection);
    grid->addWidget(inout_variables_view, 2, 0, 3, 6);

    QPushButton* add_button = new QPushButton("Add");
    QPushButton* remove_button = new QPushButton("Remove");

    grid->addWidget(add_button, 5, 0, 1, 3);
    grid->addWidget(remove_button, 5, 3, 1, 3);

    inout_variable_panel->setLayout(grid);

    connect(add_button,
            &QPushButton::clicked,
            this,
            &PropertiesPanel::addInoutVariable);
    connect(inout_variable_type,
            &QLineEdit::returnPressed,
            this,
            &PropertiesPanel::addInoutVariable);
    connect(remove_button,
            &QPushButton::clicked,
            this,
            &PropertiesPanel::removeInoutVariables);
}

void PropertiesPanel::fillVariablesLists()
{
    QStringList intern_variables;
    for(auto& var :
        main_window->getCanvas()->getStateChart()->getInternVariables())
    {
        std::string res = var->getName() + " : " + var->getType();
        intern_variables << QString(res.c_str());
    }
    delete intern_variables_model;
    intern_variables_model = new QStringListModel(intern_variables);
    intern_variables_view->setModel(intern_variables_model);

    QStringList input_variables;
    for(auto& var :
        main_window->getCanvas()->getStateChart()->getInputVariables())
    {
        std::string res =
            var->getName() + " : " + var->getType() + " = " + var->getStimuli();
        input_variables << QString(res.c_str());
    }
    delete input_variables_model;
    input_variables_model = new QStringListModel(input_variables);
    input_variables_view->setModel(input_variables_model);

    QStringList output_variables;
    for(auto& var :
        main_window->getCanvas()->getStateChart()->getOutputVariables())
    {
        std::string res = var->getName() + " : " + var->getType();
        output_variables << QString(res.c_str());
    }
    delete output_variables_model;
    output_variables_model = new QStringListModel(output_variables);
    output_variables_view->setModel(output_variables_model);

    QStringList inout_variables;
    for(auto& var :
        main_window->getCanvas()->getStateChart()->getInoutVariables())
    {
        std::string res = var->getName() + " : " + var->getType();
        inout_variables << QString(res.c_str());
    }
    delete inout_variables_model;
    inout_variables_model = new QStringListModel(inout_variables);
    inout_variables_view->setModel(inout_variables_model);
}

void PropertiesPanel::free()
{
    delete intern_variables_model;
    delete input_variables_model;
    delete output_variables_model;
    delete inout_variables_model;
}
