#ifndef SELECT_TOOL_HPP_INCLUDED
#define SELECT_TOOL_HPP_INCLUDED

#include "Tool.hpp"

class MainWindow;

class SelectTool : public Tool
{
    public:
        explicit SelectTool(MainWindow* main_window);
        ~SelectTool();

        void pressAct(QGraphicsSceneMouseEvent* event);
        void releaseAct(QGraphicsSceneMouseEvent *event) {}
};

#endif
