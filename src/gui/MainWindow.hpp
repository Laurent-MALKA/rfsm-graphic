#ifndef RFSM_GRAPHIC_MAINWINDOW_HPP
#define RFSM_GRAPHIC_MAINWINDOW_HPP

#include <string>
#include <map>

#include <QMainWindow>
#include <QMenuBar>
#include <QFrame>
#include <QPushButton>

#include "Canvas.hpp"


class Tool;

enum class ToolEnum {select, initial_state, add_state, add_transition, deletion};

class MainWindow : public QMainWindow
{

Q_OBJECT

private:
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

    QWidget *central_widget;
    QFrame *tool_bar;
    Canvas *canvas;
    QFrame *properties_panel;

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

    //Tool* getCurrentTool() const;
    void setCurrentTool(Tool* tool);

private:
    void createCentralWidget();
    void createMenu();
    QPushButton* createPushButton(std::string label, std::string icon_path);
    void createToolBar();
    void createCanvas();
    void createPropertiesPanel();

};


#endif
