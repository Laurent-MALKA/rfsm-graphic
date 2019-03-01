#ifndef PROPERTIES_PANEL_HPP_INCLUDED
#define PROPERTIES_PANEL_HPP_INCLUDED

#include <QComboBox>
#include <QFrame>
#include <QGraphicsItem>
#include <QGroupBox>
#include <QLineEdit>
#include <QListView>
#include <QString>
#include <QStringListModel>

class MainWindow;
class StateUI;
class TransitionUI;

class PropertiesPanel : public QFrame
{
    Q_OBJECT

  private:
    MainWindow* main_window;

    QGraphicsItem* selected_item;

    // QGroupBox* tree_panel;

    QGroupBox* state_panel;
    QLineEdit* state_name_field;

    QGroupBox* transition_panel;
    QComboBox* transition_start_state_field;
    QComboBox* transition_end_state_field;
    QLineEdit* transition_condition_field;
    QLineEdit* transition_action_field;

    QGroupBox* intern_variable_panel;
    QLineEdit* intern_variable_name;
    QLineEdit* intern_variable_type;
    QStringListModel* intern_variables_model;
    QListView* intern_variables_view;

    QGroupBox* input_variable_panel;
    QLineEdit* input_variable_name;
    QLineEdit* input_variable_type;
    QLineEdit* input_variable_stimuli;
    QStringListModel* input_variables_model;
    QListView* input_variables_view;

    QGroupBox* output_variable_panel;
    QLineEdit* output_variable_name;
    QLineEdit* output_variable_type;
    QStringListModel* output_variables_model;
    QListView* output_variables_view;

    QGroupBox* inout_variable_panel;
    QLineEdit* inout_variable_name;
    QLineEdit* inout_variable_type;
    QStringListModel* inout_variables_model;
    QListView* inout_variables_view;

  public:
    explicit PropertiesPanel(MainWindow* parent);
    ~PropertiesPanel();

    void unselectItem();
    void setSelectedItem(QGraphicsItem* item);
    void setSelectedItem(StateUI* state);
    void setSelectedItem(TransitionUI* transition);

  public slots:
    void setStateName(const QString& name);

    void setTransitionStartState(int index);
    void setTransitionEndState(int index);
    void setTransitionCondition(const QString& condition);
    void setTransitionAction(const QString& action);

    void addInternVariable();
    void removeInternVariables();

    void addInputVariable();
    void removeInputVariables();

    void addOutputVariable();
    void removeOutputVariables();

    void addInoutVariable();
    void removeInoutVariables();

    void clear();

  private:
    void createStatePanel();
    void createTransitionPanel();

    void createInternVariablePanel();
    void createInputVariablePanel();
    void createOutputVariablePanel();
    void createInoutVariablePanel();

    void fillVariablesLists();
    void free();
};

#endif