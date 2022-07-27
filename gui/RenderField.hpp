#pragma once

#include "core/Field.hpp"

#include <SDL2/SDL.h>

class RenderField : public Field
{
public:
    RenderField(int width, int height);
    ~RenderField();

    void draw(SDL_Renderer* renderer) const;
    void processEvent(const SDL_Event& evnt);
};
