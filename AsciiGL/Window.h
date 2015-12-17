#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include <stdarg.h>

#include "glm/glm.hpp"
#include "Framebuffer.h"

namespace agl 
{

class Window
{
private:
    WINDOW *window;
    int x, y, width, height;
    std::string title;

public:
    bool drawBox;

    Window(int x, int y, int width, int height);
    ~Window();

    void attrOn(int attr);

    void display();
    void render(const Framebuffer &fb) const;
    void erase() const;

    void setPos(const glm::vec2& pos);
    void setPos(int x, int y);
    void setSize(const glm::vec2& size);
    void setSize(int width, int height);
    void setTitle(const std::string& newTitle);

    void printf(int x, int y, const char* format, ... );
    void write(int x, int y, const std::string &str);

    int getX() { return x; }
    int getY() { return y; }
    int getWidth() { return width; }
    int getHeight() { return height; }

    int getClippedX();
    int getClippedY();
    int getClippedWidth();
    int getClippedHeight();

    static int getMaxWidth();
    static int getMaxHeight();
};
}

#endif // WINDOW_H
