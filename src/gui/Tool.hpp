#ifndef TOOL_HPP_INCLUDED
#define TOOL_HPP_INCLUDED

#include <string>

#include <QCursor>
#include <QMouseEvent>

class Canvas;

class Tool
{
    protected:
        Canvas* canvas;
        QCursor* cursor;

    public:
        Tool(Canvas* canvas);
        virtual ~Tool();

        virtual void act(QMouseEvent *event) = 0;
        void setCursor(std::string path_to_file);
        QCursor& getCursor() const;

};

#endif