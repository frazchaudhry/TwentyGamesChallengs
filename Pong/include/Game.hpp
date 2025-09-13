#ifndef GAME_HPP
#define GAME_HPP

#include <libraVideo.h>

class Game {
public:
    Game() = default;
    ~Game();

    void Init();

    void Update(float deltaTime);

    void Render(LC_GL_Renderer *renderer);

    void Unload(LC_GL_Renderer *renderer);
};

#endif // GAME_HPP

