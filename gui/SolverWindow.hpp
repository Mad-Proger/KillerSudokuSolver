#pragma once

#include <SDL2/SDL.h>

#include <chrono>
#include <stdexcept>
#include <thread>

class SolverWindow
{
public:
    SolverWindow(int width, int height);
    ~SolverWindow();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::thread m_eventLoopThread;

    void eventLoop(int width, int height);

    static constexpr std::chrono::duration RENDER_DELAY = std::chrono::milliseconds(30);
};
