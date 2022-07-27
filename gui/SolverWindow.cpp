#include "SolverWindow.hpp"

SolverWindow::SolverWindow(int width, int height) : m_renderField(width, height) 
{
    m_eventLoopThread = std::thread(&SolverWindow::eventLoop,
                                    this, width, height);
}

SolverWindow::~SolverWindow()
{
    if (m_eventLoopThread.joinable())
        m_eventLoopThread.join();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void SolverWindow::eventLoop(int width, int height)
{
    m_window = SDL_CreateWindow("Killer Sudoku Solver",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
        throw std::runtime_error(SDL_GetError());

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr)
        throw std::runtime_error(SDL_GetError());

    while (true)
    {
        SDL_Event evnt{};
        while (SDL_PollEvent(&evnt))
        {
            if (evnt.type == SDL_QUIT)
                return;
            m_renderField.processEvent(evnt);
        }

        SDL_RenderClear(m_renderer);
        m_renderField.draw(m_renderer);
        SDL_RenderPresent(m_renderer);

        std::this_thread::sleep_for(RENDER_DELAY);
    }
}
