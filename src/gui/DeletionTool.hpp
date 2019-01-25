#ifndef DELETION_TOOL_HPP_INCLUDED
#define DELETION_TOOL_HPP_INCLUDED

#include "Tool.hpp"

class DeletionTool : public Tool
{
    public:
        DeletionTool(MainWindow* main_window);
        ~DeletionTool();

        void act(QGraphicsSceneMouseEvent* event);
};

#endif
