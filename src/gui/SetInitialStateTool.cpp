#include "SetInitialStateTool.hpp"
#include "MainWindow.hpp"
#include "StateUI.hpp"

#include <iostream>

SetInitialStateTool::SetInitialStateTool(MainWindow* main_window)
    : Tool(main_window), current_initial_state(nullptr)
{
    setCursor("assets/init_state.svg");
}

void SetInitialStateTool::pressAct(QGraphicsSceneMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QPointF click_pos = event->scenePos();

    QGraphicsItem* item = canvas->itemAt(click_pos, QTransform());
    StateUI* state = dynamic_cast<StateUI*>(item);

    if(state != nullptr)
    {
        canvas->setInitialState(state->getState().getId());

        main_window->getPropertiesPanel()->setSelectedItem(state);
        main_window->setUnsavedChanges(true);
    }
}