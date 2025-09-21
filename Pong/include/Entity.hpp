#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

extern "C" {
#include <libraVideo.h>
}

class Entity {
public:
    std::string id;
    LC_Rect transform{ 0, 0, 1, 1 };
    vec2 velocity{ 0 };
    vec2 acceleration { 0 };
    LC_Color color{ .r = 255, .g = 255, .b = 255, .a = 1.0f };

    Entity() = default;
    Entity(std::string id, LC_Rect pos, LC_Color color);

    virtual ~Entity() = default;

    virtual void ProcessInput(const SDL_Event *event);
    virtual void Update(double deltaTime, int32 screenHeight);
    virtual void Render(LC_GL_Renderer *renderer);
};

class Wall final : public Entity {
public: 
    bool isVisible{ false };
    static constexpr int32 HEIGHT { 25 };

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
    static constexpr int32 PADDLE_WIDTH { 10 };
    static constexpr int32 PADDLE_HEIGHT { 50 };

    Paddle() = default;
    Paddle(std::string id, LC_Rect pos, LC_Color color);

    void ProcessInput(const SDL_Event *event) override;
    void Update(double deltaTime, int32 screenHeight) override;
private:
    enum PaddleState {
        PADDLE_STOP,
        PADDLE_UP,
        PADDLE_DOWN
    };
    PaddleState state { PADDLE_STOP };
    static constexpr int32 PADDLE_VELOCITY { 300 };
};

class Ball final : public Entity {
public:
    static constexpr int32 BALL_LENGTH { 10 };
    float currentSpeed { 300 };

    Ball() = default;
    Ball(std::string id, LC_Rect pos, LC_Color color);

    void Update(double deltaTime, int32 screenHeight) override;
};

#endif // ENTITY_HPP

