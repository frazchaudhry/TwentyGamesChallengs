#include "Entity.hpp"

Entity::Entity(const std::string &id, const LC_FRect &pos, const LC_Color &color) : id(id), velocity{ 0.0f, 0.0f } {
    transform.x = pos.x;
    transform.y = pos.y;
    transform.w = pos.w;
    transform.h = pos.h;
    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;
    this->color.a = color.a;
}

void Entity::ProcessInput([[maybe_unused]]const SDL_Event *event) {}

void Entity::Update([[maybe_unused]]double deltaTime, [[maybe_unused]]const int32 screenHeight) {}

void Entity::Render(LC_GL_Renderer *renderer) {
    LC_GL_RenderRectangle(renderer, &transform, &color, false);
}

Wall::Wall(const std::string &id, const LC_FRect &pos, const LC_Color &color, const bool isVisible) : Entity(id ,pos, color), isVisible(isVisible) {

}

void Wall::Render(LC_GL_Renderer *renderer) {
    if (!isVisible) return;

    this->Entity::Render(renderer);
}

Divider::Divider(const std::string &id, const LC_FRect &pos, const LC_Color &color) : Entity(id, pos, color) {
}

void Divider::Render(LC_GL_Renderer *renderer) {
    LC_GL_RenderRectangle(renderer, &transform, &color, true);
}

Paddle::Paddle(const std::string &id, const LC_FRect &pos, const LC_Color &color) : Entity(id, pos, color) {}

void Paddle::ProcessInput(const SDL_Event *event) {
    if (id == "leftPaddle") {
        if (event->key.key == SDLK_W && event->type == SDL_EVENT_KEY_DOWN) {
            state = PaddleState::UP;
        } else if (event->type == SDL_EVENT_KEY_UP && (event->key.key == SDLK_W || event->key.key == SDLK_S)) {
            state = PaddleState::STOP;
        } else if (event->key.key == SDLK_S && event->type == SDL_EVENT_KEY_DOWN) {
            state = PaddleState::DOWN;
        } 
    } else if (id == "rightPaddle") {
        if (event->key.key == SDLK_UP && event->type == SDL_EVENT_KEY_DOWN) {
            state = PaddleState::UP;
        } else if (event->type == SDL_EVENT_KEY_UP && (event->key.key == SDLK_UP || event->key.key == SDLK_DOWN)) {
            state = PaddleState::STOP;
        } else if (event->key.key == SDLK_DOWN && event->type == SDL_EVENT_KEY_DOWN) {
            state = PaddleState::DOWN;
        }
    } 
}

void Paddle::Update(const double deltaTime, const int32 screenHeight) {
    const auto deltaTimeF = static_cast<float>(deltaTime);
    constexpr auto paddleVelocity = static_cast<float>(PADDLE_VELOCITY);
    if (state == PaddleState::UP && transform.y >= Wall::HEIGHT) {
        transform.y -= paddleVelocity * deltaTimeF;
    } else if (state == PaddleState::DOWN && transform.y <= static_cast<float>(screenHeight) - (PADDLE_HEIGHT + Wall::HEIGHT)) {
        transform.y += paddleVelocity * deltaTimeF;
    }
}

void Paddle::UpdateAi(double deltaTime, float ballY, int32 screenHeight) {
    const auto deltaTimeF = static_cast<float>(deltaTime);
    constexpr auto paddleVelocity = static_cast<float>(PADDLE_VELOCITY);
    if (transform.y + transform.h / 2 < ballY + 5 && transform.y <= static_cast<float>(screenHeight) - (PADDLE_HEIGHT + Wall::HEIGHT)) {
        transform.y += paddleVelocity * deltaTimeF;
    } else if (transform.y + transform.h / 2 > ballY + 5 && transform.y >= Wall::HEIGHT) {
        transform.y -= paddleVelocity * deltaTimeF;
    }
}

Ball::Ball(const std::string &id, const LC_FRect &pos, const LC_Color &color) : Entity(id, pos, color) {
    velocity[0] = 1.0f;
}

void Ball::Update(const double deltaTime, [[maybe_unused]]const int32 screenHeight) {
    const float currentSpeed = speed * static_cast<float>(deltaTime);
    vec2 currentPos = { transform.x, transform.y };
    glm_vec2_muladds(velocity, currentSpeed, currentPos);
    transform.x = currentPos[0];
    transform.y = currentPos[1];
}

