#include "Tool.hpp"
#include "MainWindow.hpp"

Tool::Tool(MainWindow* main_window): main_window(main_window), cursor(new QCursor(Qt::ArrowCursor)) {}

Tool::~Tool()
{
    delete cursor;
}

void Tool::setCursor(const std::string& path_to_file, int hotX, int hotY)
{
    QPixmap icon(path_to_file.c_str());
    icon = icon.scaled(16,16,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    delete cursor;
    cursor = new QCursor(icon, hotX, hotY);
}

QCursor& Tool::getCursor() const
{
    return *cursor;
}
