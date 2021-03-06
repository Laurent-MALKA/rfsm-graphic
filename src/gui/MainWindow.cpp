#include "MainWindow.hpp"
#include "Canvas.hpp"
#include "PropertiesPanel.hpp"
#include "Tools.hpp"

#include <QApplication>
#include <QComboBox>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>
#include <cstdio>
#include <fstream>

MainWindow::MainWindow() : unsaved_changes(false)
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
    setCurrentTool(ToolEnum::select);
}

MainWindow::~MainWindow()
{
    for(auto& tool : tools)
        delete tool.second;
    delete menu_bar;
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

void MainWindow::setUnsavedChanges(bool unsaved_changes)
{
    this->unsaved_changes = unsaved_changes;
    setWindowTitle(unsaved_changes ? "RFSM Graphic (Unsaved changes)"
                                   : "RFSM Graphic");
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if(event->matches(QKeySequence::SelectAll))
        canvas->selectAllItems();

    else if(event->key() == Qt::Key_Delete)
        deleteSelectedItems();
}

/**
 * Generate the menu
 */
void MainWindow::createMenu()
{
    // Setup the menubar
    menu_bar = menuBar();
    file_menu = menu_bar->addMenu("&File");

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
        "&Exit", this, SLOT(closeWindow()), QKeySequence("Ctrl+Q"));
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
        createPushButton("Selection", "assets/select.svg");
    QPushButton* set_initial_state_tool =
        createPushButton("Initial State", "assets/init_state.svg");
    QPushButton* add_state_tool = createPushButton("State", "assets/state.svg");
    QPushButton* add_transition_tool =
        createPushButton("Transition", "assets/transition.svg");
    QPushButton* deletion_tool =
        createPushButton("Delete", "assets/delete.svg");

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
    connect(set_initial_state_tool, &QPushButton::clicked, this, [this]() {
        setCurrentTool(ToolEnum::set_initial_state);
    });
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

void MainWindow::closeWindow()
{
    if(unsaved_changes)
    {
        QMessageBox save_message;
        save_message.setText("Do you want to save your changes?");
        save_message.setStandardButtons(QMessageBox::Save | QMessageBox::Discard
                                        | QMessageBox::Cancel);
        save_message.setDefaultButton(QMessageBox::Save);

        int save_answer = save_message.exec();

        switch(save_answer)
        {
            case QMessageBox::Cancel:
                return;
            case QMessageBox::Save:
                save();
        }
    }

    close();
}

/**
 * Create a new file
 */
void MainWindow::newFile()
{
    if(unsaved_changes)
    {
        QMessageBox save_message;
        save_message.setText("Do you want to save your changes?");
        save_message.setStandardButtons(QMessageBox::Save | QMessageBox::Discard
                                        | QMessageBox::Cancel);
        save_message.setDefaultButton(QMessageBox::Save);

        int save_answer = save_message.exec();

        switch(save_answer)
        {
            case QMessageBox::Cancel:
                return;
            case QMessageBox::Save:
                save();
        }
    }

    canvas->clear();
    properties_panel->clear();

    file_name.clear();

    setUnsavedChanges(false);
}

/**
 * Open a new file
 */
void MainWindow::openFile()
{
    if(unsaved_changes)
    {
        QMessageBox save_message;
        save_message.setText("Do you want to save your changes?");
        save_message.setStandardButtons(QMessageBox::Save | QMessageBox::Discard
                                        | QMessageBox::Cancel);
        save_message.setDefaultButton(QMessageBox::Save);

        int save_answer = save_message.exec();

        switch(save_answer)
        {
            case QMessageBox::Cancel:
                return;
            case QMessageBox::Save:
                save();
        }
    }

    std::ifstream file;
    std::string new_file_name;

    do
    {
        new_file_name = QFileDialog::getOpenFileName(
                            this, "Open state chart", "", "GFSM file (*.gfsm)")
                            .toStdString();

        if(new_file_name.empty())
            return;

        file.open(new_file_name);
        if(!file)
            QMessageBox::warning(this, "Error", "Unable to open file");
    } while(!file);

    try
    {
        std::string json_data;

        // Fills json_data with the content of the whole file
        file.seekg(0, std::ios::end);
        json_data.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        json_data.assign((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

        canvas->importCanvas(json_data);
    }
    catch(const std::exception& e)
    {
        QMessageBox::warning(
            this, "Error", "Unable to import : " + QString(e.what()));
        return;
    }

    properties_panel->clear();

    file_name = new_file_name;
    setUnsavedChanges(false);
}

/**
 * Save the file
 */
void MainWindow::save()
{
    std::ofstream file(file_name);

    if(!file)
    {
        saveAs();
    }
    else
    {
        file << canvas->exportCanvas();
        setUnsavedChanges(false);
    }
}

/**
 * Save as the file
 */
void MainWindow::saveAs()
{
    std::ofstream file;

    do
    {
        file_name = QFileDialog::getSaveFileName(
                        this, "Save state chart", "", "GFSM file (*.gfsm)")
                        .toStdString();

        if(file_name.empty())
            return;

        if(file_name.substr(file_name.length() - 5) != ".gfsm")
            file_name += ".gfsm";

        file.open(file_name);
        if(!file)
            QMessageBox::warning(this, "Error", "Unable to open file");
    } while(!file);

    file << canvas->exportCanvas();
    setUnsavedChanges(false);
}

/**
 * Export the file
 */
void MainWindow::exportContent()
{
    std::string fsm_code;
    try
    {
        fsm_code = canvas->getStateChart()->toFSMCode();
    }
    catch(const std::exception& e)
    {
        QMessageBox::warning(
            this, "Error", "Unable to export : " + QString(e.what()));
        return;
    }

    std::ofstream file;
    std::string file_name;

    do
    {
        file_name = QFileDialog::getSaveFileName(
                        this, "Export to FSM file", "", "FSM file (*.fsm)")
                        .toStdString();

        if(file_name.empty())
            return;

        if(file_name.substr(file_name.length() - 4) != ".fsm")
            file_name += ".fsm";

        file.open(file_name);
        if(!file)
            QMessageBox::warning(this, "Error", "Unable to open file");
    } while(!file);

    file << fsm_code;
}

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
        view->setDragMode(QGraphicsView::RubberBandDrag);
        canvas->setStatesFlag(QGraphicsItem::ItemIsMovable, true);
        canvas->setStatesFlag(QGraphicsItem::ItemIsSelectable, true);
        canvas->setTransitionsFlag(QGraphicsItem::ItemIsSelectable, true);
    }
    else
    {
        view->setDragMode(QGraphicsView::NoDrag);
        canvas->setStatesFlag(QGraphicsItem::ItemIsMovable, false);
        canvas->setStatesFlag(QGraphicsItem::ItemIsSelectable, false);
        canvas->setTransitionsFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}

void MainWindow::deleteSelectedItems()
{
    if(view->hasFocus() && !canvas->selectedItems().isEmpty())
    {
        canvas->deleteSelectedItems();

        setUnsavedChanges(true);
    }
}