#include <iostream>
#include <QLabel>
#include "SelectTool.hpp"
#include "MainWindow.hpp"

SelectTool::SelectTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../asset/select.svg");
}

SelectTool::~SelectTool() 
{

}

void SelectTool::act(QMouseEvent* event)
{
    //TODO parcours des transitions
    Canvas* canvas = main_window->getCanvas();
    QPoint click_pos = canvas->mapFrom(main_window, event->pos());

    QWidget* state = canvas->childAt(click_pos);
    if(state)
    {
        while(state->parentWidget() != canvas)
            state = state->parentWidget();
        std::cout << ((StateUI*)state)->getState().getId() << std::endl;
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