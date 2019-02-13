#include "DeletionTool.hpp"
#include "MainWindow.hpp"

DeletionTool::DeletionTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/delete.svg");
}

DeletionTool::~DeletionTool()
{

}

void DeletionTool::pressAct(QGraphicsSceneMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QPointF click_pos = event->scenePos();

    QGraphicsItem* widget = canvas->itemAt(click_pos, QTransform());

    if(widget)
    {
        if(widget->type() == StateUI::Type) 
        {
            StateUI* state = (StateUI*)widget;
            canvas->deleteState(state->getState().getId());
        }
        else
        {
            TransitionUI* transition = (TransitionUI*) widget;
            canvas->deleteTransition(transition->getTransition().getId());
        }
        
    }
}
