#include "SelectTool.hpp"
#include "MainWindow.hpp"

SelectTool::SelectTool(MainWindow* main_window) : Tool(main_window)
{
    setCursor("assets/select.svg", 0, 0);
}

void SelectTool::pressAct(QGraphicsSceneMouseEvent* event)
{
    Canvas* canvas = main_window->getCanvas();
    QGraphicsItem* item = canvas->itemAt(event->scenePos(), QTransform());

    if(item != nullptr)
        main_window->getPropertiesPanel()->setSelectedItem(item);
    else
        main_window->getPropertiesPanel()->unselectItem();
}

void SelectTool::releaseAct(QGraphicsSceneMouseEvent* event)
{
    StateUI* state = dynamic_cast<StateUI*>(
        main_window->getCanvas()->itemAt(event->scenePos(), QTransform()));

    // TODO find a proper way to detect if an object has moved
    if(event->buttonDownScenePos(Qt::LeftButton) != event->scenePos()
       && state != nullptr)
        main_window->setUnsavedChanges(true);
}
