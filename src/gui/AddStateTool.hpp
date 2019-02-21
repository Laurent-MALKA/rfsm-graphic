#ifndef ADD_STATE_TOOL
#define ADD_STATE_TOOL

#include "Tool.hpp"

class AddStateTool : public Tool
{
  public:
    explicit AddStateTool(MainWindow* main_window);
    ~AddStateTool() = default;

    void pressAct(QGraphicsSceneMouseEvent* event) override;
    void releaseAct(QGraphicsSceneMouseEvent* event) override {}
};

#endif
