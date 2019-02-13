#include <iostream>
#include <QLabel>
#include "SelectTool.hpp"
#include "MainWindow.hpp"

SelectTool::SelectTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/select.svg");
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
            StateUI* state = (StateUI*) widget;
            std::cout << "State selected : " << state->getState().getId() << std::endl;
        } 
        else
        {
            TransitionUI* transition = (TransitionUI*) widget;
            std::cout << "Transition selected : " << transition->getTransition().getId() << std::endl;
        }
        
        // StateUI* state = (StateUI*)widget; //TODO refactor with type()
        // std::cout << state->getState().getId() << std::endl; //TODO get properties in side panel
    }
}
