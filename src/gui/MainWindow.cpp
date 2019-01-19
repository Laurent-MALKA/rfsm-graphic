#include <iostream>
#include <QApplication>
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QTreeView>

#include "MainWindow.hpp"

MainWindow::MainWindow() : QMainWindow() {
    setWindowTitle("RFSM Graphic");
    resize(1280, 720);

    createMenu();
    createCentralWidget();
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
    QWidget* central_widget = new QWidget();

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
    tool_bar->setFixedWidth(32);

    // Init the layout of the tool_bar
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(8);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create all buttons
    QPushButton* select_tool = createPushButton("Selection", "../assets/select.svg");
    QPushButton* init_state_tool = createPushButton("Initial State", "../assets/init_state.svg");
    QPushButton* state_tool = createPushButton("State", "../assets/state.svg");
    QPushButton* transition_tool = createPushButton("Transition", "../assets/transition.svg");
    QPushButton* delete_tool = createPushButton("Delete", "../assets/delete.svg");

    // Bind button to the layout
    layout->addWidget(select_tool);
    layout->addWidget(init_state_tool);
    layout->addWidget(state_tool);
    layout->addWidget(transition_tool);
    layout->addWidget(delete_tool);

    tool_bar->setLayout(layout);
}

void MainWindow::createCanvas()
{
    canvas = new Canvas();
    canvas->setStyleSheet("background-color: white;");
}

void MainWindow::createPropertiesPanel()
{
    properties_panel = new QFrame();
    properties_panel->setMinimumWidth(240);
    properties_panel->setMaximumWidth(360);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(createTreeView());
    layout->addWidget(createStatePanel());
    layout->addWidget(createTransitionPanel());
    layout->addWidget(createInputVariablePanel());
    layout->addWidget(createOutputVariablePanel());
    layout->addWidget(createInternVariablePanel());

    properties_panel->setLayout(layout);
}

/**
 * Create the treeview pannel
 */
QGroupBox* MainWindow::createTreeView()
{
    QGroupBox* treePanel = new QGroupBox("Tree view");
    QVBoxLayout* treePanelLayout = new QVBoxLayout();

    QTreeView* treeView = new QTreeView();

    treePanelLayout->addWidget(treeView);
    treePanel->setLayout(treePanelLayout);

    return treePanel;
}

/**
 * Create the state pannel
 */
QGroupBox* MainWindow::createStatePanel()
{
    QGroupBox* statePanel = new QGroupBox("State settings");
    QVBoxLayout* statePanelLayout = new QVBoxLayout();

    // Name input
    QLabel* nameLabel = new QLabel("Name");
    QLineEdit* nameField = new QLineEdit();
    nameField->setPlaceholderText("Enter a name...");
    statePanelLayout->addWidget(nameLabel);
    statePanelLayout->addWidget(nameField);

    statePanel->setLayout(statePanelLayout);

    return statePanel;
}

/**
 * Create the transition pannel
 */
QGroupBox* MainWindow::createTransitionPanel()
{
    QGroupBox* transitionPanel = new QGroupBox("Transition settings");
    QVBoxLayout* transitionLayout = new QVBoxLayout();

    // Group start and end transition state
    QGroupBox* travelPanel = new QGroupBox("Transition travel");
    QHBoxLayout* travelLayout = new QHBoxLayout();
    QLabel* startLabel = new QLabel("Starting Node");
    QComboBox* startSelect = new QComboBox();
    travelLayout->addWidget(startLabel);
    travelLayout->addWidget(startSelect);
    QLabel* endLabel = new QLabel("Ending Node");
    QComboBox* endSelect = new QComboBox();
    travelLayout->addWidget(endLabel);
    travelLayout->addWidget(endSelect);
    travelPanel->setLayout(travelLayout);
    transitionLayout->addWidget(travelPanel);

    // Conditions input
    QLabel* conditionLabel = new QLabel("Conditions");
    QTextEdit* conditionArea = new QTextEdit();
    conditionArea->setPlaceholderText("Enter some conditions...");
    transitionLayout->addWidget(conditionLabel);
    transitionLayout->addWidget(conditionArea);

    // Actions input
    QLabel* actionLabel = new QLabel("Actions");
    QTextEdit* actionArea = new QTextEdit();
    actionArea->setPlaceholderText("Enter some actions...");
    transitionLayout->addWidget(actionLabel);
    transitionLayout->addWidget(actionArea);

    transitionPanel->setLayout(transitionLayout);

    return transitionPanel;
}

/**
 * Create the input variable pannel
 */
QGroupBox* MainWindow::createInputVariablePanel()
{
    QGroupBox* variablePanel = new QGroupBox("Input variables");
    QVBoxLayout* variablePanelLayout = new QVBoxLayout();

    QLabel* variableLabel = new QLabel("Variables");
    QTextEdit* variableArea = new QTextEdit();
    variableArea->setPlaceholderText("Enter a name...");
    variablePanelLayout->addWidget(variableLabel);
    variablePanelLayout->addWidget(variableArea);

    variablePanel->setLayout(variablePanelLayout);

    return variablePanel;
}

/**
 * Create the ouput variable pannel
 */
QGroupBox* MainWindow::createOutputVariablePanel()
{
    QGroupBox* variablePanel = new QGroupBox("Output variables");
    QVBoxLayout* variablePanelLayout = new QVBoxLayout();

    QLabel* variableLabel = new QLabel("Variables");
    QTextEdit* variableArea = new QTextEdit();
    variableArea->setPlaceholderText("Enter a name...");
    variablePanelLayout->addWidget(variableLabel);
    variablePanelLayout->addWidget(variableArea);

    variablePanel->setLayout(variablePanelLayout);

    return variablePanel;
}

/**
 * Create the intern variable pannel
 */
QGroupBox* MainWindow::createInternVariablePanel()
{
    QGroupBox* variablePanel = new QGroupBox("Intern variables");
    QVBoxLayout* variablePanelLayout = new QVBoxLayout();

    QLabel* variableLabel = new QLabel("Variables");
    QTextEdit* variableArea = new QTextEdit();
    variableArea->setPlaceholderText("Enter a name...");
    variablePanelLayout->addWidget(variableLabel);
    variablePanelLayout->addWidget(variableArea);

    variablePanel->setLayout(variablePanelLayout);

    return variablePanel;
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
