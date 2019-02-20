#include <iostream>
#include <QLabel>
#include "SelectTool.hpp"
#include "MainWindow.hpp"

SelectTool::SelectTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/select.svg",0,0);
}

SelectTool::~SelectTool() 
{

}

void SelectTool::pressAct(QGraphicsSceneMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QGraphicsItem* widget = canvas->itemAt(event->scenePos(), QTransform());

    if(widget)
    {
        if(widget->type() == StateUI::Type)
        {
            StateUI* state = dynamic_cast<StateUI*>(widget);
            if(state)
                std::cout << "State selected : " << state->getState().getId() << std::endl;
        } 
        else
        {
            TransitionUI* transition = dynamic_cast<TransitionUI*>(widget);
            if(transition)
                std::cout << "Transition selected : " << transition->getTransition().getId() << std::endl;
        }        
    }
}
