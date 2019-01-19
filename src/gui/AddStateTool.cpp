#include "AddStateTool.hpp"
#include "Canvas.hpp"

AddStateTool::AddStateTool(Canvas* canvas) : Tool(canvas)
{
    setCursor("../assets/state.svg");
}

AddStateTool::~AddStateTool()
{
    
}

void AddStateTool::act(QMouseEvent *event)
{
    StateUI* state = canvas->addState(event->x(), event->y());
    state->move(state->x() - state->width()/2, state->y() - state->height()/2);
    state->show();
}