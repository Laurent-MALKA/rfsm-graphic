#ifndef RFSM_GRAPHIC_MAINWINDOW_HPP
#define RFSM_GRAPHIC_MAINWINDOW_HPP

#include <string>

#include <QMainWindow>
#include <QMenuBar>
#include <QFrame>
#include <QPushButton>

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

    QFrame *tool_bar;
    QFrame *canevas;
    QFrame *properties_panel;

public slots:
    void newFile();
    void openFile();
    void save();
    void saveAs();
    void exportContent();
    void undo();
    void redo();

public:
    MainWindow();

private:
    void createCentralWidget();
    void createMenu();
    QPushButton* createPushButton(std::string label, std::string icon_path);
    void createToolBar();
    void createCanevas();
    void createPropertiesPanel();

};


#endif
