#include "Tool.hpp"
#include "Canvas.hpp"

Tool::Tool(Canvas* canvas): canvas(canvas) {}

Tool::~Tool()
{
    delete canvas;
    delete cursor;
}

void Tool::setCursor(std::string path_to_file)
{
    QPixmap icon(path_to_file.c_str());
    icon = icon.scaled(32,32,Qt::IgnoreAspectRatio);

    cursor = new QCursor(icon);
}

QCursor& Tool::getCursor() const
{
    return *cursor;
}
