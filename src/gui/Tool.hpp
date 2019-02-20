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

        virtual void pressAct(QGraphicsSceneMouseEvent *event) = 0;
        virtual void releaseAct(QGraphicsSceneMouseEvent *event) = 0;
        void setCursor(const std::string& path_to_file, int hotX = -1, int hotY = -1);
        QCursor& getCursor() const;
};

#endif
