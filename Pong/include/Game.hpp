#ifndef GAME_HPP
#define GAME_HPP

extern "C" {
#include <libraVideo.h>
}

class Game {
public:
    LC_Arena *arena;
    LC_GL_Renderer *renderer;

    Game() = default;
    ~Game();

    bool Init();

    SDL_AppResult ProcessInput(SDL_Event *event);

    void Update(float deltaTime);

    void Render();

    void Unload();
private:
    void *backingBuffer;
    char errorLog[1024];
};

#endif // GAME_HPP

