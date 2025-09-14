#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Game.hpp"

Game *breakout;

SDL_AppResult SDL_AppInit([[maybe_unused]]void **appstate, [[maybe_unused]]int argc, [[maybe_unused]]char *argv[]) {
    breakout = new Game();
    if (!breakout->Init()) {
        SDL_Log("Could not initialize Game.");
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent([[maybe_unused]]void *appstate, SDL_Event *event) {
    const auto gameState = breakout->ProcessInput(event);

    return gameState;
}

SDL_AppResult SDL_AppIterate([[maybe_unused]]void *appstate) {
    // Update
    breakout->Update(0.0f);

    // Render
    breakout->Render();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit([[maybe_unused]]void *appstate, SDL_AppResult result) {
    delete breakout;
    SDL_Log("%s", "");
    if (result == SDL_APP_SUCCESS) SDL_Log("Exiting with status EXIT_SUCCESS");
    else SDL_Log("Exiting with status EXIT_FAILURE");
    SDL_Quit();
}
