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

void SelectTool::act(QMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QPoint click_pos = canvas->mapFrom(main_window, event->pos());

    QWidget* widget = canvas->childAt(click_pos);
    if(widget)
    {
        while(widget->parentWidget() != canvas)
            widget = widget->parentWidget();
        StateUI* state = (StateUI*)widget;
        std::cout << state->getState().getId() << std::endl;
    }
        //std::cout << "[" << state->x() << "," << state->y() << "]" << std::endl;

    // auto states = canvas->getStates();
    // auto state = states.crbegin();
    // for(; state != states.crend(); state++)
    // {
    //     if((*state)->getRegion().contains(event->pos()))
    //         break;
    // } 


    // if(state != states.crend())
    // else
    //     std::cout << "Noeud non trouvé" << std::endl;
}