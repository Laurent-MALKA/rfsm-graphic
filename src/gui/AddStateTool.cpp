#include "AddStateTool.hpp"
#include "MainWindow.hpp"

AddStateTool::AddStateTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("../assets/state.svg");
}

AddStateTool::~AddStateTool()
{
    
}

void AddStateTool::pressAct(QGraphicsSceneMouseEvent *event)
{
    Canvas* canvas = main_window->getCanvas();
    QPointF click_pos = event->scenePos();

    StateUI* state = canvas->addState(click_pos.x(), click_pos.y());
    state->setFlag(QGraphicsItem::ItemIsMovable, false);
}
