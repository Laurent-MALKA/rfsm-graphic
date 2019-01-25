#ifndef TOOL_HPP_INCLUDED
#define TOOL_HPP_INCLUDED

#include <string>

#include <QCursor>
#include <QGraphicsSceneMouseEvent>

class MainWindow;

class Tool
{
    protected:
        MainWindow* main_window;
        QCursor* cursor;

    public:
        Tool(MainWindow* main_window);
        virtual ~Tool();

        virtual void act(QGraphicsSceneMouseEvent *event) = 0;
        void setCursor(std::string path_to_file);
        QCursor& getCursor() const;
};

#endif