#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

extern "C" {
#include <libraVideo.h>
}

class Entity {
public:
    std::string id;
    LC_Rect transform;
    vec2 velocity;
    LC_Color color;

    Entity() = default;
    Entity(std::string id, LC_Rect pos, LC_Color color);

    virtual ~Entity() = default;

    virtual void ProcessInput(const SDL_Event *event);
    virtual void Update(double deltaTime, int32 screenHeight);
    virtual void Render(LC_GL_Renderer *renderer);
};

class Wall final : public Entity {
public: 
    bool isVisible;
    static const int32 HEIGHT { 25 };

    Wall() = default;
    Wall(std::string id, LC_Rect pos, LC_Color color, bool isVisible);

    void Render(LC_GL_Renderer *renderer) override;
};

class Divider final : public Entity {
public:
    Divider() = default;
    Divider(std::string id, LC_Rect pos, LC_Color color);
    void Render(LC_GL_Renderer *renderer) override;
};

class Paddle final : public Entity {
public:
    enum PaddleState {
        STOP,
        UP,
        DOWN
    };
    PaddleState state { STOP };
    static const int32 PADDLE_WIDTH { 10 };
    static const int32 PADDLE_HEIGHT { 50 };
    static const int32 PADDLE_VELOCITY { 300 };

    Paddle() = default;
    Paddle(std::string id, LC_Rect pos, LC_Color color);

    void ProcessInput(const SDL_Event *event) override;
    void Update(double deltaTime, int32 screenHeight) override;
private:
};

#endif // ENTITY_HPP

