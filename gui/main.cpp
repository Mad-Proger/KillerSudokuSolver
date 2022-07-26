#include <SDL2/SDL.h>
#include "SolverWindow.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

constexpr int RENDER_WIDTH = 1280;
constexpr int RENDER_HEIGHT = 720;
constexpr int DIMENSION_GAP = 100;

std::pair<int, int> getWindowSize()
{
    SDL_DisplayMode displayMode{};
    if (SDL_GetDesktopDisplayMode(0, &displayMode) < 0)
    {
        const std::string errorMessage(SDL_GetError());
        throw std::runtime_error("could not get display parameters: " + errorMessage);
    }

    if (displayMode.w > RENDER_WIDTH && displayMode.h > RENDER_HEIGHT)
        return std::pair{ RENDER_WIDTH, RENDER_HEIGHT };

    const int maxWidth = displayMode.w - DIMENSION_GAP;
    const int maxHeight = displayMode.h - DIMENSION_GAP;
    const float aspectRatio = 16.F / 9.F;

    if (maxWidth > maxHeight * aspectRatio)
        return std::pair{ int(maxHeight * aspectRatio), maxHeight };
    else
        return std::pair{ maxWidth, int(maxWidth / aspectRatio) };
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    const auto [width, height] = getWindowSize();
    { SolverWindow window(width, height); }

    SDL_Quit();
    return 0;
}
