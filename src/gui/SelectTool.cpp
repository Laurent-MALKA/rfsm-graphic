#include "SelectTool.hpp"
#include "MainWindow.hpp"

#include <QLabel>
#include <iostream>

SelectTool::SelectTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/select.svg", 0, 0);
}

void SelectTool::pressAct(QGraphicsSceneMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QGraphicsItem* item = canvas->itemAt(event->scenePos(), QTransform());

    if(item != nullptr)
    {
        if(item->type() == StateUI::Type)
        {
            StateUI* state = dynamic_cast<StateUI*>(item);
            if(state != nullptr)
            {
                std::cout << "State selected : " << state->getState().getId()
                          << std::endl;
            }
        }
        else
        {
            TransitionUI* transition = dynamic_cast<TransitionUI*>(item);
            if(transition != nullptr)
            {
                std::cout << "Transition selected : "
                          << transition->getTransition().getId() << std::endl;
            }
        }
    }
}
