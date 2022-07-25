#include <SDL2/SDL.h>
#include "SolverWindow.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_DisplayMode displayMode{};
    if (SDL_GetDesktopDisplayMode(0, &displayMode) < 0)
    {
        std::cerr << "Could not get display dimensions: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 0;
    }

    SolverWindow window(displayMode.w, displayMode.h);    

    SDL_Quit();
    return 0;
}
