#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Game.hpp"

Game breakout;
double deltaTime = 0.0;
uint64 lastFrame = 0;

SDL_AppResult SDL_AppInit([[maybe_unused]] void **appstate, [[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    if (!breakout.Init(800, 600)) {
        SDL_Log("Could not initialize Game.");
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent([[maybe_unused]] void *appstate, SDL_Event *event) {
    const auto sdlAppState = breakout.ProcessInput(event);

    return sdlAppState;
}

SDL_AppResult SDL_AppIterate([[maybe_unused]] void *appstate) {
    // Update
    const uint64 currentFrame = SDL_GetPerformanceCounter();
    deltaTime = static_cast<double>(currentFrame - lastFrame) / static_cast<double>(SDL_GetPerformanceFrequency());
    lastFrame = currentFrame;
    breakout.Update(deltaTime);

    // Render
    breakout.Render();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit([[maybe_unused]] void *appstate, SDL_AppResult result) {
    SDL_Log("%s", "");
#if defined(DEBUG) || defined(_DEBUG)
    if (result == SDL_APP_SUCCESS) SDL_Log("Exiting with status EXIT_SUCCESS");
    else SDL_Log("Exiting with status EXIT_FAILURE");
#endif

    SDL_Quit();
}
