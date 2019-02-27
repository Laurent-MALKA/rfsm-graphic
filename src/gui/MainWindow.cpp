#include "MainWindow.hpp"
#include "Canvas.hpp"
#include "PropertiesPanel.hpp"
#include "Tools.hpp"

#include <QApplication>
#include <QComboBox>
#include <QGraphicsView>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

MainWindow::MainWindow()
{
    setWindowTitle("RFSM Graphic");
    resize(1280, 720);

    createMenu();
    createCentralWidget();
    tools[ToolEnum::select] = new SelectTool(this);
    tools[ToolEnum::add_state] = new AddStateTool(this);
    tools[ToolEnum::set_initial_state] = new SetInitialStateTool(this);
    tools[ToolEnum::add_transition] = new AddTransitionTool(this);
    tools[ToolEnum::deletion] = new DeletionTool(this);
    setCurrentTool(ToolEnum::add_state);
}

MainWindow::~MainWindow()
{
    for(auto& tool : tools)
        delete tool.second;
}

Tool* MainWindow::getCurrentTool()
{
    return current_tool;
}

void MainWindow::setCurrentTool(Tool* tool)
{
    current_tool = tool;
}

Canvas* MainWindow::getCanvas()
{
    return canvas;
}

PropertiesPanel* MainWindow::getPropertiesPanel()
{
    return properties_panel;
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
    new_file_action =
        file_menu->addAction("&New", this, SLOT(newFile()), QKeySequence::New);
    open_file_action = file_menu->addAction(
        "&Open", this, SLOT(openFile()), QKeySequence::Open);
    save_file_action =
        file_menu->addAction("&Save", this, SLOT(save()), QKeySequence::Save);
    save_as_file_action = file_menu->addAction(
        "&Save As", this, SLOT(saveAs()), QKeySequence("Ctrl+Shift+S"));
    export_content_action = file_menu->addAction(
        "&Export", this, SLOT(exportContent()), QKeySequence("Ctrl+E"));
    exit_action = file_menu->addAction(
        "&Exit", this, SLOT(close()), QKeySequence("Ctrl+Q"));

    undo_action =
        edit_menu->addAction("&Undo", this, SLOT(undo()), QKeySequence::Undo);
    redo_action =
        edit_menu->addAction("&Redo", this, SLOT(redo()), QKeySequence::Redo);
}

/**
 * Init the central widget
 */
void MainWindow::createCentralWidget()
{
    central_widget = new QWidget();

    QHBoxLayout* main_layout = new QHBoxLayout();

    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    createToolBar();
    main_layout->addWidget(tool_bar);
    createCanvas();
    view = new QGraphicsView(canvas);
    view->centerOn(QPointF(0, 0));
    main_layout->addWidget(view);
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
QPushButton* MainWindow::createPushButton(const std::string& label,
                                          const std::string& icon_path)
{
    QPushButton* button = new QPushButton;
    button->setToolTip(label.c_str());
    button->setIcon(QIcon(icon_path.c_str()));
    button->setMinimumSize(32, 32);
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
    tool_bar->setFixedWidth(32);

    // Init the layout of the tool_bar
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(8);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create all buttons
    QPushButton* select_tool =
        createPushButton("Selection", "../assets/select.svg");
    QPushButton* set_initial_state_tool =
        createPushButton("Initial State", "../assets/init_state.svg");
    QPushButton* add_state_tool =
        createPushButton("State", "../assets/state.svg");
    QPushButton* add_transition_tool =
        createPushButton("Transition", "../assets/transition.svg");
    QPushButton* deletion_tool =
        createPushButton("Delete", "../assets/delete.svg");

    // Bind button to the layout
    layout->addWidget(select_tool);
    layout->addWidget(set_initial_state_tool);
    layout->addWidget(add_state_tool);
    layout->addWidget(add_transition_tool);
    layout->addWidget(deletion_tool);

    tool_bar->setLayout(layout);

    // connect events
    connect(select_tool, &QPushButton::clicked, this, [this]() {
        setCurrentTool(ToolEnum::select);
    });
    connect(set_initial_state_tool, &QPushButton::clicked, this, [this](){
    setCurrentTool(ToolEnum::set_initial_state); });
    connect(add_state_tool, &QPushButton::clicked, this, [this]() {
        setCurrentTool(ToolEnum::add_state);
    });
    connect(add_transition_tool, &QPushButton::clicked, this, [this]() {
        setCurrentTool(ToolEnum::add_transition);
    });
    connect(deletion_tool, &QPushButton::clicked, this, [this]() {
        setCurrentTool(ToolEnum::deletion);
    });
}

void MainWindow::createCanvas()
{
    canvas = new Canvas(this);
}

void MainWindow::createPropertiesPanel()
{
    properties_panel = new PropertiesPanel(this);
    properties_panel->setMinimumWidth(240);
    properties_panel->setMaximumWidth(360);
}

/**
 * Create the treeview pannel
 */
// QGroupBox* MainWindow::createTreeView()
// {
//     QGroupBox* treePanel = new QGroupBox("Tree view");
//     QVBoxLayout* treePanelLayout = new QVBoxLayout();

//     QTreeView* treeView = new QTreeView();

//     treePanelLayout->addWidget(treeView);
//     treePanel->setLayout(treePanelLayout);

//     return treePanel;
// }

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
    tool_bar->setCursor(current_tool->getCursor());
    view->setCursor(current_tool->getCursor());
    if(tool == ToolEnum::select)
    {
        canvas->setStatesFlag(QGraphicsItem::ItemIsMovable, true);
        canvas->setStatesFlag(QGraphicsItem::ItemIsSelectable, true);
        canvas->setTransitionsFlag(QGraphicsItem::ItemIsSelectable, true);
    }
    else
    {
        canvas->setStatesFlag(QGraphicsItem::ItemIsMovable, false);
        canvas->setStatesFlag(QGraphicsItem::ItemIsSelectable, false);
        canvas->setTransitionsFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}
