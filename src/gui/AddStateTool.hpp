#ifndef ADD_STATE_TOOL
#define ADD_STATE_TOOL

#include "Tool.hpp"

class AddStateTool : public Tool
{
    public:
        AddStateTool(MainWindow* main_window);
        ~AddStateTool();
        void act(QMouseEvent *event);

        QCursor& getCursor() const;


};

#endif