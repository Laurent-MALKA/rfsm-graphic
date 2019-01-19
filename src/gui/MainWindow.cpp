#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>

#include <QVBoxLayout>
#include <QPushButton>
#include <QSignalMapper>

#include "MainWindow.hpp"
#include "Tools.hpp"

MainWindow::MainWindow() : QMainWindow() {
    setWindowTitle("RFSM Graphic");
    resize(1280, 720);

    createMenu();
    createCentralWidget();
    //tools[ToolEnum::select] = new SelectTool(canvas);
    tools[ToolEnum::add_state] = new AddStateTool(canvas);
    // tools[ToolEnum::set_initial_state] = new SetInitialStateTool(canvas);
    // tools[ToolEnum::add_transition] = new AddTransitionTool(canvas);
    // tools[ToolEnum::deletion] = new DeletionTool(canvas);
    setCurrentTool(ToolEnum::add_state);
}

// Tool* MainWindow::getCurrentTool() const
// {
//     return current_tool;
// }

void MainWindow::setCurrentTool(Tool* tool)
{
    current_tool = tool;
    canvas->setCurrentTool(tool);
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
    QPushButton* select_tool = createPushButton("Selection", "../assets/select.svg");
    QPushButton* set_initial_state_tool = createPushButton("Initial State", "../assets/init_state.svg");
    QPushButton* add_state_tool = createPushButton("State", "../assets/state.svg");
    QPushButton* add_transition_tool = createPushButton("Transition", "../assets/transition.svg");
    QPushButton* deletion_tool = createPushButton("Delete", "../assets/delete.svg");

    // Bind button to the layout
    layout->addWidget(select_tool);
    layout->addWidget(set_initial_state_tool);
    layout->addWidget(add_state_tool);
    layout->addWidget(add_transition_tool);
    layout->addWidget(deletion_tool);

    tool_bar->setLayout(layout);

    //connect events
    //connect(select_tool, &QPushButton::clicked, this, [this](){ setCurrentTool(ToolEnum::select); });
    //connect(initial_state_tool, &QPushButton::clicked, this, [this](){ setCurrentTool(ToolEnum::set_initial_state); });
    connect(add_state_tool, &QPushButton::clicked, this, [this](){ setCurrentTool(ToolEnum::add_state); });
    //connect(add_transition_tool, &QPushButton::clicked, this, [this](){ setCurrentTool(ToolEnum::add_transition); });
    //connect(deletion_tool, &QPushButton::clicked, this, [this](){ setCurrentTool(ToolEnum::deletion); });
}

void MainWindow::createCanvas()
{
    canvas = new Canvas(this);
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
    setCurrentTool(tools[tool]);
    central_widget->setCursor(current_tool->getCursor());
}