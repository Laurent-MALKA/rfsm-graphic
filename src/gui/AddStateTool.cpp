#include "AddStateTool.hpp"
#include "MainWindow.hpp"

AddStateTool::AddStateTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/state.svg");
}

AddStateTool::~AddStateTool()
{
    
}

void AddStateTool::act(QMouseEvent *event)
{
    Canvas* canvas = main_window->getCanvas();
    StateUI* state = canvas->addState(event->x(), event->y());
    state->move(state->x() - state->width()/2, state->y() - state->height()/2);
    state->show();
}