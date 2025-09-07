#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

extern "C" {
#include "libraVideo.h"
}

static constexpr uint64 STARTING_ARENA_SIZE = 100 * 1024;
static void *backingBuffer = nullptr;
static LC_Arena arena;

SDL_AppResult SDL_AppInit([[maybe_unused]]void **appstate, [[maybe_unused]]int argc, [[maybe_unused]]char *argv[]) {
    backingBuffer = malloc(STARTING_ARENA_SIZE);
    LC_Arena_Initialize(&arena, backingBuffer, STARTING_ARENA_SIZE);

    LC_GL_Renderer *renderer = (LC_GL_Renderer*)LC_Arena_Allocate(&arena, sizeof(LC_GL_Renderer));
    LC_GL_InitializeRenderer(&arena, renderer, 800, 600);

    *appstate = renderer;

    char errorLog[1024];
    if (LC_GL_InitializeVideo(&arena, renderer, "Pong", "assets/fonts/pong-score-extended.ttf", errorLog)) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not initialize Video.%s", errorLog);
        return SDL_APP_FAILURE;
    }

    // Disabling Vsync
    SDL_GL_SetSwapInterval(0);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    LC_GL_Renderer *renderer = (LC_GL_Renderer*)appstate;
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

SDL_AppResult SDL_AppIterate(void *appstate) {
    LC_GL_Renderer *renderer = (LC_GL_Renderer*)appstate;
    char errorLog[1024];

    // Clear background
    LC_GL_ClearBackground(LC_Color_Create(51.0f, 51.0f, 76.5f, 1.0f));

    // Render

    // Swap buffers
    if (!LC_GL_SwapBuffer(renderer->window, errorLog)) {
        SDL_Log("%s\n", errorLog);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit([[maybe_unused]]void *appstate, [[maybe_unused]]SDL_AppResult result) {
    SDL_Quit();
}
