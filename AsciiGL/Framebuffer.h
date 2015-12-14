#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <ncurses.h>

#include <vector>
#include "Texture.h"
#include "glm/glm.hpp"

typedef std::pair<int, char> Fragment; //color_id, value_char

namespace agl 
{
    class Framebuffer
    {
    friend class Window;

    private:

        static char greyrampChars[];

        int width, height;
        Texture colorBuffer;
        Texture zBuffer;

        static Fragment getColorID(const glm::vec4 &rgb);
        static void initializeColor();

        void render(WINDOW *win) const;

    public:

        Framebuffer(int width, int height);

        void setPixel(const glm::vec3 &pos, const glm::vec4 &color);

        void clearColorBuffer();
        void clearZBuffer();
        void clearBuffers();

        int getWidth() const { return width; }
        int getHeight() const { return height; }
    };
}

#endif // FRAMEBUFFER_H
