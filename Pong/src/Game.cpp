#include "Game.hpp"
#include <cstdlib>
#include <libraCore.h>

bool Game::Init() {
    backingBuffer = malloc(100 * 1024);
    arena = new LC_Arena();
    LC_Arena_Initialize(arena, backingBuffer, 100 * 1024);

    renderer = static_cast<LC_GL_Renderer*>(LC_Arena_Allocate(arena, sizeof(LC_GL_Renderer)));
    LC_GL_InitializeRenderer(arena, renderer, 800, 600);

    if (LC_GL_InitializeVideo(arena, renderer, "Pong", "assets/fonts/pong-score-extended.ttf", errorLog)) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not initialize Video.%s", errorLog);
        return false;
    }

    // Disabling Vsync
    if (!SDL_GL_SetSwapInterval(0)) {
        SDL_Log("Failed to disable Vsync.");
        return false;
    }

    return true;
}

SDL_AppResult Game::ProcessInput(SDL_Event *event) {
    if (event->key.key == SDLK_ESCAPE ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (renderer && event->type == SDL_EVENT_WINDOW_RESIZED) {
        int width, height = 0;
        SDL_GetWindowSize(renderer->window, &width, &height);
        LC_GL_FramebufferSizeCallback(width, height);
    }
    return SDL_APP_CONTINUE;
}

void Game::Update([[maybe_unused]]float deltaTime) {

}

void Game::Render() {
    // Clear background
    LC_GL_ClearBackground(LC_Color_Create(0.0f, 0.0f, 0.5f, 1.0f));

    constexpr LC_GL_Text textToShow = {
        .string = (char*)"Making Pong!",
        .position = { 300, 300, 0.0f },
        .color = { 255, 255, 255, 1.0 },
        .scale = 2.0f
    };
    LC_GL_RenderText(renderer, &textToShow);

    // Swap buffers
    if (!LC_GL_SwapBuffer(renderer->window, errorLog)) {
        SDL_Log("%s\n", errorLog);
    }

}

void Game::Unload() {
    LC_GL_FreeResources(renderer);

    LC_Arena_FreeAll(arena);
    delete arena;
    free(backingBuffer);
}

Game::~Game() {

}
