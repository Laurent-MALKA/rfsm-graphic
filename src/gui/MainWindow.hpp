#ifndef RFSM_GRAPHIC_MAINWINDOW_HPP
#define RFSM_GRAPHIC_MAINWINDOW_HPP

#include "Canvas.hpp"
#include "PropertiesPanel.hpp"
#include "Tools.hpp"

#include <QFrame>
#include <QGroupBox>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <map>
#include <string>

class Tool;
class QGraphicsView;

enum class ToolEnum
{
    select,
    set_initial_state,
    add_state,
    add_transition,
    deletion
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

  private:
    QMenuBar* menu_bar;

    QMenu* file_menu;
    QAction* new_file_action;
    QAction* open_file_action;
    QAction* save_file_action;
    QAction* save_as_file_action;
    QAction* export_content_action;
    QAction* exit_action;

    QMenu* edit_menu;
    QAction* undo_action;
    QAction* redo_action;

    QMenu* help_menu;
    QAction* about_action;

    QWidget* central_widget;
    QFrame* tool_bar;
    Canvas* canvas;
    QGraphicsView* view;
    PropertiesPanel* properties_panel;

    Tool* current_tool;
    std::map<ToolEnum, Tool*> tools;

  public slots:
    void newFile();
    void openFile();
    void save();
    void saveAs();
    void exportContent();
    void undo();
    void redo();

    void setCurrentTool(ToolEnum tool);

  public:
    MainWindow();
    ~MainWindow();

    Tool* getCurrentTool();
    void setCurrentTool(Tool* tool);

    Canvas* getCanvas();
    PropertiesPanel* getPropertiesPanel();

    // void mousePressEvent(QMouseEvent *event);

  private:
    void createCentralWidget();
    void createMenu();
    QPushButton* createPushButton(const std::string& label,
                                  const std::string& icon_path);
    void createToolBar();
    void createCanvas();
    void createPropertiesPanel();
    QGroupBox* createTreeView();
    QGroupBox* createStatePanel();
    QGroupBox* createTransitionPanel();
    QGroupBox* createInputVariablePanel();
    QGroupBox* createOutputVariablePanel();
    QGroupBox* createInternVariablePanel();
};

#endif
