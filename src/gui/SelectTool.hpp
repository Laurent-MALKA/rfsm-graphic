#ifndef SELECT_TOOL_HPP_INCLUDED
#define SELECT_TOOL_HPP_INCLUDED

#include "Tool.hpp"

class MainWindow;

class SelectTool : public Tool
{
  public:
    explicit SelectTool(MainWindow* main_window);
    ~SelectTool() = default;

    void pressAct(QGraphicsSceneMouseEvent* event) override;
    void releaseAct(QGraphicsSceneMouseEvent* event) override;
};

#endif
