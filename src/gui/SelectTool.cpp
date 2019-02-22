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
        main_window->getPropertiesPanel()->setSelectedItem(item);
    else
        main_window->getPropertiesPanel()->unselectItem();
}
