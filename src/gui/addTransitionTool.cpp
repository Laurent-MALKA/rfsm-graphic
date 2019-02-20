#include "AddTransitionTool.hpp"
#include "MainWindow.hpp"

#include <iostream>

AddTransitionTool::AddTransitionTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/transition.svg");
}

AddTransitionTool::~AddTransitionTool()
{

}

void AddTransitionTool::releaseAct(QGraphicsSceneMouseEvent *event)
{
    Canvas* canvas = main_window->getCanvas();

    StateUI* start_state = dynamic_cast<StateUI*>(canvas->itemAt(event->buttonDownScenePos(Qt::LeftButton), QTransform()));
    StateUI* end_state = dynamic_cast<StateUI*>(canvas->itemAt(event->scenePos(), QTransform()));
    
    if(start_state && end_state)
    {
        canvas->addTransition(*start_state, *end_state);
    }
}