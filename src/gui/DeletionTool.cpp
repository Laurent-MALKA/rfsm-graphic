#include "DeletionTool.hpp"
#include "MainWindow.hpp"

DeletionTool::DeletionTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/delete.svg");
}

DeletionTool::~DeletionTool()
{

}

void DeletionTool::act(QMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QPoint click_pos = canvas->mapFrom(main_window, event->pos());

    QWidget* widget = canvas->childAt(click_pos);

    if(widget)
    {
        while(widget->parentWidget() != canvas)
            widget = widget->parentWidget();
        StateUI* state = (StateUI*)widget;
        canvas->deleteState(state->getState().getId());
    }
}