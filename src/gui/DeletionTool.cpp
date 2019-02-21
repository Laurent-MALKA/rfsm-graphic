#include "DeletionTool.hpp"
#include "MainWindow.hpp"

DeletionTool::DeletionTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/delete.svg");
}

void DeletionTool::pressAct(QGraphicsSceneMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QPointF click_pos = event->scenePos();

    QGraphicsItem* item = canvas->itemAt(click_pos, QTransform());

    if(item != nullptr)
    {
        if(item->type() == StateUI::Type)
        {
            StateUI* state = dynamic_cast<StateUI*>(item);
            if(state != nullptr)
            {
                canvas->deleteState(state->getState().getId());
            }
        }
        else
        {
            TransitionUI* transition = dynamic_cast<TransitionUI*>(item);
            if(transition != nullptr)
            {
                canvas->deleteTransition(transition->getTransition().getId());
            }
        }
    }
}
