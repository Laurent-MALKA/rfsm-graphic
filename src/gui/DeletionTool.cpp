#include "DeletionTool.hpp"
#include "MainWindow.hpp"

DeletionTool::DeletionTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/delete.svg");
}

DeletionTool::~DeletionTool()
{

}

void DeletionTool::act(QGraphicsSceneMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QPointF click_pos = event->scenePos();

    QGraphicsItem* widget = canvas->itemAt(click_pos, QTransform());

    if(widget)
    {
    
        StateUI* state = (StateUI*)widget;
        canvas->deleteState(state->getState().getId());
    }
}
