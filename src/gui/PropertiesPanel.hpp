#ifndef PROPERTIES_PANEL_HPP_INCLUDED
#define PROPERTIES_PANEL_HPP_INCLUDED

#include <QComboBox>
#include <QFrame>
#include <QGraphicsItem>
#include <QGroupBox>
#include <QLineEdit>
#include <QString>

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

    // QGroupBox* input_variable_panel;
    // QGroupBox* output_variable_panel;
    // QGroupBox* intern_variable_panel;

  public:
    PropertiesPanel(MainWindow* parent);
    ~PropertiesPanel() = default;

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

  private:
    void createStatePanel();
    void createTransitionPanel();
    // void createInputVariablePanel();
    // void createOutputVariablePanel();
    // void createInternVariablePanel();
};

#endif