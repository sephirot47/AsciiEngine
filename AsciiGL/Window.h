#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include<stdarg.h>

#include "Framebuffer.h"

namespace agl 
{

class Window
{
private:
    WINDOW *window;
    int x, y, width, height;

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

    void printf(int x, int y, const char* format, ... );

    int getX() { return x; }
    int getY() { return y; }
    int getWidth() { return width; }
    int getHeight() { return height; }

    static int getMaxWidth();
    static int getMaxHeight();
};
}

#endif // WINDOW_H
