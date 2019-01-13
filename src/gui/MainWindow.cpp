#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>

#include <QVBoxLayout>
#include <QPushButton>
#include <QSignalMapper>

#include "MainWindow.hpp"

MainWindow::MainWindow() : QMainWindow() {
    setWindowTitle("RFSM Graphic");
    resize(1280, 720);

    createMenu();
    createCentralWidget();
    current_tool = new AddStateTool(canvas);
}

/**
 * Generate the menu
 */
void MainWindow::createMenu()
{
    // Setup the menubar
    file_menu = menuBar()->addMenu("&File");
    edit_menu = menuBar()->addMenu("&Edit");
    help_menu = menuBar()->addMenu("&Help");

    // Init and bind action
    new_file_action = file_menu->addAction("&New", this, SLOT(newFile()), QKeySequence::New);
    open_file_action = file_menu->addAction("&Open", this, SLOT(openFile()), QKeySequence::Open);
    save_file_action = file_menu->addAction("&Save", this, SLOT(save()), QKeySequence::Save);
    save_as_file_action = file_menu->addAction("&Save As", this, SLOT(saveAs()), QKeySequence("Ctrl+Shift+S"));
    export_content_action = file_menu->addAction("&Export", this, SLOT(exportContent()), QKeySequence("Ctrl+E"));
    exit_action = file_menu->addAction("&Exit", this, SLOT(close()), QKeySequence("Ctrl+Q"));

    undo_action = edit_menu->addAction("&Undo", this, SLOT(undo()), QKeySequence::Undo);
    redo_action = edit_menu->addAction("&Redo", this, SLOT(redo()), QKeySequence::Redo);
}

/**
 * Init the central widget
 */
void MainWindow::createCentralWidget()
{
    central_widget = new QWidget();

    QHBoxLayout* main_layout = new QHBoxLayout();

    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0,0,0,0);

    createToolBar();
    main_layout->addWidget(tool_bar);
    createCanvas();
    main_layout->addWidget(canvas);
    createPropertiesPanel();
    main_layout->addWidget(properties_panel);

    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);
}

/**
 * Create a QPushButton
 * @param label
 * @param icon_path
 * @return
 */
QPushButton* MainWindow::createPushButton(std::string label, std::string icon_path) {

    QPushButton* button = new QPushButton;
    button->setToolTip(label.c_str());
    button->setIcon(QIcon(icon_path.c_str()));
    button->setMinimumSize(32,32);
    button->setFlat(true);

    return button;
}

/**
 * Generate tool bar
 */
 void MainWindow::createToolBar()
{
     // Create the tool_bar
    tool_bar = new QFrame();
    tool_bar->setStyleSheet("background-color: grey");
    tool_bar->setFixedWidth(32);

    // Init the layout of the tool_bar
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(8);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create all buttons
    QPushButton* select_tool = createPushButton("Sélection", "../assets/select.svg");
    QPushButton* state_tool = createPushButton("Etat", "../assets/state.svg");
    QPushButton* transition_tool = createPushButton("Transition", "../assets/transition.svg");

    // Bind button to the layout
    layout->addWidget(select_tool);
    layout->addWidget(state_tool);
    layout->addWidget(transition_tool);

    tool_bar->setLayout(layout);

    //connect events
    connect(select_tool, &QPushButton::clicked, this, [this](){ setCurrentTool(ToolEnum::select); });
    connect(state_tool, &QPushButton::clicked, this, [this](){ setCurrentTool(ToolEnum::state); });
    connect(transition_tool, &QPushButton::clicked, this, [this](){ setCurrentTool(ToolEnum::transition); });
}

void MainWindow::createCanvas()
{
    canvas = new Canvas();
    canvas->addState("state1", 100, 100);
}

void MainWindow::createPropertiesPanel()
{
    properties_panel = new QFrame();
    properties_panel->setFixedWidth(64);
    properties_panel->setStyleSheet("background: grey");
}

/**
 * Create a new file
 */
void MainWindow::newFile() {}

/**
 * Open a new file
 */
void MainWindow::openFile() {}

/**
 * Save the file
 */
void MainWindow::save() {}

/**
 * Save as the file
 */
void MainWindow::saveAs() {}

/**
 * Export the file
 */
void MainWindow::exportContent() {}

/**
 * Undo the last command
 */
void MainWindow::undo() {}

/**
 * Redo the last command
 */
void MainWindow::redo() {}

/**
 * Set the current tool for the canvas
 */
void MainWindow::setCurrentTool(ToolEnum tool)
{
    switch(tool)
    {
        case ToolEnum::select:
            break;
        case ToolEnum::state:
            break;
        case ToolEnum::transition:
            break;
    }
    central_widget->setCursor(current_tool->getCursor());
}