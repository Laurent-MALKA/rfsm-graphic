#ifndef DELETION_TOOL_HPP_INCLUDED
#define DELETION_TOOL_HPP_INCLUDED

#include "Tool.hpp"

class DeletionTool : public Tool
{
  public:
    explicit DeletionTool(MainWindow* main_window);
    ~DeletionTool() = default;

    void pressAct(QGraphicsSceneMouseEvent* event) override;
    void releaseAct(QGraphicsSceneMouseEvent* event) override {}
};

#endif
